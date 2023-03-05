<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'stories/consts.inc';
	require DIR_UNITS . 'stories/site/views/all.tpl';
	require DIR_UNITS . 'stories/site/views/show.tpl';


	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Units;
	use Proj\Units\Consts;
	use Proj\DBQuery;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\Stories\All;
	use Proj\Site\Templates\Stories\Show;
    use Proj\Site\Templates\General;

	class Stories extends Units implements Consts\Stories {
		use Instance;

		private DBQuery $db;

		public Action $all;
		public Action $show;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBQuery::instance();

			$this->all = new Action('stories', 'null');
			$this->show = new Action('stories', 'show', '/stories/show?id=%id%');

			Controller::instance()->view->Push($this->all, [$this, 'All']);
			Controller::instance()->view->Push($this->all, [$this, 'HeaderForAll']);
			Controller::instance()->view->Push($this->show, [$this, 'HeaderForItem'], [$this, 'Show'], [$this, 'Carousel']);
		}

        public function HeaderForAll() {
            Layout::instance()->header->Push(General\HeaderForPages::object()->ToVar('safdzssad', 'Приключения', 'Возможно, текст'));
        }

        public function HeaderForItem() {
            if (!$id = GetInt('id')) die;//TODO 404

            $state = self::STATE_ACTIVE;

            $item = $this->db->SelectOne(self::TABLES['stories'], ['header'], "(`id` = {$id}) AND (`state` = {$state})");

            $image = 'safdzssad';
            Layout::instance()->header->Push(General\HeaderForPages::object()->ToVar($image, $item['header'], ''));
        }

		public function All(): void {
			$state = self::STATE_ACTIVE;
			$result = $this->db->Select(self::TABLES['stories'], ['id', 'header', 'text'], "`state` = {$state}", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
			$items = $this->db->FetchAll($result);

			Layout::instance()->main->Push(All::object()->ToVar($items));
		}

		public function Show(): void {
			$state = self::STATE_ACTIVE;

			$data = $this->db->SelectOne(self::TABLES['stories'], ['id', 'header', 'text'], "(`state` = {$state})", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);

			Layout::instance()->main->Push(Show::object()->ToVar($data));
		}

        public function Carousel(): void {
            $state = self::STATE_ACTIVE;

            $result = $this->db->Select(self::TABLES['stories'], ['id', 'header'], "(`state` = {$state})", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
            $items = $this->db->FetchAll($result);

            Layout::instance()->main->Push(Show::object()->ToVarCarousel($items));
        }

	}

	Stories::init();