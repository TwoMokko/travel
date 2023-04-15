<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'people/admin/people.structure.inc';
	require DIR_UNITS . 'people/admin/people.editor.inc';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Editor\EditorMySQLi;
	use Proj\Admin\Structure;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Group;

	class People extends Structure\People {
		use Instance;

		private EditorMySQLi $editor_people;

		private Action $out_menu;

		private function __construct() {
			parent::__construct();

			$this->editor_people = new \Proj\Admin\Editor\People(self::NAME, $this->table_people);

			$this->out_menu = new Action();

			Controller::instance()->view->Push($this->out_menu, [$this, 'OutMenu']);
		}

		public function OutMenu() {
			Layout::instance()->menu->Push(
				Group::ToVar('Люди', [
					$this->editor_people->select->GetLink('Список людей', ['page' => 1]),
					$this->editor_people->create->GetLink('Добавить человека')
				])
			);
		}

	}

	People::init();