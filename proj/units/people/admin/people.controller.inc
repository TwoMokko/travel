<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'people/admin/people.structure.inc';
	require DIR_UNITS . 'people/admin/editors/people/people.editor.inc';

	use Base\Instance;
	use Proj\Admin\Structure;
	use Proj\Admin\Editor;
	use Proj\Editor\Consts as EditorConsts;

	class People extends Structure\People {
		use Instance;

		public Editor\People $editor_people;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->editor_people = new Editor\People(EditorConsts\ID_PEOPLE, self::NAME, $this->table_people, 'Люди (редактор)');
		}

	}

	People::init();