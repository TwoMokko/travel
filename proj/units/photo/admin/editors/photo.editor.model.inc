<?php

	namespace Proj\Admin\Editor\Model;

	use Base\DB\MySQLi\Table;
	use Base\DB\MySQLi\Select;
	use Base\Editor\MySQLi\Model;
	use Proj\Units\Consts;
	use Proj\Others\UploaderImage;

	class Photo extends Model {
		private Table $table_show;

		public function __construct(array $tables, array $params = []) {
			[$table, $this->table_show] = $tables;
			parent::__construct($table, $params);
		}

		protected function Init(): void {
			$this->querySelect = new Select();
			$this->querySelect
				->calc("*, CONCAT(`hash`, '.', `id`, '.', `ext`) AS `cover`")
				->table($this->table->GetName())
				->where('`state` != ' . Consts\Photo::STATES['delete'])
				->order('date_create', 'DESC')
				->order('id');
		}

		public function GetItemForBrowse(int $id): array {
			return $this->table->SelectOne(null, "(`id` = {$id})", null, null, ["*, CONCAT(`hash`, '.', `id`, '.', `ext`) AS `cover`"]);
		}

		public function Create(array $data, array $params): bool {
			$id = $this->table->Insert($data);

			if ($_FILES['form']['tmp_name']['cover']) {
				$info = $this->SaveFile($id);
				if (!$info) return false;
				[$hash, $ext] = $info;
				$this->table->Update(['hash' => $hash, 'ext' => $ext], "`id` = {$id}");
			}

			$this->table_show->Update(['all_id' => $id, 'u_id' => ''], "`u_id` = '{$params['uid']}'");


			return true;
		}

		public function Update(array $data, int $id): bool {
			if ($_FILES['form']['tmp_name']['cover']) {
				$old_file = $this->table->SelectOneFieldCalc("CONCAT(`hash`, '.', `id`, '.', `ext`) AS `name`", 'name', "`id` = {$id}");
				if ($old_file) {
					if (file_exists(Consts\Photo::PATH_ALL_ORIGINAL . $old_file)) unlink(Consts\Photo::PATH_ALL_ORIGINAL . $old_file);
					if (file_exists(Consts\Photo::PATH_ALL_PREVIEW . $old_file)) unlink(Consts\Photo::PATH_ALL_PREVIEW . $old_file);
				}
				$info = $this->SaveFile($id);
				if (!$info) return false;
				[$data['hash'], $data['ext']] = $info;
			}

			$this->table->Update($data, "`id` = {$id}");

			return true;
		}

		private function SaveFile(int $id): array {
			$dir_original = Consts\Photo::PATH_ALL_ORIGINAL;
			$dir_preview = Consts\Photo::PATH_ALL_PREVIEW;

			$temp_path = $_FILES['form']['tmp_name']['cover'];
			$temp_name = $_FILES['form']['name']['cover'];

			$info = pathinfo($temp_name);
			$ext = strtolower($info['extension']);
			$hash = hash_file('md5', $temp_path);

			try {
				$IMG = new UploaderImage($temp_path, $ext);
//				$IMG->Save( $dir . '/', "{$hash}.{$id}");
				$IMG->Save($dir_original . '/', "{$hash}.{$id}", null, 2000, 2000, UploaderImage::SIZE_COVER);
				$IMG->Save($dir_preview . '/', "{$hash}.{$id}", null, 500, 500, UploaderImage::SIZE_COVER);
			}
			catch (\Exception) { return []; }

			return [$hash, $ext];
		}

		public function PhotoLoad(string $uid, int $id_album): array {
			$temp_path = $_FILES['file']['tmp_name'];
			$temp_name = $_FILES['file']['name'];

			$info = pathinfo($temp_name);
			$ext = $info['extension'];
			$hash = hash_file('md5', $temp_path);

			$id = $this->table_show->Insert([
				'u_id' => $uid,
				'all_id' => $id_album,
				'state' => Consts\Photo::STATE_ACTIVE,
				'hash' => $hash,
				'ext' => $ext
			]);

			try {
				$IMG = new UploaderImage($temp_path, $ext);
				$IMG->Save(Consts\Photo::PATH_SHOW_ORIGINAL . '/', "{$hash}.{$id}", null, 2000, 2000, UploaderImage::SIZE_COVER);
				$IMG->Save(Consts\Photo::PATH_SHOW_PREVIEW . '/', "{$hash}.{$id}", null, 500, 500, UploaderImage::SIZE_COVER);
			}
			catch (\Exception $e) { return [0, $e->getMessage()]; }

			return [$id, ''];
		}

		public function PhotoDel(int $id): void {
			$dir_orig = Consts\Photo::PATH_SHOW_ORIGINAL;
			$dir_preview = Consts\Photo::PATH_SHOW_PREVIEW;
			$name = $this->table_show->SelectOneFieldCalc("CONCAT(`hash`, '.', `id`, '.', `ext`) AS `name`", 'name', "`id` = {$id}");

			if (file_exists($dir_orig . $name)) unlink($dir_orig . $name);
			if (file_exists($dir_preview . $name)) unlink($dir_preview . $name);
			$this->table_show->Delete("`id` = {$id}");
		}

		public function Cron() {
			$result = $this->table_show->Select(['id'],"`date_create` < DATE_SUB(NOW(), INTERVAL 1 MONTH) AND `all_id` = 0", null, null, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `name`"]);
			while ($row = $this->table_show->Fetch($result)) {
				unlink(Consts\Photo::PATH_SHOW_ORIGINAL . $row['name']);
				unlink(Consts\Photo::PATH_SHOW_PREVIEW . $row['name']);
				$this->table_show->Delete("`id` = {$row['id']}");
			}
		}

	}