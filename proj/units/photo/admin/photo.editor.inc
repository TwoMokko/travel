<?php

	namespace Proj\Admin\Editor;

	use Base\Action;
    use Base\Controller;
    use JetBrains\PhpStorm\NoReturn;

	use Base\DB\TableMySQLi;
	use Base\Editor\EditorMySQLi;
	use Base\Editor\Skins;
	use Proj\Units\Consts;

	class Photo extends EditorMySQLi {
        private TableMySQLi $table_show;
        private Action $photo_load;
        private Action $photo_del;

		public function __construct(string $name, array $tables) {
            [$table, $this->table_show] = $tables;
            $this->photo_load = new Action($name, 'load', "/{$name}/load?uid=%uid%");
            $this->photo_del = new Action($name, 'del', "/{$name}/del");

            parent::__construct($name, $table);

            Controller::instance()->work->Push($this->photo_load, [$this, 'PhotoLoad']);
            Controller::instance()->work->Push($this->photo_del, [$this, 'PhotoDel']);
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
				'photos' => new Skins\Edit\Uploader('photos', 'Фотографии', $this->photo_load->GetHref(['uid' => $uid]), $this->photo_del->GetHref(), '', 'Выберите фотографии', '.jpg, .jpeg, .png')
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
            $uid = GetParam('uid');

			$id = $this->table->Insert($data);

			if ($_FILES['form']['tmp_name']['cover']) {
				[$hash, $ext] = $this->SaveFile($id);
				$this->table->Update(['hash' => $hash, 'ext' => $ext], "`id` = {$id}");
			}

            $this->table_show->Update(['all_id' => $id, 'u_id' => ''], "`u_id` = '{$uid}'");

			SendJSONSuccess(['message' => $this->titleDoCreate, 'html' => $this->Select()]);
		}

		#[NoReturn] public function DoUpdate(): void {
			$id = (int)GetParam('id', 0);
			$data = GetParam('form', []);

			if ($_FILES['form']['tmp_name']['cover']) {
				$old_file = $this->table->SelectOneFieldCalc("CONCAT(`hash`, '.', `id`, '.', `ext`) AS `name`", 'name', "`id` = {$id}");
				if ($old_file) unlink(Consts\Photo::PATH_COVER . $old_file);

				[$data['hash'], $data['ext']] = $this->SaveFile($id);
			}

			$this->table->Update($data, "`id` = {$id}");

			SendJSONSuccess(['message' => $this->titleDoUpdate, 'html' => $this->Select()]);
		}

		private function SaveFile(int $id): array {
			$temp_path = $_FILES['form']['tmp_name']['cover'];
			$temp_name = $_FILES['form']['name']['cover'];
			$dir = Consts\Photo::PATH_COVER;
			$hash = hash_file('md5', $temp_path);
			$info = pathinfo($temp_name);
			$ext = $info['extension'];
			$name = "{$hash}.{$id}.{$ext}";

			if (!is_dir($dir)) mkdir($dir, 0777, true);
			move_uploaded_file($temp_path, $dir . $name);

			return [$hash, $ext];
		}

        #[NoReturn] public function PhotoLoad(): void {
            $result = $this->table_show->Select(['id'],"`date_create` < DATE_SUB(NOW(), INTERVAL 1 MONTH) AND `all_id` = 0", null, null, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `name`"]);
            while ($row = $this->table_show->Fetch($result)) {
                $dir = Consts\Photo::PATH_SHOW;

                unlink($dir . $row['name']);
                $this->table_show->Delete("`id` = {$row['id']}");
            }


            $uid = GetParam('uid');

            $temp_path = $_FILES['file']['tmp_name'];
            $temp_name = $_FILES['file']['name'];
            $dir = Consts\Photo::PATH_SHOW;
            $hash = hash_file('md5', $temp_path);
            $info = pathinfo($temp_name);
            $ext = $info['extension'];

            $id = $this->table_show->Insert([
                'u_id' => $uid,
                'state' => Consts\Photo::STATE_ACTIVE,
                'hash' => $hash,
                'ext' => $ext
            ]);

            $name = "{$hash}.{$id}.{$ext}";

            if (!is_dir($dir)) mkdir($dir, 0777, true);
            move_uploaded_file($temp_path, $dir . $name);

            SendJSONSuccess(['id' => $id]);
        }

        #[NoReturn] public function PhotoDel(): void {
            $id = GetParam('id');
            $dir = Consts\Photo::PATH_SHOW;
            $name = $this->table_show->SelectOneFieldCalc("CONCAT(`hash`, '.', `id`, '.', `ext`) AS `name`", 'name', "`id` = {$id}");

            unlink($dir . $name);
            $this->table_show->Delete("`id` = {$id}");

            SendJSONSuccess([]);
        }

	}