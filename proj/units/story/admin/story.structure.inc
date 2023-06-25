<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'story/consts.inc';

	use Base\Units;
	use Base\DB\MySQLi\Table;
	use Proj\Units\Consts;
	use Proj\DBObject;

	class Story extends Units implements Consts\Story {
		private DBObject $db;

		protected Table $table_story;

		protected function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBObject::instance();

			$this->table_story = new Table(self::TABLES['story'], $this->db);
			$this->table_story->id('id');
			$this->table_story->uint8('state');
			$this->table_story->timestamp('date_create');
			$this->table_story->timestamp('date_modify');
			$this->table_story->string('header', 50);
			$this->table_story->string('hash', 32);
			$this->table_story->string('ext', 6);
			$this->table_story->text('text');

			$this->db->PushTables($this->table_story);
		}

	}