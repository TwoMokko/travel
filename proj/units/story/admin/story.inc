<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'story/admin/story.structure.inc';
	require DIR_UNITS . 'story/admin/editors/story.editor.inc';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Proj\Admin\Structure;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Group;
	use Proj\Admin\Editor;

	class Story extends Structure\Story {
		use Instance;

			private Editor\Story\Story $editor_story;

			private Action $out_menu;

			private function __construct() {
				parent::__construct();

				$this->editor_story = new Editor\Story\Story(self::NAME, $this->table_story);

				$this->out_menu = new Action();

				Controller::instance()->view->Push($this->out_menu, [$this, 'OutMenu']);
			}

			public function OutMenu() {
				Layout::instance()->menu->Push(
					Group::ToVar('Истории', [
						$this->editor_story->select->GetLink('Список историй', ['page' => 1]),
						$this->editor_story->create->GetLink('Добавить историю')
					])
				);
			}

	}

	Story::init();