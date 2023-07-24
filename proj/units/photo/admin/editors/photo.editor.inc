<?php

	namespace Proj\Admin\Editor\Photo;

	require DIR_UNITS . 'photo/admin/editors/photo.editor.model.inc';

	use Base\Action;
	use Base\Controller;
	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins;
	use JetBrains\PhpStorm\NoReturn;
	use Proj\Admin\Units;
	use Proj\Admin\Editor\Model;
	use Proj\Others\UploaderImage;
	use Proj\Units\Consts;

	class Photo extends Editor {
		private Action $photo_load;
		private Action $photo_del;

		public function __construct(string $name, /* @var Table $tables */ array $tables) {
			parent::__construct($name);

			$this->titleSelect = 'Список альбомов';
			$this->titleCreate = 'Добавить альбом';
			$this->titleUpdate = 'Редактирование альбома';
			$this->titleDelete = 'Удалить альбом?';

			$this->titleDoCreate = 'Альбом добавлен';
			$this->titleDoUpdate = 'Альбом изменен';
			$this->titleDoDelete = 'Альбом удален';

			$this->model = new Model\Photo($tables, $this->params);

			$this->photo_load = new Action($name, 'load', "/{$name}/load?uid=%uid%&id=%id%");
			$this->photo_del = new Action($name, 'del', "/{$name}/del");

			Controller::instance()->work->Push($this->photo_load, [$this, 'PhotoLoad']);
			Controller::instance()->work->Push($this->photo_del, [$this, 'PhotoDel']);
		}

		protected function SetHandlers(): void {
			Controller::instance()->view->Push($this->select, [$this, 'OnSelect']);
			Controller::instance()->view->Push($this->browse, [$this, 'OnBrowse']);
			Controller::instance()->view->Push($this->create, [$this, 'OnCreate']);
			Controller::instance()->view->Push($this->update, [$this, 'OnUpdate']);

			Controller::instance()->view->Push($this->do_create, [$this, 'DoCreate']);
			Controller::instance()->view->Push($this->do_update, [$this, 'DoUpdate']);
			Controller::instance()->view->Push($this->do_delete, [$this, 'DoDelete']);
		}

		protected function FieldsSelect(): array {
			return [
				'id' 		=> new Skins\Browse\Text('#'),
				'state' 	=> new Skins\Browse\ValueFromArray('Состояние', Consts\Photo::STATES_RU),
				'header' 	=> new Skins\Browse\Text('Заголовок')
			];
		}

		protected function FieldsBrowse() : array {
			return [
				'state'     => new Skins\Browse\ValueFromArray('Состояние', Consts\Photo::STATES_RU),
				'header'    => new Skins\Browse\Text('Заголовок'),
				'cover'     => new Skins\Browse\Image('Картинка', Consts\Photo::PATH_ALL_RELATIVE)
			];
		}

		protected function ManageSelect(): array {
			return [
				function (array $item) { return $this->update->GetLink('Изменить', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->browse->GetLink('Просмотреть', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->delete->GetLink('Удалить', array_merge(['id' => $item['id']], $this->params)); },
			];
		}

		protected function FieldsCreate(): array {
			$uid = uniqid();

			$states = [
				Consts\Photo::STATE_DRAFT => Consts\Photo::STATES_RU[Consts\Photo::STATE_DRAFT],
				Consts\Photo::STATE_ACTIVE => Consts\Photo::STATES_RU[Consts\Photo::STATE_ACTIVE],
				Consts\Photo::STATE_INACTIVE => Consts\Photo::STATES_RU[Consts\Photo::STATE_INACTIVE],
			];

			return [
				'uid' 		=> new Skins\Edit\Hidden('uid', 'uid', $uid),
				'state' 	=> new Skins\Edit\Select('Состояние','form[state]',  $states),
				'header' 	=> new Skins\Edit\Text('Заголовок', 'form[header]'),
				'cover' 	=> new Skins\Edit\File('Обложка','form[cover]',  'Выберите обложку', '.jpg, .jpeg, .png'),
				'photos' 	=> new Skins\Edit\Uploader('Фотографии','photos',  $this->photo_load->GetHref(['uid' => $uid, 'id' => 0]), $this->photo_del->GetHref(), '', 'Выберите фотографии', '.jpg, .jpeg, .png')
			];
		}

		protected function FieldsUpdate(): array {
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
				'photos' 	=> new Skins\Edit\Uploader('Фотографии', 'photos', $this->photo_load->GetHref(['uid' => '', 'id' => $id]), $this->photo_del->GetHref(),  Consts\Photo::PATH_SHOW_RELATIVE_PREVIEW, 'Выберите фотографии', '.jpg, .jpeg, .png', $photos)
			];
		}

		protected function PrepareDoCreate(array & $data, array & $params): void {
			$params['uid'] = GetParam('uid');
		}
		#[NoReturn] public function PhotoLoad(): void {
			$uid = GetParam('uid', '');
			$id_album = GetParam('id', 0);

			$this->model->Cron();
			$id = $this->model->PhotoLoad($uid, $id_album);

			if (!$id) SendJSONSuccess(['action' => 'error', 'text' => 'Изображение не загружено']);

			SendJSONSuccess(['action' => 'ok', 'id' => $id]);
		}

		#[NoReturn] public function PhotoDel(): void {
			$id = GetParam('id');

			$this->model->PhotoDel($id);

			SendJSONSuccess([]);
		}

	}