<?php

	namespace Proj\Site\Model;

	use Base\Model;
	use Base\Instance;
	use Proj\Units\Consts;
	use Proj\DBQuery;

	class Story extends Model {
		use Instance;

		private DBQuery $db;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->db = DBQuery::instance();
		}

		public function GetList(): array {
			$state = Consts\Story::STATE_ACTIVE;
			$result = $this->db->Select(Consts\Story::TABLES['story'], ['id', 'header', 'text'], "`state` = {$state}", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
			return $this->db->FetchAll($result);
		}

		public function GetStoryByID(int $id): ?array {
			$state = Consts\Story::STATE_ACTIVE;

			return $this->db->SelectOne(Consts\Story::TABLES['story'], ['id', 'header', 'text'], "(`state` = {$state}) AND (`id` = {$id})", '`date_create` DESC', null, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
		}

		public function GetListNotId(int $id, int $limit): array {
			$state = Consts\Story::STATE_ACTIVE;
			$result = $this->db->Select(Consts\Story::TABLES['story'], ['id', 'header'], "(`state` = {$state}) AND (`id` != {$id})", '`date_create` DESC', $limit, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
			return $this->db->FetchAll($result);
		}

		public function GetTitle(int $id): string {
			return $this->db->SelectOneField(Consts\Story::TABLES['story'], 'header', "`id` = {$id}");
		}

	}

	Story::init();