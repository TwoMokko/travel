<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'tour_types/consts.inc';
//	require DIR_UNITS . 'stories/site/views/all.tpl';
	require DIR_UNITS . 'tour_types/site/views/show.tpl';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Units;
	use Proj\Units\Consts;
	use Proj\DBQuery;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\Tour_types\Show;

	class Tour_types extends Units implements Consts\Tour_types {
		use Instance;

		private DBQuery $db;

		public Action $tour_types;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBQuery::instance();

			$this->tour_types = new Action();

			Controller::instance()->view->Push($this->tour_types, [$this, 'Tour_types']);
		}

		public function Tour_types(): void {
			$state = self::STATE_ACTIVE;
			$result = $this->db->Select(self::TABLES['tour_types'], ['id', 'name', 'description'], "`state` = {$state}", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
			$items = $this->db->FetchAll($result);

			Layout::instance()->main->Push(Show::object()->ToVar($items));
		}
	}

	Tour_types::init();