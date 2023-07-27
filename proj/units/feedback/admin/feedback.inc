<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'feedback/admin/feedback.structure.inc';
	require DIR_UNITS . 'feedback/admin/editors/feedback.editor.inc';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Proj\Admin\Structure;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Group;
	use Proj\Admin\Editor;

	class Feedback extends Structure\Feedback {
		use Instance;

		private Editor\Feedback\Feedback $editor_feedback;

		private Action $out_menu;

		private function __construct() {
			parent::__construct();

			$this->editor_feedback = new Editor\Feedback\Feedback(self::NAME, $this->table_feedback);
			$this->out_menu = new Action();

			Controller::instance()->view->Push($this->out_menu, [$this, 'OutMenu']);
		}

		public function OutMenu() {
			Layout::instance()->menu->Push(
				Group::ToVar('Обратная связь', [
					$this->editor_feedback->select->GetLink('Список', ['page' => 1])
				])
			);
		}

	}

	Feedback::init();