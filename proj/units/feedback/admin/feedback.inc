<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'feedback/admin/feedback.structure.inc';
//	require DIR_UNITS . 'feedback/admin/feedback.editor.inc';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
//	use Base\Editor\EditorMySQLi;
	use Proj\Admin\Structure;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Group;

	class News extends Structure\Feedback {
		use Instance;

//		private EditorMySQLi $editor_news;
//
//		private Action $out_menu;
//
//		private function __construct() {
//			parent::__construct();
//
//			$this->editor_news = new \Proj\Admin\Editor\News(self::NAME, $this->table_news);
//
//			$this->out_menu = new Action();
//
//			Controller::instance()->view->Push($this->out_menu, [$this, 'OutMenu']);
//		}

//		public function OutMenu() {
//			Layout::instance()->menu->Push(
//				Group::object()->ToVar('Новости', [
//					$this->editor_news->select->GetLink('Список новостей'),
//					$this->editor_news->create->GetLink('Добавить новость')
//				])
//			);
//		}

	}

	News::init();