<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'photo/consts.inc';
//	require DIR_UNITS . 'photo/site/views/a.tpl';


	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Units;
	use Proj\Units\Consts;
	use Proj\DBQuery;
	use Proj\Site\Templates\Layout;
//	use Proj\Site\Templates\photo\a;
	use Proj\Site\Templates\General;

	class Photo extends Units implements Consts\Photo {
		use Instance;

		private DBQuery $db;

		public Action $a;
		public Action $i;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBQuery::instance();

			$this->a = new Action('story', 'null');
			$this->i = new Action('story', 'null');

			Controller::instance()->view->Push($this->a, [$this, 'HeaderForAll']);
			Controller::instance()->view->Push($this->i, [$this, 'HeaderForItem']);
		}

		public function HeaderForAll() {
			Layout::instance()->header->Push(General\HeaderForPages::object()->ToVar('safdzssad', 'Приключения', 'Возможно, текст'));
		}

		public function HeaderForItem() {
			if (!$id = GetInt('id')) die;//TODO 404

			$state = self::STATE_ACTIVE;

			$item = $this->db->SelectOne(self::TABLES['photo'], ['header'], "(`id` = {$id}) AND (`state` = {$state})");

			$image = 'safdzssad';
			Layout::instance()->header->Push(General\HeaderForPages::object()->ToVar($image, $item['header'], ''));
		}

		public function All(): void {
			$state = self::STATE_ACTIVE;
			$result = $this->db->Select(self::TABLES['photo'], ['id', 'header', 'text'], "`state` = {$state}", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
			$items = $this->db->FetchAll($result);

			Layout::instance()->main->Push(All::object()->ToVar($items));
		}

		public function Show(): void {
			$state = self::STATE_ACTIVE;

			$data = $this->db->SelectOne(self::TABLES['photo'], ['id', 'header', 'text'], "(`state` = {$state})", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);

			Layout::instance()->main->Push(Show::object()->ToVar($data));
		}


	}

	Photo::init();