<?php

	namespace Proj\Admin\Editor\Photo;

	require DIR_UNITS . 'photo/admin/editors/photo/photo.editor.model.inc';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Controller;
	use Base\ActionRight;
	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins;
	use Base\Helper\Response;
	use Proj\Admin\Units;
	use Proj\Units\Consts;
	use Proj\Admin\Editor\Model;
	use Closure;

	class Photo extends Editor {
		private ActionRight $photo_load;
		private ActionRight $photo_del;

		public function __construct(int $id, string $name, /** @var Table[] $tables */ $tables, string $title = '') {
			parent::__construct($id, $name, $tables[0], $title);

			$this->titleSelect = 'Список альбомов';
			$this->titleCreate = 'Добавить альбом';
			$this->titleUpdate = 'Редактирование альбома';
			$this->titleDelete = 'Удалить альбом?';

			$this->titleDoCreate = 'Альбом добавлен';
			$this->titleDoUpdate = 'Альбом изменен';
			$this->titleDoDelete = 'Альбом удален';

			$this->model = new Model\Photo($tables, $this->params);
		}

		protected function RegActions(): void {
			parent::RegActions();

			$this->photo_load = new ActionRight($this->id, $this->name, 'load', "/{$this->name}/load?uid=%uid%&id=%id%");
			$this->photo_del = new ActionRight($this->id, $this->name, 'del', "/{$this->name}/del");
		}

		protected function SetHandlers(): void {
			parent::SetHandlers();

			Controller::$view->Push([Controller::ENTRY_XHR], $this->photo_load, Closure::fromCallable([$this, 'PhotoLoad']));
			Controller::$view->Push([Controller::ENTRY_XHR], $this->photo_del, Closure::fromCallable([$this, 'PhotoDel']));
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
				'cover'     => new Skins\Browse\Image('Картинка', Consts\Photo::PATH_ALL_PREVIEW_RELATIVE)
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
			$photos = Units\Photo::instance()->model->GetPhotoShow($id);

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

		#[NoReturn] public function PhotoLoad(): void {
			$uid = GetParam('uid', '');
			$id_album = GetParam('id', 0);

			$this->model->Cron();
			[$id, $error] = $this->model->PhotoLoad($uid, $id_album);

			if (!$id) Response::SendNoticeError("Изображение не загружено ({$error})");

			Response::SendJSONData(['id' => $id]);
		}

		#[NoReturn] public function PhotoDel(): void {
			$id = GetParam('id');

			$this->model->PhotoDel($id);

			Response::SendJSONData([]);
		}

	}