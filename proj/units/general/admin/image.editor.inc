<?php

	namespace Proj\Admin\Editor\General;

	use JetBrains\PhpStorm\NoReturn;

	use Base\DB\TableMySQLi;
	use Base\Editor\EditorMySQLi;
	use Base\Editor\Skins;
	use Proj\Admin\Units;
	use Proj\Units\Consts;

	class Image extends EditorMySQLi {

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);
		}

		protected function Where(array $params): array {
			return [
				'`state` != ' . Consts\General::STATE_DELETE
			];
		}

		protected function Order(): array {
			return [
				'`id` ASC'
			];
		}

		protected function Calc(): array {
			return [
				"*, CONCAT(`hash`, '.', `id`, '.', `ext`) AS `cover`"
			];
		}

		protected function RegTitles(): void {
			$this->titleSelect = 'Список изображений';
			$this->titleCreate = 'Добавить изображение';
			$this->titleUpdate = 'Редактирование изображения';
			$this->titleDelete = 'Удалить изображение?';

			$this->titleDoCreate = 'Изображение добавлено';
			$this->titleDoUpdate = 'Изображение изменено';
			$this->titleDoDelete = 'Изображение удалено';
		}

		protected function FieldsSelect(array $params): array {
			return [
				'id' 		=> new Skins\Browse\Text('#'),
//				'state' 	=> new Skins\Browse\ValueFromArray('Состояние', Consts\General::STATES_RU),
				'name' 		=> new Skins\Browse\Text('Имя')
			];
		}

		protected function FieldsBrowse(array $data) : array {
			return [
//				'state'     => new Skins\Browse\ValueFromArray('Состояние', Consts\General::STATES_RU),
				'name'    	=> new Skins\Browse\Text('Имя'),
				'cover'     => new Skins\Browse\Image('Картинка', Consts\General::PATH_IMAGE_RELATIVE)
			];
		}

		protected function Manage(): array {
			return [
				function (array $params, array $item) { return $this->update->GetLink('Изменить', ['id' => $item['id']]); },
//				function (array $params, array $item) { return $this->do_delete->GetLink('Удалить', ['id' => $item['id']]); },
				function (array $params, array $item) { return $this->browse->GetLink('Просмотреть', ['id' => $item['id']]); }
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
//                'state' 	=> new Skins\Edit\Select('Состояние', 'form[state]', $states),
                'name' 		=> new Skins\Edit\Text('Имя', 'form[name]'),
                'cover' 	=> new Skins\Edit\File('Фотография', 'form[cover]', 'Выберите фотографию', '.jpg, .jpeg, .png')
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

			if ($_FILES['form']['tmp_name']['cover']) {
				[$hash, $ext] = $this->SaveFile($id);
				$this->table->Update(['hash' => $hash, 'ext' => $ext], "`id` = {$id}");
			}

			SendJSONSuccess(['message' => $this->titleDoCreate, 'html' => $this->Select()]);
		}

		#[NoReturn] public function DoUpdate(): void {
			$id = (int)GetParam('id', 0);
			$data = GetParam('form', []);

			if ($_FILES['form']['tmp_name']['cover']) {
				$old_file = $this->table->SelectOneFieldCalc("CONCAT(`hash`, '.', `id`, '.', `ext`) AS `name`", 'name', "`id` = {$id}");
				if ($old_file) unlink(Consts\General::PATH_IMAGE . $old_file);

				[$data['hash'], $data['ext']] = $this->SaveFile($id);
			}

			$this->table->Update($data, "`id` = {$id}");

			SendJSONSuccess(['message' => $this->titleDoUpdate, 'html' => $this->Select()]);
		}

		private function SaveFile(int $id): array {
			$temp_path = $_FILES['form']['tmp_name']['cover'];
			$temp_name = $_FILES['form']['name']['cover'];
			$dir = Consts\General::PATH_IMAGE;
			$hash = hash_file('md5', $temp_path);
			$info = pathinfo($temp_name);
			$ext = $info['extension'];
			$name = "{$hash}.{$id}.{$ext}";

			if (!is_dir($dir)) mkdir($dir, 0777, true);
			move_uploaded_file($temp_path, $dir . $name);

			return [$hash, $ext];
		}

	}