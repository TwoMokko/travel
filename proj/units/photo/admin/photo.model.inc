<?php

	namespace Proj\Admin\Model;

	use Base\Model;
	use Base\Instance;
	use Base\DB\MySQLi\Table;
	use Proj\DBObject;
	use Proj\Units\Consts;

	class Photo extends Model {
		use Instance;

		protected Table $table_photo_all;
		protected Table $table_photo_show;

		private DBObject $db;

		private function __construct() {
			parent::__construct(__FILE__);
			$this->db = DBObject::instance();
		}

		public function AcceptTables(/** @var Table[] $tables */ $tables) {
			[$this->table_photo_all, $this->table_photo_show] = $tables;
		}

		public function GetPhotoShow(int $idAlbum): array {
            $result = $this->table_photo_show->Select(['id'], "`all_id` = {$idAlbum}", null, null, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
            return $this->table_photo_show->FetchAll($result);
        }

		public function GetAlbums(): array {
			$state = Consts\Photo::STATE_ACTIVE;
			$result = $this->table_photo_all->Select(['id', 'header'], "`state` = {$state}");
			return $this->table_photo_all->FetchAll($result, function(& $all, $item) {
				$all[$item['id']] = $item['header'];
			});
		}

	}

	Photo::init();