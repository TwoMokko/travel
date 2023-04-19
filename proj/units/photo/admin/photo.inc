<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'photo/admin/photo.structure.inc';
	require DIR_UNITS . 'photo/admin/photo.editor.inc';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Editor\EditorMySQLi;
	use Proj\Admin\Structure;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Group;

	class Photo extends Structure\Photo {
		use Instance;

		private EditorMySQLi $editor_photo;

		private Action $out_menu;

		private function __construct() {
			parent::__construct();

			$this->editor_photo = new \Proj\Admin\Editor\Photo(self::NAME, [$this->table_photo_all, $this->table_photo_show]);

			$this->out_menu = new Action();

			Controller::instance()->view->Push($this->out_menu, [$this, 'OutMenu']);
		}

		public function OutMenu() {
			Layout::instance()->menu->Push(
				Group::ToVar('Фотоальбомы', [
					$this->editor_photo->select->GetLink('Список фотоальбомов', ['page' => 1]),
					$this->editor_photo->create->GetLink('Добавить фотоальбом')
				])
			);
		}

        public function GetPhotoShow(int $id_album): array {
            $result = $this->table_photo_show->Select(['id'], "`all_id` = {$id_album}", null, null, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
            return $this->table_photo_show->FetchAll($result);
        }
	}

	Photo::init();