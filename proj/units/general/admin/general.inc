<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'general/admin/general.structure.inc';
	require DIR_UNITS . 'general/admin/views/group.tpl';
	require DIR_UNITS . 'general/admin/editors/image/image.editor.inc';
	require DIR_UNITS . 'general/admin/editors/text/text.editor.inc';

	use JetBrains\PhpStorm\NoReturn;

	use Proj\Admin\Structure;
	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Proj\DBObject;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Item;
	use Proj\Admin\Templates\General\Group;
	use Proj\Admin\Editor;

	class General extends Structure\General {
		use Instance;

		private DBObject $db;
		private Editor\General\Image $editor_image;
		private Editor\General\Text $editor_text;

		private Action $site;
		private Action $out_head;
		private Action $out_menu;
		private Action $out_footer;
		private Action $db_struct;
		private Action $db_check;
		private Action $db_make;

		private function __construct() {
			parent::__construct();
			$this->db = DBObject::instance();
			$this->editor_image = new Editor\General\Image(self::NAME . '_image', $this->table_image);
			$this->editor_text = new Editor\General\Text(self::NAME . '_text', $this->table_text);

			$this->out_head 	= new Action();
			$this->out_menu 	= new Action();
			$this->out_footer 	= new Action();
			$this->site			= new Action('', '', '/');
			$this->db_struct 	= new Action('db', 'struct', '#', /** @lang JavaScript */ "console.log('struct'); return false;");
			$this->db_check 	= new Action('db', 'check', 'admin/db/check', /** @lang JavaScript */ "Base.Common.Query.Send('/db/check', Admin.General.Render.CheckDB); return false;");
			$this->db_make 		= new Action('db', 'make', 'admin/db/make', /** @lang JavaScript */ "Base.Common.Query.Send('/db/make', Admin.General.Render.CheckDB); return false;");

			Controller::instance()->view->Push($this->out_head, [$this, 'OutHead']);
			Controller::instance()->view->Push($this->out_menu, [$this, 'OutMenu']);
			Controller::instance()->view->Push($this->out_footer, [$this, 'OutFooter']);
			Controller::instance()->view->Push($this->db_check, [$this, 'Check']);
			Controller::instance()->view->Push($this->db_make, [$this, 'Make']);
		}

		public function OutHead() {
			Layout::instance()->header->Push('Привет, админ');
		}

		public function OutMenu() {
			Layout::instance()->menu->Push(Item::ToVar('<a href = "/" target = "blank">Открыть сайт</a>'));
			Layout::instance()->menu->Push(
				Group::ToVar('База данных', [
					$this->db_struct->GetLink('Структура'),
					$this->db_check->GetLink('Проверить')
				])
			);
			Layout::instance()->menu->Push(
				Group::ToVar('Изображения и текста', [
					$this->editor_image->select->GetLink('Список изображений', ['page' => 1]),
					$this->editor_text->select->GetLink('Список текстов', ['page' => 1]),
				])
			);
		}

		public function OutFooter() {
			Layout::instance()->footer->Push('© Travel, 2023');
		}

		#[NoReturn] public function Check() {
			SendJSONSuccess($this->db->Check());
		}

		#[NoReturn] public function Make() {
			$this->db->Make();
			SendJSONSuccess($this->db->Check());
		}

	}

	General::init();