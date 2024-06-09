<?php

	namespace Proj\Site\Model;

	use Base\Instance;
	use Base\Model;
	use Proj\DBQuery;
	use Proj\Units\Consts;

	class Photo extends Model {
		use Instance;

		private DBQuery $db;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->db = DBQuery::instance();
		}

		public function GetPhotoByAlbumID(int $albumId, ?int $limit = null): array {
			$state = Consts\Photo::STATE_ACTIVE;

			$result = $this->db->Select(Consts\Photo::TABLES['photo_show'], ['id'], "(`all_id` = {$albumId}) AND (`state` = {$state})", '`date_create` DESC', $limit, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
			return $this->db->FetchAll($result);
		}

		public function GetAlbumHeader(int $id): string {
			$state = Consts\Photo::STATE_ACTIVE;

			return $this->db->SelectOneField(Consts\Photo::TABLES['photo_all'], 'header', "(`id` = {$id}) AND (`state` = {$state})");
		}

		public function GetAlbums(int $limit = 20): array {
			$state = Consts\Photo::STATE_ACTIVE;
			$result = $this->db->Select(Consts\Photo::TABLES['photo_all'], ['id', 'header'], "`state` = {$state}", '`date_create` DESC', $limit, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
			return $this->db->FetchAll($result);
		}

	}

	Photo::init();