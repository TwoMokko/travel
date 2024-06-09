<?php

	namespace Proj\Admin\Model;

	use Base\Model;
	use Base\Instance;
	use Base\DB\MySQLi\Table;
	use Proj\DBObject;
	use Proj\Units\Consts;

	class Travel extends Model {
		use Instance;

		protected Table $table_types;
		protected Table $table_directions;
		protected Table $table_tours;

		private DBObject $db;

		private function __construct() {
			parent::__construct(__FILE__);
			$this->db = DBObject::instance();
		}

		public function AcceptTables(/** @var Table[] $tables */ $tables) {
			[$this->table_types, $this->table_directions, $this->table_tours] = $tables;
		}

		public function GetTypes(): array {
			$state = Consts\Travel::STATE_ACTIVE;
			$result = $this->table_types->Select(['id', 'name'], "`state` = {$state}");
			return $this->table_types->FetchAll($result, function(& $types, $type) {
				$types[$type['id']] = $type['name'];
			});
		}

		public function GetDirections(): array {
			$state = Consts\Travel::STATE_ACTIVE;
			$result = $this->table_directions->Select(['id', 'name'], "`state` = {$state}");
			return $this->table_directions->FetchAll($result, function(& $directions, $direction) {
				$directions[$direction['id']] = $direction['name'];
			});
		}

//        public function GetTour(int $id): array {
//            return $this->table_tour->SelectOne(['date', 'gid'], "`id` = {$id}");
//        }
//
//        public function GetNameGroupTour($id): string {
//            return $this->table_group->SelectOneField('name', "`id` = {$id}");
//        }
//
//        public function GetTours(): array {
//            $state_active = Consts\Tour::STATE_ACTIVE;
//            $state_inactive = Consts\Tour::STATE_INACTIVE;
//            $result = $this->table_tour->Select(['id', 'name'], "`state` = {$state_active} OR `state` = {$state_inactive}");
//            return $this->table_tour->FetchAll($result, function(& $tours, $tour) {
//                $tours[$tour['id']] = $tour['name'];
//            });
//        }

	}

	Travel::init();