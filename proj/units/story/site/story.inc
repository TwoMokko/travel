<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'story/consts.inc';
	require DIR_UNITS . 'story/site/views/all.tpl';
	require DIR_UNITS . 'story/site/views/show.tpl';


	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Units;
	use Proj\Units\Consts;
	use Proj\DBQuery;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\Story\All;
	use Proj\Site\Templates\Story\Show;
    use Proj\Site\Templates\General;

	class Story extends Units implements Consts\Story {
		use Instance;

		private DBQuery $db;

		public Action $all;
		public Action $show;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBQuery::instance();

			$this->all = new Action('story', 'null');
			$this->show = new Action('story', 'show', '/story/show?id=%id%');

			Controller::instance()->view->Push($this->all, [$this, 'All']);
			Controller::instance()->view->Push($this->all, [$this, 'HeaderForAll']);
			Controller::instance()->view->Push($this->show, [$this, 'HeaderForItem'], [$this, 'Show'], [$this, 'Carousel']);
		}

        public function HeaderForAll() {
            Layout::instance()->header->Push(General\HeaderForPages::ToVar('safdzssad', 'Приключения', 'Возможно, текст'));
        }

        public function HeaderForItem() {
            if (!$id = GetInt('id')) die;//TODO 404

            $state = self::STATE_ACTIVE;

            $item = $this->db->SelectOne(self::TABLES['story'], ['header'], "(`id` = {$id}) AND (`state` = {$state})");

            $image = 'safdzssad';
            Layout::instance()->header->Push(General\HeaderForPages::ToVar($image, $item['header'], ''));
        }

		public function All(): void {
			$state = self::STATE_ACTIVE;
			$result = $this->db->Select(self::TABLES['story'], ['id', 'header', 'text'], "`state` = {$state}", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
			$items = $this->db->FetchAll($result);

			Layout::instance()->main->Push(All::ToVar($items));
		}

		public function Show(): void {
			$state = self::STATE_ACTIVE;

			$data = $this->db->SelectOne(self::TABLES['story'], ['id', 'header', 'text'], "(`state` = {$state})", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);

			Layout::instance()->main->Push(Show::ToVar($data));
		}

        public function Carousel(): void {
            $state = self::STATE_ACTIVE;

            $result = $this->db->Select(self::TABLES['story'], ['id', 'header'], "(`state` = {$state})", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
            $items = $this->db->FetchAll($result);

            Layout::instance()->main->Push(Show::ToVarCarousel($items));
        }

	}

	Story::init();