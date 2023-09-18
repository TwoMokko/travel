<?php

	namespace Proj\Admin\Editor\Model;

	use Base\DB\MySQLi\Table;
	use Base\DB\MySQLi\Select;
	use Base\Editor\MySQLi\Model;
	use Proj\Units\Consts;
	use Proj\Others\UploaderImage;

	class Tour extends Model {
		private Table $table_program;

		public function __construct(array $tables, array $params = []) {
			[$table, $this->table_program] = $tables;
			parent::__construct($table, $params);
		}

		protected function Init(): void {
			$this->querySelect = new Select();
			$this->querySelect
				->calc("*, CONCAT(`hash`, '.', `id`, '.', `ext`) AS `cover`")
				->table($this->table->GetName())
				->where('`state` != ' . Consts\Tour::STATES['delete'])
				->order('date_create', 'DESC')
				->order('id');
		}

		public function GetItemForBrowse(int $id): array {
			return $this->table->SelectOne(null, "(`id` = {$id})", null, null, ["*, CONCAT(`hash`, '.', `id`, '.', `ext`) AS `cover`"]);
		}

		public function Create(array $data, array $params): bool {
			$program = [];
			if (isset($data['program'])) {
				$program = $data['program'];
				unset($data['program']);
			}

			$id = $this->table->Insert($data);

			$this->SaveProgram($program, $id);

			if ($_FILES['form']['tmp_name']['cover']) {
				[$hash, $ext] = $this->SaveFile($id);
				$this->table->Update(['hash' => $hash, 'ext' => $ext], "`id` = {$id}");
			}

			return true;
		}

		public function Update(array $data, int $id): bool {
			$program = [];
			if (isset($data['program'])) {
				$program = $data['program'];
				unset($data['program']);
			}

			$this->table_program->Delete("`tour_id` = {$id}");
			$this->SaveProgram($program, $id);

			if ($_FILES['form']['tmp_name']['cover']) {
				$old_file = $this->table->SelectOneFieldCalc("CONCAT(`hash`, '.', `id`, '.', `ext`) AS `cover`", 'cover', "`id` = {$id}");
				if ($old_file) {
					if (file_exists(Consts\Tour::PATH_TOUR_ORIGINAL . $old_file)) unlink(Consts\Photo::PATH_ALL_ORIGINAL . $old_file);
					if (file_exists(Consts\Tour::PATH_TOUR_PREVIEW . $old_file)) unlink(Consts\Photo::PATH_ALL_PREVIEW . $old_file);
				}

				[$data['hash'], $data['ext']] = $this->SaveFile($id);
			}

			$this->table->Update($data, "`id` = {$id}");

			return true;
		}

		private function SaveProgram(array $program, int $id): void {
			if ($program) {
				$valuesItems = [];
				foreach ($program as $item) $valuesItems[] = "({$id}, {$item['day']}, '{$item['description']}')";
				$values = implode(', ', $valuesItems);
				$this->table_program->Query("INSERT INTO `{$this->table_program->GetName()}` (`tour_id`, `day`, `description`) VALUES {$values}");
			}
		}

		private function SaveFile(int $id): array {
			$dir_original = Consts\Tour::PATH_TOUR_ORIGINAL;
			$dir_preview = Consts\Tour::PATH_TOUR_PREVIEW;

			$temp_path = $_FILES['form']['tmp_name']['cover'];
			$temp_name = $_FILES['form']['name']['cover'];

			$info = pathinfo($temp_name);
			$ext = $info['extension'];
			$hash = hash_file('md5', $temp_path);

			try {
				$IMG = new UploaderImage($temp_path, $ext);
				$IMG->Save($dir_original . '/', "{$hash}.{$id}", null, 2000, 2000, UploaderImage::SIZE_COVER);
				$IMG->Save($dir_preview . '/', "{$hash}.{$id}", null, 610, 610, UploaderImage::SIZE_COVER);
			}
			catch (\Exception) { return []; }

			return [$hash, $ext];
		}

		public function GetDescriptionByTourId($id): array {
			$result = $this->table_program->Select(['day', 'description'], "`tour_id`={$id}", '`day`');
			return $this->table_program->FetchAll($result);
		}

	}