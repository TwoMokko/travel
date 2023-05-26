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
	use Proj\Site\Templates\Template;
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
            Controller::instance()->view->Push($this->all, [$this, 'HeaderForAll'], [$this, 'All'], [$this, 'SetSeoForAll']);
            Controller::instance()->view->Push($this->item, [$this, 'HeaderForItem'], [$this, 'Item'], [$this, 'Carousel'], [$this, 'SetSeoForItem']);
		}

        public function Select() {
            $state = self::STATE_ACTIVE;

            $result = $this->db->Select(self::TABLES['type'], ['id', 'name'], "`state` = {$state}");
            $data = $this->db->FetchAll($result, function (& $items, $item) {
                $items[$item['id']] = ['name' => $item['name']];
            });

            foreach ($data as $key => & $type) {
//                $result = $this->db->Select(self::TABLES['tour'], ['id', 'name'], "(`state` = {$state}) AND (`tid` = {$key})");
                $table_tour = self::TABLES['tour'];
                $table_group = self::TABLES['group'];
                $result = $this->db->Query("SELECT `tour`.`id`, CONCAT (`group`.`name`, ', ', `tour`.`date`) AS name_date FROM `{$table_tour}` AS `tour` LEFT JOIN `{$table_group}` AS `group` ON (`tour`.`gid` = `group`.`id`) WHERE (`tour`.`tid` = {$key}) AND (`tour`.`state` = {$state})");

                $type['tours'] = $this->db->FetchAll($result, function (& $items, $item) {
                    $items[$item['id']] = [
                        'name' => $item['name_date'],
                        'href' => $this->item->GetHref(['id'=>$item['id']])
                    ];
                });
            }

            Layout::instance()->main->Push(Select::ToVar($data));
        }

        public function Types(): void {
            $state = self::STATE_ACTIVE;
            $result = $this->db->Select(self::TABLES['type'], ['id', 'name', 'description', 'alias'], "`state` = {$state}", null, 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
            $items = $this->db->FetchAll($result);

            Layout::instance()->main->Push(Types::ToVar($items));
        }

        public function All(): void {
            $state = self::STATE_ACTIVE;

            $result = $this->db->Select(self::TABLES['type'], ['id', 'name', 'alias'], "`state` = {$state}");
            $items = $this->db->FetchAll($result);

            $table_tour = self::TABLES['tour'];
            $table_group = self::TABLES['group'];
            foreach ($items as & $type) {
                $result = $this->db->Query("SELECT `tour`.`id`, `tour`.`description`, `tour`.`price`, `tour`.`date`, CONCAT(`tour`.`hash`, '.', `tour`.`id`, '.', `tour`.`ext`) AS `image`, `group`.`name` FROM `{$table_tour}` AS `tour` LEFT JOIN `{$table_group}` AS `group` ON (`tour`.`gid` = `group`.`id`) WHERE (`tour`.`state` = {$state}) AND (`tour`.`tid` = {$type['id']})");
//                $result = $this->db->Select(self::TABLES['tour'], ['id', 'name', 'description', 'price', 'date'], "(`state` = {$state}) AND (`tid` = {$type['id']})", null, null, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);

                $type['tours'] = $this->db->FetchAll($result);
            }

            Layout::instance()->main->Push(All::ToVar($items));
        }

        public function HeaderForAll() {
            Layout::instance()->header->Push(General\HeaderForPages::ToVar('safdzssad', 'Путешествия', 'Возможно, текст'));
        }

        public function HeaderForItem() {
            if (!$id = GetInt('id')) die;//TODO 404
            $state = self::STATE_ACTIVE;

//            $item = $this->db->SelectOne(self::TABLES['tour'], ['name', 'date'], "(`id` = {$id}) AND (`state` = {$state})");
            $table_tour = self::TABLES['tour'];
            $table_group = self::TABLES['group'];
            $result = $this->db->Query("SELECT `tour`.`date`, `group`.`name` FROM `{$table_tour}` AS `tour` LEFT JOIN `{$table_group}` AS `group` ON (`tour`.`gid` = `group`.`id`) WHERE (`tour`.`id` = {$id}) AND (`tour`.`state` = {$state})");
            $item = $this->db->Fetch($result);

            $image = 'safdzssad';
            Layout::instance()->header->Push(General\HeaderForPages::ToVar($image, $item['name'], $item['date']));
        }

        public function Item(): void {
            $id = GetInt('id');
            $state = self::STATE_ACTIVE;
//            $result = $this->db->Select(self::TABLES['tour'], ['id', 'name', 'description', 'price', 'duration', 'video'], "`state` = {$state}", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
            $table_tour = self::TABLES['tour'];
            $table_group = self::TABLES['group'];
            $result = $this->db->Query("SELECT `tour`.*, `group`.`name`, `group`.`video`, `group`.`photo_id` FROM `{$table_tour}` AS `tour` LEFT JOIN `{$table_group}` AS `group` ON (`tour`.`gid` = `group`.`id`)");
            $data = $this->db->Fetch($result);

            $result_program = $this->db->Select(self::TABLES['program'], ['day', 'description'], "`tour_id` = {$id}");
            $program = $this->db->FetchAll($result_program);

            Layout::instance()->main->Push(Item::ToVar($data, $program));
        }

		public function Carousel(): void {
			$id = GetInt('id');
			$state = self::STATE_ACTIVE;

//			$result = $this->db->Select(self::TABLES['tour'], ['id', 'name', 'date', 'price'], "(`state` = {$state}) AND (`id` != {$id})", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
            $table_tour = self::TABLES['tour'];
            $table_group = self::TABLES['group'];
            $result = $this->db->Query("SELECT `tour`.`id`, `tour`.`date`, `tour`.`price`, CONCAT(`tour`.`hash`, '.', `tour`.`id`, '.', `tour`.`ext`) AS `image`, `group`.`name` FROM `{$table_tour}` AS `tour` LEFT JOIN `{$table_group}` AS `group` ON (`tour`.`gid` = `group`.`id`) WHERE (`tour`.`state` = {$state}) AND (`tour`.`id` != {$id}) ORDER BY `tour`.`date_create` DESC");

            $items = $this->db->FetchAll($result);

			Layout::instance()->main->Push(Carousel::ToVarCarousel($items));
		}

		public function SetSeoForAll() {
			Template::instance()->SetTitle('Путешествия');
			Template::instance()->SetDescription('Недорогие туры на Алтай. Всем рады.');
		}

		public function SetSeoForItem() {
			$id = GetParam('id');
			$name = $this->db->SelectOneField(self::TABLES['tour'], 'name', "`id` = {$id}");
			$description = $this->db->SelectOneField(self::TABLES['tour'], 'description', "`id` = {$id}");

			Template::instance()->SetTitle("{$name}");
			Template::instance()->SetDescription("{$description}");
		}

	}

	Tour::init();