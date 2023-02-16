<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'reviews/consts.inc';
	require DIR_UNITS . 'reviews/site/views/lists.tpl';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Units;
	use Proj\Units\Consts;
	use Proj\DBQuery;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\Reviews\Lists;

	class Reviews extends Units implements Consts\Reviews {
		use Instance;

		private DBQuery $db;

		public Action $for_main;
		public Action $for_tour;
		public Action $for_list;
		public Action $get;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBQuery::instance();

			$this->for_main = new Action();
			$this->for_tour = new Action('tours', 'show');
			$this->for_list = new Action('reviews');
			$this->get = new Action('reviews', 'get');

			Controller::instance()->view->Push($this->for_main, [$this, 'ForMain']);
			Controller::instance()->view->Push($this->for_tour, [$this, 'ForTour']);
			Controller::instance()->view->Push($this->for_list, [$this, 'ForList']);
			Controller::instance()->view->Push($this->get, [$this, 'OnReview']);
		}

		public function ForMain(): void {
			$state = self::STATE_ACTIVE;
			$result = $this->db->Select(self::TABLES['reviews'], ['id', 'name', 'text'], "`state` = {$state}", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
			$items = $this->db->FetchAll($result);

			Layout::instance()->main->Push(Lists::object()->ToVarCarousel($items));
		}

		public function ForTour(): void {
			$state = self::STATE_ACTIVE;
			$tid = GetInt('id');
			$result = $this->db->Select(self::TABLES['reviews'], ['id', 'name', 'text'], "(`state` = {$state}) AND (`tid` = {$tid})", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
			$items = $this->db->FetchAll($result);

			Layout::instance()->main->Push(Lists::object()->ToVarCarousel($items));
		}

		public function ForList(): void {
			$state = self::STATE_ACTIVE;
			$result = $this->db->Select(self::TABLES['reviews'], ['id', 'name', 'text'], "`state` = {$state}", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
			$items = $this->db->FetchAll($result);

			Layout::instance()->main->Push(Lists::object()->ToVarGrid($items));
		}

		#[NoReturn] public function OnReview(): void {
			$id = GetInt('id');

			$state = self::STATE_ACTIVE;
			$path = Consts\Reviews::PATH_AVATAR_RELATIVE;
			$item = $this->db->SelectOne(self::TABLES['reviews'], ['name', 'text'], "(`state` = {$state}) AND (`id` = {$id})", null, null, ["CONCAT('{$path}', `hash`, '.', `id`, '.', `ext`) AS `image`"]);

			SendJSONSuccess($item);
		}

	}

	Reviews::init();