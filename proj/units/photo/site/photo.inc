<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'photo/consts.inc';
	require DIR_UNITS . 'photo/site/views/all.tpl';
	require DIR_UNITS . 'photo/site/views/show.tpl';
	require DIR_UNITS . 'photo/site/views/forTour.tpl';


	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Units;
	use Proj\Units\Consts;
	use Proj\DBQuery;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\photo\All;
	use Proj\Site\Templates\photo\Show;
	use Proj\Site\Templates\photo\ForTour;
	use Proj\Site\Templates\General;

	class Photo extends Units implements Consts\Photo {
		use Instance;

		private DBQuery $db;

		public Action $all;
		public Action $show;
		public Action $for_tour;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBQuery::instance();

			$this->all = new Action('photo', 'null');
			$this->show = new Action('photo', 'show', '/photo/show?id=%id%');
			$this->for_tour = new Action('tours', 'show', '/tour/show?id=%id%');

			Controller::instance()->view->Push($this->all, [$this, 'HeaderForAll'], [$this, 'All']);
			Controller::instance()->view->Push($this->show, [$this, 'HeaderForItem'], [$this, 'Show']);
			Controller::instance()->view->Push($this->for_tour, [$this, 'ForTour']);
		}

		public function HeaderForAll() {
			Layout::instance()->header->Push(General\HeaderForPages::object()->ToVar('safdzssad', 'Фотографии', 'Возможно, текст'));
		}

		public function HeaderForItem() {
			if (!$id = GetInt('id')) die;//TODO 404

			$state = self::STATE_ACTIVE;

			$item = $this->db->SelectOne(self::TABLES['photo_all'], ['header'], "(`id` = {$id}) AND (`state` = {$state})");

			$image = 'safdzssad';
			Layout::instance()->header->Push(General\HeaderForPages::object()->ToVar($image, $item['header'], ''));
		}

		public function All(): void {
			$state = self::STATE_ACTIVE;
			$result = $this->db->Select(self::TABLES['photo_all'], ['id', 'header'], "`state` = {$state}", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
			$items = $this->db->FetchAll($result);

			Layout::instance()->main->Push(All::object()->ToVar($items));
		}

		public function Show(): void {
			if (!$id = GetInt('id')) die;//TODO 404

			$state = self::STATE_ACTIVE;

			$result = $this->db->Select(self::TABLES['photo_show'], ['id'], "(`all_id` = {$id}) AND (`state` = {$state})", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
			$data = $this->db->FetchAll($result);

			Layout::instance()->main->Push(Show::object()->ToVar($data));
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

			Layout::instance()->main->Push(ForTour::object()->ToVar($data, $photo_id));
		}

	}

	Photo::init();