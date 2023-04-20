<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'photo/consts.inc';
	require DIR_UNITS . 'photo/site/views/all.tpl';
	require DIR_UNITS . 'photo/site/views/show.tpl';
	require DIR_UNITS . 'photo/site/views/forTour.tpl';
	require DIR_UNITS . 'photo/site/views/forMain.tpl';


	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Units;
	use Proj\Site\Templates\Template;
	use Proj\Units\Consts;
	use Proj\DBQuery;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\photo\All;
	use Proj\Site\Templates\photo\Show;
	use Proj\Site\Templates\photo\ForTour;
	use Proj\Site\Templates\photo\ForMain;
	use Proj\Site\Templates\General;

	class Photo extends Units implements Consts\Photo {
		use Instance;

		private DBQuery $db;

		public Action $all;
		public Action $show;
		public Action $for_tour;
		public Action $for_main;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBQuery::instance();

			$this->all = new Action('photo', 'null', 'default');
			$this->show = new Action('photo', 'show', '/photo/show?id=%id%');
			$this->for_tour = new Action('tours', 'show', '/tour/show?id=%id%');
			$this->for_main = new Action();

			Controller::instance()->view->Push($this->all, [$this, 'HeaderForAll'], [$this, 'All'], [$this, 'SetSeoForAll']);
			Controller::instance()->view->Push($this->show, [$this, 'HeaderForItem'], [$this, 'Show'], [$this, 'SetSeoForShow']);
			Controller::instance()->view->Push($this->for_tour, [$this, 'ForTour']);
			Controller::instance()->view->Push($this->for_main, [$this, 'ForMain']);
		}

		public function HeaderForAll() {
			Layout::instance()->header->Push(General\HeaderForPages::ToVar('safdzssad', 'Фотографии', 'Возможно, текст'));
		}

		public function HeaderForItem() {
			if (!$id = GetInt('id')) die;//TODO 404

			$state = self::STATE_ACTIVE;

			$item = $this->db->SelectOne(self::TABLES['photo_all'], ['header'], "(`id` = {$id}) AND (`state` = {$state})");

			$image = 'safdzssad';
			Layout::instance()->header->Push(General\HeaderForPages::ToVar($image, $item['header'], ''));
		}

		public function All(): void {
			$state = self::STATE_ACTIVE;
			$result = $this->db->Select(self::TABLES['photo_all'], ['id', 'header'], "`state` = {$state}", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
			$items = $this->db->FetchAll($result);

			Layout::instance()->main->Push(All::ToVar($items));
		}

		public function Show(): void {
			if (!$id = GetInt('id')) die;//TODO 404

			$state = self::STATE_ACTIVE;

			$result = $this->db->Select(self::TABLES['photo_show'], ['id'], "(`all_id` = {$id}) AND (`state` = {$state})", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
			$data = $this->db->FetchAll($result);

			Layout::instance()->main->Push(Show::ToVar($data));
		}

		public function ForTour(): void {
			if (!$id = GetInt('id')) die;//TODO 404

			$tour_state = Consts\Tour::STATE_ACTIVE;
			$state = self::STATE_ACTIVE;

			$photo_id = $this->db->SelectOneField(Consts\Tour::TABLES['tour'], 'photo_id', "(`id` = {$id}) AND (`state` = {$tour_state})");

			if (!$photo_id) return;

			$result = $this->db->Select(self::TABLES['photo_show'], ['id'], "(`all_id` = {$photo_id}) AND (`state` = {$state})", '`date_create` DESC', 6, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
			$data = $this->db->FetchAll($result);

			if (!$data) return;

			Layout::instance()->main->Push(ForTour::ToVar($data, $photo_id));
		}

		public function ForMain(): void {
//			if (!$id = GetInt('id')) die;//TODO 404

			$tour_state = Consts\Tour::STATE_ACTIVE;
			$state = self::STATE_ACTIVE;

//			$photo_id = $this->db->SelectOneField(Consts\Tour::TABLES['tour'], 'photo_id', "(`id` = {$id}) AND (`state` = {$tour_state})");
//
//			if (!$photo_id) return;

			$result = $this->db->Select(self::TABLES['photo_show'], ['id'], "(`state` = {$state})", '`date_create` DESC', 10, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
			$data = $this->db->FetchAll($result);

			if (!$data) return;

			Layout::instance()->main->Push(ForMain::ToVar($data));
		}

		public function SetSeoForAll() {
			Template::instance()->SetTitle('Фотографии');
			Template::instance()->SetDescription('');
		}

		public function SetSeoForShow() {
			$id = GetParam('id');
			$header = $this->db->SelectOneField(self::TABLES['photo_all'], 'header', "`id` = {$id}");

			Template::instance()->SetTitle("{$header}");
			Template::instance()->SetDescription('');
		}
	}

	Photo::init();