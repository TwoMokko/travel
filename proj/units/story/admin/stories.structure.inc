<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'story/consts.inc';

	use Base\Units;
	use Base\DB\TableMySQLi;
	use Proj\Units\Consts;
	use Proj\DBObject;

	class Story extends Units implements Consts\Story {
		private DBObject $db;

		protected TableMySQLi $table_stories;

		protected function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBObject::instance();

			$this->table_stories = new TableMySQLi(self::TABLES['story'], $this->db);
			$this->table_stories->id('id');
			$this->table_stories->uint8('state');
			$this->table_stories->timestamp('date_create');
			$this->table_stories->timestamp('date_modify');
			$this->table_stories->string('header', 50);
			$this->table_stories->string('hash', 32);
			$this->table_stories->string('ext', 6);
			$this->table_stories->text('text');

			$this->db->PushTables($this->table_stories);
		}

	}