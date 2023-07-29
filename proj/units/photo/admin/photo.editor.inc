<?php

	namespace Proj\Admin\Editor;

	use Base\Action;
    use Base\Controller;
    use JetBrains\PhpStorm\NoReturn;

	use Base\DB\MySQLi\Table;
	use Base\Editor\EditorMySQLi;
	use Base\Editor\Skins;
	use Proj\Admin\Units;
	use Proj\Others\UploaderImage;
	use Proj\Units\Consts;

	class Photo extends EditorMySQLi {
        private Table $table_show;
        private Action $photo_load;
        private Action $photo_del;

		public function __construct(string $name, array $tables) {
            [$table, $this->table_show] = $tables;
            $this->photo_load = new Action($name, 'load', "/{$name}/load?uid=%uid%&id=%id%");
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

		protected function FieldsBrowse(array $data) : array {
			return [
				'state'     => new Skins\Browse\ValueFromArray('Состояние', Consts\Photo::STATES_RU),
				'header'    => new Skins\Browse\Text('Заголовок'),
				'cover'     => new Skins\Browse\Image('Картинка', Consts\Photo::PATH_ALL_PREVIEW_RELATIVE)
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
				'uid' 		=> new Skins\Edit\Hidden('uid', 'UID', $uid),
				'state' 	=> new Skins\Edit\Select('Состояние','form[state]',  $states),
				'header' 	=> new Skins\Edit\Text('Заголовок', 'form[header]'),
				'cover' 	=> new Skins\Edit\File('Обложка','form[cover]',  'Выберите обложку', '.jpg, .jpeg, .png'),
				'photos' 	=> new Skins\Edit\Uploader('Фотографии','photos',  $this->photo_load->GetHref(['uid' => $uid, 'id' => 0]), $this->photo_del->GetHref(), '', 'Выберите фотографии', '.jpg, .jpeg, .png')
			];
		}

		protected function FieldsUpdate(array $params): array {
            $id = GetParam('id');
            $photos = Units\Photo::instance()->GetPhotoShow($id);

			$states = [
				Consts\Photo::STATE_DRAFT => Consts\Photo::STATES_RU[Consts\Photo::STATE_DRAFT],
				Consts\Photo::STATE_ACTIVE => Consts\Photo::STATES_RU[Consts\Photo::STATE_ACTIVE],
				Consts\Photo::STATE_INACTIVE => Consts\Photo::STATES_RU[Consts\Photo::STATE_INACTIVE],
			];

			return [
				'state' 	=> new Skins\Edit\Select('Состояние', 'form[state]', $states),
				'header' 	=> new Skins\Edit\Text('Заголовок', 'form[header]'),
				'cover' 	=> new Skins\Edit\File('Обложка', 'form[cover]', 'Выберите обложку', '.jpg, .jpeg, .png'),
                'photos' 	=> new Skins\Edit\Uploader('Фотографии', 'photos', $this->photo_load->GetHref(['uid' => '', 'id' => $id]), $this->photo_del->GetHref(),  Consts\Photo::PATH_SHOW_RELATIVE, 'Выберите фотографии', '.jpg, .jpeg, .png', $photos)
			];
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
				if ($old_file && file_exists(Consts\Photo::PATH_COVER . $old_file)) unlink(Consts\Photo::PATH_COVER . $old_file);

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
                unlink(Consts\Photo::PATH_SHOW_ORIGINAL . $row['name']);
                unlink(Consts\Photo::PATH_SHOW_PREVIEW . $row['name']);
                $this->table_show->Delete("`id` = {$row['id']}");
            }

            $uid = GetParam('uid', '');
            $id_album = GetParam('id', 0);

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
				$IMG->Save(Consts\Photo::PATH_SHOW_ORIGINAL . '/', "{$hash}.{$id}");
				$IMG->Save(Consts\Photo::PATH_SHOW_PREVIEW . '/', "{$hash}.{$id}", null, 500, 500, UploaderImage::SIZE_COVER);
			}
			catch (\Exception) { SendJSONSuccess(['action' => 'error', 'text' => 'Изображение не загружено']); }

            SendJSONSuccess(['action' => 'ok', 'id' => $id]);
        }

        #[NoReturn] public function PhotoDel(): void {
            $id = GetParam('id');
            $dir_orig = Consts\Photo::PATH_SHOW_ORIGINAL;
            $dir_preview = Consts\Photo::PATH_SHOW_PREVIEW;
            $name = $this->table_show->SelectOneFieldCalc("CONCAT(`hash`, '.', `id`, '.', `ext`) AS `name`", 'name', "`id` = {$id}");

            if (file_exists($dir_orig . $name)) unlink($dir_orig . $name);
            if (file_exists($dir_preview . $name)) unlink($dir_preview . $name);
            $this->table_show->Delete("`id` = {$id}");

            SendJSONSuccess([]);
        }

	}