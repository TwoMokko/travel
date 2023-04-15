<?php

	namespace Proj\Admin\Editor;

	use JetBrains\PhpStorm\NoReturn;

	use Base\DB\TableMySQLi;
	use Base\Editor\EditorMySQLi;
	use Base\Editor\Skins;
	use Proj\Units\Consts;

	class Photo extends EditorMySQLi {

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);
		}

		protected function Where(array $params): array {
			return [
				'`state` != ' . Consts\Photo::STATES['delete']
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
			$this->titleSelect = 'Список альбомов';
			$this->titleCreate = 'Добавить альбом';
			$this->titleUpdate = 'Редактирование альбома';
			$this->titleDelete = 'Удалить альбом?';

			$this->titleDoCreate = 'Альбом добавлен';
			$this->titleDoUpdate = 'Альбом изменен';
			$this->titleDoDelete = 'Альбом удален';
		}

		protected function FieldsSelect(array $params): array {
			return [
				'id' 		=> new Skins\Browse\Text('#'),
				'state' 	=> new Skins\Browse\ValueFromArray('Состояние', Consts\Photo::STATES_RU),
				'header' 	=> new Skins\Browse\Text('Заголовок')
			];
		}

		protected function FieldsBrowse(array $params) : array {
			return [
				'state'     => new Skins\Browse\ValueFromArray('Состояние', Consts\Photo::STATES_RU),
				'header'    => new Skins\Browse\Text('Заголовок'),
				'cover'     => new Skins\Browse\Image('Картинка', Consts\Photo::PATH_ALL_RELATIVE)
			];
		}

		protected function FieldsCreate(array $params): array {
			$uid = uniqid();

			$states = [
				Consts\Photo::STATE_DRAFT => Consts\Photo::STATES_RU[Consts\Photo::STATE_DRAFT],
				Consts\Photo::STATE_ACTIVE => Consts\Photo::STATES_RU[Consts\Photo::STATE_ACTIVE],
				Consts\Photo::STATE_INACTIVE => Consts\Photo::STATES_RU[Consts\Photo::STATE_INACTIVE],
			];

			return [
				'uid' => new Skins\Edit\Hidden('uid', 'UID', $uid),
				'state' => new Skins\Edit\Select('form[state]', 'Состояние', $states),
				'header' => new Skins\Edit\Text('form[header]', 'Заголовок'),
				'cover' => new Skins\Edit\File('form[cover]', 'Обложка', 'Выберите обложку', '.jpg, .jpeg, .png'),
				'photos' => new Skins\Edit\Uploader('photos', 'Фотографии', 'Выберите фотографии', '.jpg, .jpeg, .png', ['uid' => $uid])
			];
		}

		protected function FieldsUpdate(array $params): array {
			$states = [
				Consts\Photo::STATE_DRAFT => Consts\Photo::STATES_RU[Consts\Photo::STATE_DRAFT],
				Consts\Photo::STATE_ACTIVE => Consts\Photo::STATES_RU[Consts\Photo::STATE_ACTIVE],
				Consts\Photo::STATE_INACTIVE => Consts\Photo::STATES_RU[Consts\Photo::STATE_INACTIVE],
			];

			return [
				'state' => new Skins\Edit\Select('form[state]', 'Состояние', $states),
				'header' => new Skins\Edit\Text('form[header]', 'Заголовок'),
				'cover' => new Skins\Edit\File('form[cover]', 'Обложка', 'Выберите обложку', '.jpg, .jpeg, .png'),
//				'photos' => new Skins\Edit\Uploader('photos', 'Фотографии', 'Выберите фотографии', '.jpg, .jpeg, .png')
			];
//			return [
//				'state' => ['skin' => 'select', 'name' => 'Состояние'],
//				'header' => ['skin' => 'text', 'name' => 'Заголовок'],
//				'cover' => ['skin' => 'file', 'name' => 'Обложка', 'params' => ['accept' => '.jpg, .jpeg, .png']],
//			];
		}

		public function PrepareOnCreate(array & $data): void {
			$data['state'] = [
				Consts\Photo::STATE_DRAFT	=> 'Черновик',
				Consts\Photo::STATE_ACTIVE	=> 'Активная',
				Consts\Photo::STATE_INACTIVE	=> 'Не активная',
			];
		}

		public function PrepareOnUpdate(int $id, array & $item, array & $data): void {
			$data['state'] = [
				Consts\Photo::STATE_DRAFT	=> 'Черновик',
				Consts\Photo::STATE_ACTIVE	=> 'Активная',
				Consts\Photo::STATE_INACTIVE	=> 'Не активная',
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
				if ($old_file) unlink(Consts\Photo::PATH_ALL . $old_file);

				[$data['hash'], $data['ext']] = $this->SaveFile($id);
			}

			$this->table->Update($data, "`id` = {$id}");

			SendJSONSuccess(['message' => $this->titleDoUpdate, 'html' => $this->Select()]);
		}

		private function SaveFile(int $id): array {
			$temp_path = $_FILES['form']['tmp_name']['cover'];
			$temp_name = $_FILES['form']['name']['cover'];
			$dir = Consts\Photo::PATH_ALL;
			$hash = hash_file('md5', $temp_path);
			$info = pathinfo($temp_name);
			$ext = $info['extension'];
			$name = "{$hash}.{$id}.{$ext}";

			if (!is_dir($dir)) mkdir($dir, 0777, true);
			move_uploaded_file($temp_path, $dir . $name);

			return [$hash, $ext];
		}

	}