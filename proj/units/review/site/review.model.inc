<?php

	namespace Proj\Site\Model;

	use Base\Model;
	use Base\Instance;
	use Proj\Units\Consts;
	use Proj\DBQuery;

	class Review extends Model {
		use Instance;

		private DBQuery $db;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->db = DBQuery::instance();
		}

		public function GetList(): array {
			$state = Consts\Review::STATE_VERIFIED;
			$result = $this->db->Select(Consts\Review::TABLES['review'], ['id', 'name', 'text', 'avatar'], "`state` = {$state}", '`date_create` DESC', 20);
			return $this->db->FetchAll($result);
		}

		public function Add(array $data): void {
			$this->db->Insert(Consts\Review::TABLES['review'], $data);
		}

		public function GetReviewByID(int $id): array {
			$state = Consts\Review::STATE_VERIFIED;

			$item = $this->db->SelectOne(Consts\Review::TABLES['review'], ['name', 'text', 'avatar'], "(`state` = {$state}) AND (`id` = {$id})");
			$item['image'] = Consts\Review::AVATARS[$item['avatar']];

			return $item;
		}

		public function GetReviewByTourID(int $tourID): array {
			$state = Consts\Review::STATE_VERIFIED;

			$directionID = Travel::instance()->GetDirectionIDByTourID($tourID);

			$result = $this->db->Select(Consts\Review::TABLES['review'], ['id', 'name', 'text', 'avatar'], "(`state` = {$state}) AND (`gid` = {$directionID})", '`date_create` DESC', 20);
			return $this->db->FetchAll($result);
		}

	}

	Review::init();