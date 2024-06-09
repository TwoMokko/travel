<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'photo/admin/photo.structure.inc';
	require DIR_UNITS . 'photo/admin/photo.model.inc';

	require DIR_UNITS . 'photo/admin/editors/photo/photo.editor.inc';

	use Base\Instance;
	use Proj\Admin\Structure;
	use Proj\Admin\Model;
	use Proj\Admin\Editor;
	use Proj\Editor\Consts as EditorConsts;

	class Photo extends Structure\Photo {
		use Instance;

		public Model\Photo $model;

		public Editor\Photo\Photo $editor_photo;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->model = Model\Photo::instance();
			$this->model->AcceptTables([$this->table_photo_all, $this->table_photo_show]);

			$this->editor_photo = new Editor\Photo\Photo(EditorConsts\ID_PHOTO, self::NAME, [$this->table_photo_all, $this->table_photo_show], 'Фотоальбом (редактор)');
		}

	}

	Photo::init();