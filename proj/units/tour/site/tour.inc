<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'tour/consts.inc';
    require DIR_UNITS . 'tour/site/views/select.tpl';
    require DIR_UNITS . 'tour/site/views/types.tpl';
    require DIR_UNITS . 'tour/site/views/all.tpl';
	require DIR_UNITS . 'tour/site/views/item.tpl';
	require DIR_UNITS . 'tour/site/views/carousel.tpl';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Units;
	use Proj\Site\Templates\Tour\Carousel;
	use Proj\Units\Consts;
    use Proj\DBQuery;
    use Proj\Site\Templates\Layout;
    use Proj\Site\Templates\Tour\Select;
    use Proj\Site\Templates\Tour\Types;
    use Proj\Site\Templates\Tour\All;
    use Proj\Site\Templates\Tour\Item;
    use Proj\Site\Templates\General;

    class Tour extends Units implements Consts\Tour {
		use Instance;

		private DBQuery $db;

        public Action $select;
        public Action $types;
        public Action $all;
        public Action $item;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBQuery::instance();

            $this->select = new Action();
            $this->types = new Action();
            $this->all = new Action('tours');
            $this->item = new Action('tours', 'show', '/tours/show?id=%id%');

            Controller::instance()->view->Push($this->select, [$this, 'Select']);
            Controller::instance()->view->Push($this->types, [$this, 'Types']);
            Controller::instance()->view->Push($this->all, [$this, 'HeaderForAll'], [$this, 'All']);
            Controller::instance()->view->Push($this->item, [$this, 'HeaderForItem'], [$this, 'Item'], [$this, 'Carousel']);
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

        public function Types(): void {
            $state = self::STATE_ACTIVE;
            $result = $this->db->Select(self::TABLES['type'], ['id', 'name', 'description', 'alias'], "`state` = {$state}", null, 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
            $items = $this->db->FetchAll($result);

            Layout::instance()->main->Push(Types::object()->ToVar($items));
        }

        public function All(): void {
            $state = self::STATE_ACTIVE;

            $result = $this->db->Select(self::TABLES['type'], ['id', 'name', 'alias'], "`state` = {$state}");
            $items = $this->db->FetchAll($result);

            foreach ($items as & $type) {
                $result = $this->db->Select(self::TABLES['tour'], ['id', 'name', 'description', 'price', 'date'], "(`state` = {$state}) AND (`tid` = {$type['id']})", null, null, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
                $type['tours'] = $this->db->FetchAll($result);
            }

            Layout::instance()->main->Push(All::object()->ToVar($items));
        }

        public function HeaderForAll() {
            Layout::instance()->header->Push(General\HeaderForPages::object()->ToVar('safdzssad', 'Путешествия', 'Возможно, текст'));
        }

        public function HeaderForItem() {
            if (!$id = GetInt('id')) die;//TODO 404
            $state = self::STATE_ACTIVE;

            $item = $this->db->SelectOne(self::TABLES['tour'], ['name', 'date'], "(`id` = {$id}) AND (`state` = {$state})");

            $image = 'safdzssad';
            Layout::instance()->header->Push(General\HeaderForPages::object()->ToVar($image, $item['name'], $item['date']));
        }

        public function Item(): void {
            $state = self::STATE_ACTIVE;
            $result = $this->db->Select(self::TABLES['tour'], ['id', 'name', 'description', 'price', 'duration', 'video'], "`state` = {$state}", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
            $data = $this->db->Fetch($result);

            Layout::instance()->main->Push(Item::object()->ToVar($data));
        }

		public function Carousel(): void {
			$id = GetInt('id');
			$state = self::STATE_ACTIVE;

			$result = $this->db->Select(self::TABLES['tour'], ['id', 'name', 'date', 'price'], "(`state` = {$state}) AND (`id` != {$id})", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
			$items = $this->db->FetchAll($result);

			Layout::instance()->main->Push(Carousel::object()->ToVarCarousel($items));
		}

	}

	Tour::init();