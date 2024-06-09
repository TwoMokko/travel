<?php

	namespace Proj\Site\Model;

	use Base\Model;
	use Base\Instance;
	use Proj\Site\Actions\Pages;
	use Proj\Units\Consts;
	use Proj\DBQuery;

	class Travel extends Model {
		use Instance;

		private DBQuery $db;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->db = DBQuery::instance();
		}

		public function GetData(int $id): ?array {
			$state = Consts\Travel::STATE_ACTIVE;

			$table_tours = Consts\Travel::TABLES['tours'];
			$table_directions = Consts\Travel::TABLES['directions'];

			$result = $this->db->Query("SELECT `tours`.*, `directions`.`name`, `directions`.`video`, `directions`.`photo_id` FROM `{$table_tours}` AS `tours` LEFT JOIN `{$table_directions}` AS `directions` ON (`tours`.`gid` = `directions`.`id`) WHERE (`tours`.`id` = {$id}) AND (`tours`.`state` = {$state})");
			$data = $this->db->Fetch($result);
			return $data ?: null;
		}

		public function GetProgram(int $tourID): array {
			$result_program = $this->db->Select(Consts\Travel::TABLES['programs'], ['day', 'description'], "`tour_id` = {$tourID}");
			return $this->db->FetchAll($result_program);
		}

		public function GetExpense(int $directionID): array {
			$result = $this->db->Select(Consts\Travel::TABLES['expenses'], ['expense'], "`tour_id` = {$directionID}");
			return $this->db->FetchAll($result, function (& $items, $item) {
				$items[] = $item['expense'];
			});
		}

		public function GetAdditionalExpense(int $directionID): array {
			$result = $this->db->Select(Consts\Travel::TABLES['additional_expenses'], ['additional_expense'], "`tour_id` = {$directionID}");
			return $this->db->FetchAll($result, function (& $items, $item) {
				$items[] = $item['additional_expense'];
			});
		}

		public function GetDirectionIDByTourID(int $id): int {
			return $this->db->SelectOneField(Consts\Travel::TABLES['tours'], 'gid', "`id` = {$id}");
		}

		public function GetSeoForTour(int $tourID): array {
			$tour = $this->db->SelectOne(Consts\Travel::TABLES['tours'], ['description', 'gid'], "`id` = {$tourID}");
			$title = $this->db->SelectOneField(Consts\Travel::TABLES['directions'], 'name', "`id` = {$tour['gid']}");

			return [
				'title' => $title,
				'description' => $tour['description']
			];
		}

		public function GetInfoForHeader(int $id): array {
			$state = Consts\Travel::STATE_ACTIVE;

			$table_tours = Consts\Travel::TABLES['tours'];
			$table_directions = Consts\Travel::TABLES['directions'];

			$result = $this->db->Query("SELECT `tours`.`date`, CONCAT(`tours`.`hash`, '.', `tours`.`id`, '.', `tours`.`ext`) AS `image`, `directions`.`name` FROM `{$table_tours}` AS `tours` LEFT JOIN `{$table_directions}` AS `directions` ON (`tours`.`gid` = `directions`.`id`) WHERE (`tours`.`id` = {$id}) AND (`tours`.`state` = {$state})");
			return $this->db->Fetch($result);
		}

		public function GetToursForCarousel(int $id): array {
			$state = Consts\Travel::STATE_ACTIVE;

			$table_tours = Consts\Travel::TABLES['tours'];
			$table_directions = Consts\Travel::TABLES['directions'];
			$result = $this->db->Query("SELECT `tours`.`id`, `tours`.`date`, `tours`.`price`, CONCAT(`tours`.`hash`, '.', `tours`.`id`, '.', `tours`.`ext`) AS `image`, `directions`.`name` FROM `{$table_tours}` AS `tours` LEFT JOIN `{$table_directions}` AS `directions` ON (`tours`.`gid` = `directions`.`id`) WHERE (`tours`.`state` = {$state}) AND (`tours`.`id` != {$id}) ORDER BY `tours`.`date_create` DESC");

			return $this->db->FetchAll($result);
		}

		public function GetDataForSelect(): array {
			$table_tours = Consts\Travel::TABLES['tours'];
			$table_directions = Consts\Travel::TABLES['directions'];

            $state = Consts\Travel::STATE_ACTIVE;

            $result = $this->db->Select(Consts\Travel::TABLES['types'], ['id', 'name'], "`state` = {$state}");
            $data = $this->db->FetchAll($result, function (& $items, $item) {
                $items[$item['id']] = ['name' => $item['name']];
            });

            foreach ($data as $key => & $type) {
                $result = $this->db->Query("SELECT `tour`.`id`, CONCAT (`group`.`name`, ', ', `tour`.`date`) AS name_date FROM `{$table_tours}` AS `tour` LEFT JOIN `{$table_directions}` AS `group` ON (`tour`.`gid` = `group`.`id`) WHERE (`tour`.`tid` = {$key}) AND (`tour`.`state` = {$state})");

                $type['tours'] = $this->db->FetchAll($result, function (& $items, $item) {
                    $items[$item['id']] = [
                        'name' => $item['name_date'],
                        'href' => Pages::$tour->GetHref(['id' => $item['id']])
                    ];
                });
            }

			return $data;
		}

		public function GetTypes(): array {
			$state = Consts\Travel::STATE_ACTIVE;

			$table_tours = Consts\Travel::TABLES['tours'];
			$table_types = Consts\Travel::TABLES['types'];

			$result = $this->db->Query("SELECT `id`, `name`, `description`, CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image` FROM `{$table_types}` WHERE `state` = {$state} AND (SELECT COUNT(*) FROM `{$table_tours}` WHERE `state` = {$state} AND `tid` = `{$table_types}`.`id`) > 0");

			return $this->db->FetchAll($result);

		}

		public function GetTours(): array {
            $state = Consts\Travel::STATE_ACTIVE;

            $table_tours = Consts\Travel::TABLES['tours'];
            $table_directions = Consts\Travel::TABLES['directions'];

            $result = $this->db->Select(Consts\Travel::TABLES['types'], ['id', 'name'], "`state` = {$state}");
            $items = $this->db->FetchAll($result);

            foreach ($items as & $type) {
                $result = $this->db->Query("SELECT `tours`.`id`, `tours`.`description`, `tours`.`price`, `tours`.`date`, CONCAT(`tours`.`hash`, '.', `tours`.`id`, '.', `tours`.`ext`) AS `image`, `directions`.`name` FROM `{$table_tours}` AS `tours` LEFT JOIN `{$table_directions}` AS `directions` ON (`tours`.`gid` = `directions`.`id`) WHERE (`tours`.`state` = {$state}) AND (`tours`.`tid` = {$type['id']})");

                $type['tours'] = $this->db->FetchAll($result);
            }

			return $items;
		}

		public function GetAlbumIDByDirectionID(int $id): int {
			$state = Consts\Travel::STATE_ACTIVE;

			$albumId = $this->db->SelectOneField(Consts\Travel::TABLES['directions'], 'photo_id', "(`id` = {$id}) AND (`state` = {$state})");
			return $albumId ?: 0;
		}

	}

	Travel::init();