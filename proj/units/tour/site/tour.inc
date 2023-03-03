<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'tour/consts.inc';
	require DIR_UNITS . 'tour/site/views/types.tpl';
	require DIR_UNITS . 'tour/site/views/select.tpl';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Units;
	use Proj\Units\Consts;
	use Proj\DBQuery;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\Tour\Types;
	use Proj\Site\Templates\Tour\Select;

	class Tour extends Units implements Consts\Tour {
		use Instance;

		private DBQuery $db;

		public Action $types;
		public Action $select;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBQuery::instance();

			$this->types = new Action();
			$this->select = new Action();

			Controller::instance()->view->Push($this->types, [$this, 'Types']);
			Controller::instance()->view->Push($this->select, [$this, 'Select']);
		}

		public function Types(): void {
			$state = self::STATE_ACTIVE;
			$result = $this->db->Select(self::TABLES['type'], ['id', 'name', 'description'], "`state` = {$state}", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
			$items = $this->db->FetchAll($result);

			Layout::instance()->main->Push(Types::object()->ToVar($items));
		}

        public function Select() {
            $state = self::STATE_ACTIVE;

            $result = $this->db->Select(self::TABLES['type'], ['id', 'name'], "`state` = {$state}");
            $data = $this->db->FetchAll($result);

            foreach ($data as & $type) {
                $result = $this->db->Select(self::TABLES['tour'], ['id', 'name'], "(`state` = {$state}) AND (`tid` = {$type['id']})");
                $type['tours'] = $this->db->FetchAll($result);
            }

            Layout::instance()->main->Push(Select::object()->ToVar($data));
        }

	}

	Tour::init();