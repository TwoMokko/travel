<?php

	namespace Proj\Admin\Editor\General;

	use JetBrains\PhpStorm\NoReturn;

	use Base\DB\TableMySQLi;
	use Base\Editor\EditorMySQLi;
	use Base\Editor\Skins;
	use Proj\Admin\Units;
	use Proj\Units\Consts;

	class Text extends EditorMySQLi {

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);
		}

		protected function Where(array $params): array {
			return [
				'`state` != ' . Consts\General::STATES['delete']
			];
		}

		protected function Order(): array {
			return [
				'`id` ASC'
			];
		}

//		protected function Calc(): array {
//			return [
//				"*, CONCAT(`hash`, '.', `id`, '.', `ext`) AS `cover`"
//			];
//		}

		protected function RegTitles(): void {
			$this->titleSelect = 'Список текстов';
			$this->titleCreate = 'Добавить текст';
			$this->titleUpdate = 'Редактирование текста';
			$this->titleDelete = 'Удалить текст?';

			$this->titleDoCreate = 'Текст добавлено';
			$this->titleDoUpdate = 'Текст изменено';
			$this->titleDoDelete = 'Текст удалено';
		}

		protected function FieldsSelect(array $params): array {
			return [
				'id' 		=> new Skins\Browse\Text('#'),
				'state' 	=> new Skins\Browse\ValueFromArray('Состояние', Consts\General::STATES_RU),
				'alias' 	=> new Skins\Browse\Text('Имя')
			];
		}

		protected function FieldsBrowse(array $data) : array {
			return [
				'state'     => new Skins\Browse\ValueFromArray('Состояние', Consts\General::STATES_RU),
				'alias'    	=> new Skins\Browse\Text('Имя'),
				'text'    	=> new Skins\Browse\Text('Текст')
			];
		}

		protected function FieldsCreate(array $params): array {
            return $this->FieldsCreateAndUpdate($params);
		}

		protected function FieldsUpdate(array $params): array {
            return $this->FieldsCreateAndUpdate($params);
		}

        private function FieldsCreateAndUpdate(array $params): array {
            $states = [
                Consts\General::STATE_DRAFT => Consts\General::STATES_RU[Consts\People::STATE_DRAFT],
                Consts\General::STATE_ACTIVE => Consts\General::STATES_RU[Consts\People::STATE_ACTIVE],
                Consts\General::STATE_INACTIVE => Consts\General::STATES_RU[Consts\People::STATE_INACTIVE],
            ];

            return [
                'state' 	=> new Skins\Edit\Select('Состояние', 'form[state]', $states),
                'alias' 		=> new Skins\Edit\Text('Имя', 'form[alias]'),
                'text' 		=> new Skins\Edit\TextArea('Текст', 'form[text]')
            ];
        }

		public function PrepareOnUpdate(int $id, array & $item, array & $data): void {
			$data['state'] = [
				Consts\General::STATE_DRAFT	=> 'Черновик',
				Consts\General::STATE_ACTIVE	=> 'Активная',
				Consts\General::STATE_INACTIVE	=> 'Не активная',
			];
		}

		#[NoReturn] public function DoCreate(): void {
			$data = GetParam('form', []);

			$id = $this->table->Insert($data);

//			if ($_FILES['form']['tmp_name']['cover']) {
//				[$hash, $ext] = $this->SaveFile($id);
//				$this->table->Update(['hash' => $hash, 'ext' => $ext], "`id` = {$id}");
//			}

			SendJSONSuccess(['message' => $this->titleDoCreate, 'html' => $this->Select()]);
		}

		#[NoReturn] public function DoUpdate(): void {
			$id = (int)GetParam('id', 0);
			$data = GetParam('form', []);

//			if ($_FILES['form']['tmp_name']['cover']) {
//				$old_file = $this->table->SelectOneFieldCalc("CONCAT(`hash`, '.', `id`, '.', `ext`) AS `name`", 'name', "`id` = {$id}");
//				if ($old_file) unlink(Consts\General::PATH_HEADER . $old_file);
//
//				[$data['hash'], $data['ext']] = $this->SaveFile($id);
//			}

			$this->table->Update($data, "`id` = {$id}");

			SendJSONSuccess(['message' => $this->titleDoUpdate, 'html' => $this->Select()]);
		}

//		private function SaveFile(int $id): array {
//			$temp_path = $_FILES['form']['tmp_name']['cover'];
//			$temp_name = $_FILES['form']['name']['cover'];
//			$dir = Consts\General::PATH_HEADER;
//			$hash = hash_file('md5', $temp_path);
//			$info = pathinfo($temp_name);
//			$ext = $info['extension'];
//			$name = "{$hash}.{$id}.{$ext}";
//
//			if (!is_dir($dir)) mkdir($dir, 0777, true);
//			move_uploaded_file($temp_path, $dir . $name);
//
//			return [$hash, $ext];
//		}

	}