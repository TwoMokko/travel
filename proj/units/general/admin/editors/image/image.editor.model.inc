<?php

	namespace Proj\Admin\Editor\Model;

	use Base\DB\MySQLi\Table;
	use Base\DB\MySQLi\Select;
	use Base\Editor\MySQLi\Model;
	use Proj\Units\Consts;
	use Proj\Others\UploaderImage;

	class Image extends Model {
		public function __construct(Table $table, array $params = []) {
			parent::__construct($table, $params);
		}

		protected function Init(): void {
			$this->querySelect = new Select();
			$this->querySelect
				->calc("*, CONCAT(`hash`, '.', `id`, '.', `ext`) AS `cover`")
				->table($this->table->GetName())
				->where('`state` = ' . Consts\General::STATE_ACTIVE)
				->order('alias')
				->order('id', 'DESC');
		}

		public function GetItem(int $id): array {
			return $this->table->SelectOne(null, "(`id` = {$id})", null, null, ["*", "CONCAT(`hash`, '.', `id`, '.', `ext`) AS `cover`"]);
		}

		protected function PrepareCreate(array & $data, array & $params = []): void {
			$data['state'] = Consts\General::STATE_ACTIVE;
		}

		public function Create(array $data, array $params = []): bool {
			$this->PrepareCreate($data);

			$id = $this->table->Insert($data);

			if ($_FILES['form']['tmp_name']['cover']) {
				[$hash, $ext] = $this->SaveFile($id);
				$this->table->Update(['hash' => $hash, 'ext' => $ext], "`id` = {$id}");
			}

			return true;
		}

		public function Update(array $data, int $id): bool {
			$this->PrepareUpdate($data, $id);
			if ($_FILES['form']['tmp_name']['cover']) {
				$old_file = $this->table->SelectOneFieldCalc("CONCAT(`hash`, '.', `id`, '.', `ext`) AS `alias`", 'alias', "`id` = {$id}");
				if ($old_file) unlink(Consts\General::PATH_IMAGE . $old_file);

				[$hash, $ext] = $this->SaveFile($id);
				$data['hash'] = $hash;
				$data['ext'] = $ext;
			}

			$this->table->Update($data, "`id` = {$id}");

			return true;
		}

		private function SaveFile(int $id): array {
			$dir = Consts\General::PATH_IMAGE;

			$temp_path = $_FILES['form']['tmp_name']['cover'];
			$temp_name = $_FILES['form']['name']['cover'];

			$info = pathinfo($temp_name);
			$ext = $info['extension'];
			$hash = hash_file('md5', $temp_path);

			try {
				$IMG = new UploaderImage($temp_path, $ext);
				$IMG->Save( $dir . '/', "{$hash}.{$id}", null, 2000, 2000, UploaderImage::SIZE_COVER);
			}
			catch (\Exception) { return []; }

			return [$hash, $ext];
		}

	}