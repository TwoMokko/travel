<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'people/consts.inc';
	require DIR_UNITS . 'people/site/views/team.tpl';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Units;
	use Proj\Units\Consts;
	use Proj\DBQuery;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\People\Team;
    use Proj\Site\Templates\General;

	class People extends Units implements Consts\People {
		use Instance;

		private DBQuery $db;

		public Action $people;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBQuery::instance();

			$this->people = new Action('about', 'null');

			Controller::instance()->view->Push($this->people, [$this, 'Header'], [$this, 'Team']);
		}

        public function Header() {

            Layout::instance()->header->Push(General\HeaderForPages::ToVar('safdzssad', 'О нас', 'Возможно, текст'));
        }

		public function Team(): void {
			$state = self::STATE_ACTIVE;
			$result = $this->db->Select(self::TABLES['people'], ['id', 'name', 'text', 'number', 'link_vk', 'link_wa'], "`state` = {$state}", '`date_create`', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
			$items = $this->db->FetchAll($result);

			Layout::instance()->main->Push(Team::ToVar($items));
		}

	}

	People::init();