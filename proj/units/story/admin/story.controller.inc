<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'story/admin/story.structure.inc';
	require DIR_UNITS . 'story/admin/editors/story/story.editor.inc';

	use Base\Instance;
	use Proj\Admin\Structure;
	use Proj\Admin\Editor;
	use Proj\Editor\Consts as EditorConsts;

	class Story extends Structure\Story {
		use Instance;

		public Editor\Story $editor_story;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->editor_story = new Editor\Story(EditorConsts\ID_STORY, self::NAME, $this->table_story, 'История (редактор)');
		}

	}

	Story::init();