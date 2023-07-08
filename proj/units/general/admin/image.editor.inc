<?php

	namespace Proj\Admin\Editor\General;

	use JetBrains\PhpStorm\NoReturn;

	use Base\DB\MySQLi\Table;
	use Base\Editor\EditorMySQLi;
	use Base\Editor\Skins;
	use Proj\Units\Consts;

	class Image extends EditorMySQLi {

		public function __construct(string $name, Table $table) {
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

        protected function NavigateSelect(): array {
            return [
                function () { return $this->create->GetLink('Добавить изображение', ['page' => 1]); }
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
				'id' 		    => new Skins\Browse\Text('#'),
				'alias' 		=> new Skins\Browse\Text('Псевдоним'),
				'description' 	=> new Skins\Browse\Text('Описание')
			];
		}

		protected function FieldsBrowse(array $data) : array {
			return [
				'alias'    	    => new Skins\Browse\Text('Псевдоним'),
				'description'   => new Skins\Browse\Text('Описание'),
				'cover'         => new Skins\Browse\Image('Картинка', Consts\General::PATH_IMAGE_RELATIVE)
			];
		}

		protected function Manage(): array {
			return [
				function (array $params, array $item) { return $this->update->GetLink('Изменить', ['id' => $item['id']]); },
				function (array $params, array $item) { return $this->browse->GetLink('Просмотреть', ['id' => $item['id']]); }
			];
		}

		protected function FieldsCreate(array $params): array {
            return [
                'alias' 		    => new Skins\Edit\Text('Псевдоним (неизменяемое)', 'form[alias]'),
                'description' 		=> new Skins\Edit\Text('Описание', 'form[description]'),
                'cover' 	        => new Skins\Edit\File('Фотография', 'form[cover]', 'Выберите фотографию', '.jpg, .jpeg, .png')
            ];
		}

		protected function FieldsUpdate(array $params): array {
            return [
                'alias' 		    => new Skins\Browse\Text('Псевдоним'),
                'description' 		=> new Skins\Edit\Text('Описание', 'form[description]'),
                'cover' 	        => new Skins\Edit\File('Фотография', 'form[cover]', 'Выберите фотографию', '.jpg, .jpeg, .png')
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
				$old_file = $this->table->SelectOneFieldCalc("CONCAT(`hash`, '.', `id`, '.', `ext`) AS `alias`", 'alias', "`id` = {$id}");
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