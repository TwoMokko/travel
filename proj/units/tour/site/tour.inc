<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'tour/consts.inc';
	require DIR_UNITS . 'tour/site/views/about.tpl';
	require DIR_UNITS . 'tour/site/views/video.tpl';
	require DIR_UNITS . 'tour/site/views/expense.tpl';
	require DIR_UNITS . 'tour/site/views/program.tpl';
	require DIR_UNITS . 'tour/site/views/takeThings.tpl';

	require DIR_UNITS . 'tour/site/views/select.tpl';
	require DIR_UNITS . 'tour/site/views/types.tpl';
	require DIR_UNITS . 'tour/site/views/all.tpl';
	require DIR_UNITS . 'tour/site/views/item.tpl';
	require DIR_UNITS . 'tour/site/views/carousel.tpl';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Units;
	use Proj\Units\Consts;
    use Proj\DBQuery;
    use Proj\Site;
	use Proj\Site\Templates\Template;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\Tour as TPL;

	use Proj\Site\Templates\Tour\Carousel;
    use Proj\Site\Templates\Tour\Select;
    use Proj\Site\Templates\Tour\Types;
    use Proj\Site\Templates\Tour\All;
    use Proj\Site\Templates\Tour\Item;
    use Proj\Site\Templates\General;

    class Tour extends Units implements Consts\Tour {
		use Instance;

		private DBQuery $db;

//        public Action $item;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBQuery::instance();

//            $this->item = new Action('tours', 'show', '/tours/show?id=%id%');
//            Controller::instance()->view->Push($this->item, [$this, 'HeaderForItem'], [$this, 'SetSeoForItem']);
		}

		public function Show($id) {
			$state = self::STATE_ACTIVE;

			$table_tour = self::TABLES['tour'];
			$table_group = self::TABLES['group'];
			$result = $this->db->Query("SELECT `tour`.*, `group`.`name`, `group`.`video`, `group`.`photo_id` FROM `{$table_tour}` AS `tour` LEFT JOIN `{$table_group}` AS `group` ON (`tour`.`gid` = `group`.`id`) WHERE (`tour`.`id` = {$id} AND `tour`.`state` = {$state})");
			$data = $this->db->Fetch($result);

			$result_program = $this->db->Select(self::TABLES['program'], ['day', 'description'], "`tour_id` = {$id}");
			$program = $this->db->FetchAll($result_program);

			$result_expense = $this->db->Select(self::TABLES['expense'], ['expense'], "`tour_id` = {$data['gid']}");
			$expense = $this->db->FetchAll($result_expense, function (& $items, $item) {
				$items[] = $item['expense'];
			});

			$result_additional_expense = $this->db->Select(self::TABLES['additional_expense'], ['additional_expense'], "`tour_id` = {$data['gid']}");
			$additional_expense = $this->db->FetchAll($result_additional_expense, function (& $items, $item) {
				$items[] = $item['additional_expense'];
			});

			if (!$data) Pages::instance()->Error404();

			Layout::instance()->header->Push(
				TPL\About::ToVar($data),
                $data['video'] ? TPL\Video::ToVar($data) : '',
				TPL\Expense::ToVar($data, $expense, $additional_expense),
				TPL\Program::ToVar($program)
//				TPL\TakeThings::ToVar()
			);

		}

		public function GetThings(): string { return TPL\TakeThings::ToVar(); }

        public function GetSelect(): string {
            $state = self::STATE_ACTIVE;

            $result = $this->db->Select(self::TABLES['type'], ['id', 'name'], "`state` = {$state}");
            $data = $this->db->FetchAll($result, function (& $items, $item) {
                $items[$item['id']] = ['name' => $item['name']];
            });

            foreach ($data as $key => & $type) {
                $table_tour = self::TABLES['tour'];
                $table_group = self::TABLES['group'];
                $result = $this->db->Query("SELECT `tour`.`id`, CONCAT (`group`.`name`, ', ', `tour`.`date`) AS name_date FROM `{$table_tour}` AS `tour` LEFT JOIN `{$table_group}` AS `group` ON (`tour`.`gid` = `group`.`id`) WHERE (`tour`.`tid` = {$key}) AND (`tour`.`state` = {$state})");

                $type['tours'] = $this->db->FetchAll($result, function (& $items, $item) {
                    $items[$item['id']] = [
                        'name' => $item['name_date'],
                        'href' => Pages::instance()->tour->GetHref(['id'=>$item['id']])
                    ];
                });
            }

           return Select::ToVar($data);
        }

        public function GetTypes(): string {
            $state = self::STATE_ACTIVE;
            $table_tour = self::TABLES['tour'];
            $table_type = self::TABLES['type'];
            $result = $this->db->Query("SELECT `id`, `name`, `description`, `alias`, CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image` FROM `{$table_type}` WHERE `state` = {$state} AND (SELECT COUNT(*) FROM `{$table_tour}` WHERE `state` = {$state} AND `tid` = `{$table_type}`.`id`) > 0");
            $items = $this->db->FetchAll($result);

            return Types::ToVar($items);
        }

        public function GetAllTours(): string {
            $state = self::STATE_ACTIVE;

            $result = $this->db->Select(self::TABLES['type'], ['id', 'name', 'alias'], "`state` = {$state}");
            $items = $this->db->FetchAll($result);

            $table_tour = self::TABLES['tour'];
            $table_group = self::TABLES['group'];
            foreach ($items as & $type) {
                $result = $this->db->Query("SELECT `tour`.`id`, `tour`.`description`, `tour`.`price`, `tour`.`date`, CONCAT(`tour`.`hash`, '.', `tour`.`id`, '.', `tour`.`ext`) AS `image`, `group`.`name` FROM `{$table_tour}` AS `tour` LEFT JOIN `{$table_group}` AS `group` ON (`tour`.`gid` = `group`.`id`) WHERE (`tour`.`state` = {$state}) AND (`tour`.`tid` = {$type['id']})");

                $type['tours'] = $this->db->FetchAll($result);
            }

            return All::ToVar($items);
        }

        public function GetHeaderForAll(): string {
			$image = Site\Units\General::instance()->GetImage('tour');
			return General\HeaderForPages::ToVar("{$image}", 'Путешествия', 'Возможно, текст');
        }

        public function GetHeaderForItem($id): string {
            $state = self::STATE_ACTIVE;

            $table_tour = self::TABLES['tour'];
            $table_group = self::TABLES['group'];
            $result = $this->db->Query("SELECT `tour`.`date`, `group`.`name` FROM `{$table_tour}` AS `tour` LEFT JOIN `{$table_group}` AS `group` ON (`tour`.`gid` = `group`.`id`) WHERE (`tour`.`id` = {$id}) AND (`tour`.`state` = {$state})");
            $item = $this->db->Fetch($result);

			$result = $this->db->Query("SELECT CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image` FROM `tour` WHERE `id` = '{$id}'");
			$image = $this->db->Fetch($result)['image'];
			$path = Consts\Tour::PATH_TOUR_ORIGINAL_RELATIVE . $image;
			return General\HeaderForPages::ToVar("{$path}", $item['name'], $item['date']);
        }

		public function HeaderForItem() {
			if (!$id = GetInt('id')) die;//TODO 404
			$state = self::STATE_ACTIVE;

//            $item = $this->db->SelectOne(self::TABLES['tour'], ['name', 'date'], "(`id` = {$id}) AND (`state` = {$state})");
			$table_tour = self::TABLES['tour'];
			$table_group = self::TABLES['group'];
			$result = $this->db->Query("SELECT `tour`.`date`, `group`.`name` FROM `{$table_tour}` AS `tour` LEFT JOIN `{$table_group}` AS `group` ON (`tour`.`gid` = `group`.`id`) WHERE (`tour`.`id` = {$id}) AND (`tour`.`state` = {$state})");
			$item = $this->db->Fetch($result);

			$result = $this->db->Query("SELECT CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image` FROM `tour` WHERE `id` = '{$id}'");
			$image = $this->db->Fetch($result)['image'];
//			$image = $this->db->SelectOneFieldCalc(self::TABLES['tour'], "CONCAT(`hash`, '.', `id`, '.', `ext`)", 'image', "`id` = '{$id}'");
			$path = Consts\Tour::PATH_TOUR_ORIGINAL_RELATIVE . $image;
			Layout::instance()->header->Push(General\HeaderForPages::ToVar("{$path}", $item['name'], $item['date']));
		}

		public function GetCarousel($id): string {
//			$id = GetInt('id');
			$state = self::STATE_ACTIVE;

            $table_tour = self::TABLES['tour'];
            $table_group = self::TABLES['group'];
            $result = $this->db->Query("SELECT `tour`.`id`, `tour`.`date`, `tour`.`price`, CONCAT(`tour`.`hash`, '.', `tour`.`id`, '.', `tour`.`ext`) AS `image`, `group`.`name` FROM `{$table_tour}` AS `tour` LEFT JOIN `{$table_group}` AS `group` ON (`tour`.`gid` = `group`.`id`) WHERE (`tour`.`state` = {$state}) AND (`tour`.`id` != {$id}) ORDER BY `tour`.`date_create` DESC");

            $items = $this->db->FetchAll($result);

            if (!$items) return '';

			return Carousel::ToVarCarousel($items);
		}

        public function GetGroupId(int $id): int {
            return $this->db->SelectOneField(self::TABLES['tour'], 'gid', "`id` = {$id}");
        }

		public function SetSeoForItem($id) {
//			$id = GetParam('id');
			$name = $this->db->SelectOneField(self::TABLES['tour'], 'name', "`id` = {$id}");
			$description = $this->db->SelectOneField(self::TABLES['tour'], 'description', "`id` = {$id}");

			Template::instance()->SetTitle("{$name}");
			Template::instance()->SetDescription("{$description}");
		}

	}

	Tour::init();