<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'story/consts.inc';
	require DIR_UNITS . 'story/site/views/all.tpl';
	require DIR_UNITS . 'story/site/views/show.tpl';


	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Units;
	use Proj\Site\Templates\Template;
	use Proj\Units\Consts;
	use Proj\DBQuery;
	use Proj\Site;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\Story\All;
	use Proj\Site\Templates\Story\Show;
    use Proj\Site\Templates\General;

	class Story extends Units implements Consts\Story {
		use Instance;

		private DBQuery $db;

//		public Action $all;
//		public Action $show;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBQuery::instance();

//			$this->all = new Action('stories', 'null');
//			$this->show = new Action('stories', 'show', '/stories/show?id=%id%');

//			Controller::instance()->view->Push($this->all, [$this, 'HeaderForAll'], [$this, 'SetSeoForAll']);
//			Controller::instance()->view->Push($this->show, [$this, 'HeaderForItem'], [$this, 'SetSeoForShow']);
		}

        public function HeaderForAll(): string {
            $image = Site\Units\General::instance()->GetImage('story');
            $subhead_stories = \Proj\Site\Units\General::instance()->GetText('subhead_stories');
            return General\HeaderForPages::ToVar("{$image}", 'Дневник путешествий', $subhead_stories);
        }

        public function HeaderForItem(): string {
            if (!$id = GetInt('id')) die;//TODO 404

			$state = self::STATE_ACTIVE;
            $item = $this->db->SelectOne(self::TABLES['story'], ['header'], "(`id` = {$id}) AND (`state` = {$state})");

            $image = Site\Units\General::instance()->GetImage('story');
            $subhead_one_story = \Proj\Site\Units\General::instance()->GetText('subhead_one_story');
            return General\HeaderForPages::ToVar("{$image}", $item['header'], $subhead_one_story);

//            $state = self::STATE_ACTIVE;
//
//            $item = $this->db->SelectOne(self::TABLES['story'], ['header'], "(`id` = {$id}) AND (`state` = {$state})");
//
//			$result = $this->db->Query("SELECT CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image` FROM `story` WHERE `id` = '{$id}'");
//			$image = $this->db->Fetch($result)['image'];
////			$image = $this->db->SelectOneFieldCalc(self::TABLES['story'], "CONCAT(`hash`, '.', `id`, '.', `ext`)", 'image', "`id` = '{$id}'");
//			$path = Consts\Story::PATH_COVER_RELATIVE . $image;
//            Layout::instance()->header->Push(General\HeaderForPages::ToVar("{$path}", $item['header'], ''));
        }

		public function All(): string {
			$state = self::STATE_ACTIVE;
			$result = $this->db->Select(self::TABLES['story'], ['id', 'header', 'text'], "`state` = {$state}", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
			$items = $this->db->FetchAll($result);

			return All::ToVar($items);
		}

		public function Show(): string {
			$state = self::STATE_ACTIVE;
			$id = GetInt('id');

			$data = $this->db->SelectOne(self::TABLES['story'], ['id', 'header', 'text'], "(`state` = {$state}) AND (`id` = {$id})", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);

			return Show::ToVar($data);
		}

        public function Carousel(): string {
			$id = GetInt('id');
            $state = self::STATE_ACTIVE;

            $result = $this->db->Select(self::TABLES['story'], ['id', 'header'], "(`state` = {$state}) AND (`id` != {$id})", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
            $items = $this->db->FetchAll($result);

            if (!$items) return '';

            return Show::ToVarCarousel($items);
        }

		public function SetSeoForAll() {
			Template::instance()->SetTitle('Приключения');
			Template::instance()->SetDescription('');
		}

		public function SetSeoForShow() {
			$id = GetParam('id');
			$header = $this->db->SelectOneField(self::TABLES['story'], 'header', "`id` = {$id}");

			Template::instance()->SetTitle("{$header}");
			Template::instance()->SetDescription('');
		}

	}

	Story::init();