<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'people/consts.inc';
	require DIR_UNITS . 'people/site/views/team.tpl';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Proj\Units\Consts;
	use Proj\DBQuery;
	use Proj\Site\Units;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\People\Team;
    use Proj\Site\Templates\General;

	class People extends \Base\Units implements Consts\People {
		use Instance;

		private DBQuery $db;

		public Action $people;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBQuery::instance();

			$this->people = new Action('about', 'null');

			Controller::instance()->view->Push($this->people, [$this, 'Header']);
		}

        public function Header() {
			$image = Units\General::instance()->GetImage('about');
            Layout::instance()->header->Push(General\HeaderForPages::ToVar("{$image}", 'О нас', 'Возможно, текст'));
        }

		public function Team(): string {
			$state = self::STATE_ACTIVE;

//			$table_people = self::TABLES['people'];
//			$table_image = Consts\General::TABLES['image'];
//			$result = $this->db->Query("SELECT `people`.`id`, `people`.`name`, `people`.`text`, `people`.`number`, `people`.`link_vk`, `people`.`link_wa`, CONCAT(`people`.`hash`, '.', `people`.`id`, '.', `people`.`ext`) AS `image`, CONCAT(`image`.`hash`, '.', `image`.`id`, '.', `image`.`ext`) AS `image_about` FROM `{$table_people}` AS `people` LEFT JOIN `{$table_image}` AS `image` ON (`image`.`name` = 'about_description') WHERE `people`.`state` = {$state}");

			$result = $this->db->Select(self::TABLES['people'], ['id', 'name', 'text', 'number', 'link_vk', 'link_wa'], "`state` = {$state}", '`date_create`', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
			$items = $this->db->FetchAll($result);

			return Team::ToVar($items);
		}

	}

	People::init();