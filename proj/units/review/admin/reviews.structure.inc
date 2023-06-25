<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'review/consts.inc';

	use Base\Units;
	use Base\DB\MySQLi\Table;
	use Proj\Units\Consts;
	use Proj\DBObject;

	class Reviews extends Units implements Consts\Reviews {
		private DBObject $db;

		protected Table $table_reviews;

		protected function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBObject::instance();

			$this->table_reviews = new Table(self::TABLES['review'], $this->db);
			$this->table_reviews->id('id');
			$this->table_reviews->uint32('gid');
			$this->table_reviews->uint8('state');
            $this->table_reviews->timestamp('date_create');
            $this->table_reviews->string('name', 50);
            $this->table_reviews->uint8('avatar');
            $this->table_reviews->text('text');

			$this->db->PushTables($this->table_reviews);
		}

	}