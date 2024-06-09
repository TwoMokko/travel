<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'people/people.consts.inc';

	require DIR_UNITS . 'people/site/views/team.tpl';

	use Base\Unit;
	use Base\Instance;
	use Proj\Units\Consts;
	use Proj\DBQuery;
	use Proj\Site\Model;
    use Proj\Site\Templates as TPLs;

	class People extends Unit implements Consts\People {
		use Instance;

		private DBQuery $db;

		private function __construct() {
			parent::__construct(self::ID, self::NAME, 'Люди', __FILE__);
			$this->db = DBQuery::instance();
		}

        public function Header(): string {
			$image = Model\General::instance()->GetImage('about');
            $subhead = Model\General::instance()->GetText('subhead_about');

            return TPLs\General\HeaderForPages::ToVar($image, 'О нас', $subhead);
        }

		public function Team(): string {
			$state = self::STATE_ACTIVE;

			$result = $this->db->Select(self::TABLES['people'], ['id', 'name', 'text', 'number', 'link_vk', 'link_wa'], "`state` = {$state}", '`date_create`', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
			$items = $this->db->FetchAll($result);

			return TPLs\People\Team::ToVar($items);
		}

	}

	People::init();