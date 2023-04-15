<?php

	namespace Proj\Admin\Editor;

	use JetBrains\PhpStorm\NoReturn;

	use Base\DB\TableMySQLi;
	use Base\Editor\EditorMySQLi;
	use Base\Editor\Skins;
	use Proj\Units\Consts;

	class TypeTour extends EditorMySQLi {

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);
		}

		protected function Where(array $params): array {
			return [
				'`state` != ' . Consts\Tour::STATES['delete']
			];
		}

		protected function Order(): array {
			return [
				'`date_create` DESC',
				'`id` ASC'
			];
		}

		protected function Calc(): array {
			return [
				"*, CONCAT(`hash`, '.', `id`, '.', `ext`) AS `cover`"
			];
		}

		protected function RegTitles(): void {
			$this->titleSelect = 'Список типов тура';
			$this->titleCreate = 'Добавить тип тура';
			$this->titleUpdate = 'Редактирование типа тура';
			$this->titleDelete = 'Удалить тип тура?';

			$this->titleDoCreate = 'Тип тура добавлена';
			$this->titleDoUpdate = 'Тип тура изменена';
			$this->titleDoDelete = 'Тип тура удалена';
		}

		protected function FieldsSelect(array $params): array {
			return [
				'id' 				=> new Skins\Browse\Text('#'),
				'state' 			=> new Skins\Browse\ValueFromArray('Состояние', Consts\Tour::STATES_RU),
				'name' 				=> new Skins\Browse\Text('Название')
			];
		}

		protected function FieldsBrowse(array $params) : array {
			return [
				'state'    	 		=> new Skins\Browse\ValueFromArray('Состояние', Consts\Tour::STATES_RU),
				'name'    			=> new Skins\Browse\Text('Заголовок'),
				'description'     	=> new Skins\Browse\Text('Текст'),
				'cover'     		=> new Skins\Browse\Image('Картинка', Consts\Tour::PATH_TYPE_RELATIVE)
			];
		}

		protected function FieldsCreate(array $params): array {
			return [
				'state' 			=> ['skin' => 'select', 'name' => 'Состояние', 'default' => Consts\Tour::STATES['draft']],
				'name' 				=> ['skin' => 'text', 'name' => 'Заголовок', 'default' => ''],
				'description' 		=> ['skin' => 'textarea', 'name' => 'Текст', 'default' => ''],
				'cover' 			=> ['skin' => 'file', 'name' => 'Обложка', 'default' => 'Выберите обложку', 'params' => ['accept' => '.jpg, .jpeg, .png']],
			];
		}

		protected function FieldsUpdate(array $params): array {
			return [
				'state' 			=> ['skin' => 'select', 'name' => 'Состояние'],
				'name' 				=> ['skin' => 'text', 'name' => 'Заголовок'],
				'description' 		=> ['skin' => 'textarea', 'name' => 'Текст'],
				'cover' 			=> ['skin' => 'file', 'name' => 'Обложка', 'params' => ['accept' => '.jpg, .jpeg, .png']],
			];
		}

		public function PrepareOnCreate(array & $data): void {
			$data['state'] = [
				Consts\Tour::STATE_DRAFT	=> 'Черновик',
				Consts\Tour::STATE_ACTIVE	=> 'Активная',
				Consts\Tour::STATE_INACTIVE	=> 'Не активная',
			];
		}

		public function PrepareOnUpdate(int $id, array & $item, array & $data): void {
			$data['state'] = [
				Consts\Tour::STATE_DRAFT	=> 'Черновик',
				Consts\Tour::STATE_ACTIVE	=> 'Активная',
				Consts\Tour::STATE_INACTIVE	=> 'Не активная',
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
				if ($old_file) unlink(Consts\Tour::PATH_TYPE . $old_file);

				[$data['hash'], $data['ext']] = $this->SaveFile($id);
			}

			$this->table->Update($data, "`id` = {$id}");

			SendJSONSuccess(['message' => $this->titleDoUpdate, 'html' => $this->Select()]);
		}

		private function SaveFile(int $id): array {
			$temp_path = $_FILES['form']['tmp_name']['cover'];
			$temp_name = $_FILES['form']['name']['cover'];
			$dir = Consts\Tour::PATH_TYPE;
			$hash = hash_file('md5', $temp_path);
			$info = pathinfo($temp_name);
			$ext = $info['extension'];
			$name = "{$hash}.{$id}.{$ext}";

			if (!is_dir($dir)) mkdir($dir, 0777, true);
			move_uploaded_file($temp_path, $dir . $name);

			return [$hash, $ext];
		}

	}