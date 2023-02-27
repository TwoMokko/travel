<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'tour_types/consts.inc';

	use Base\Units;
	use Base\DB\TableMySQLi;
	use Proj\Units\Consts;
	use Proj\DBObject;

	class Tour_types extends Units implements Consts\Tour_types {
		private DBObject $db;

		protected TableMySQLi $table_tour_types;

		protected function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBObject::instance();

			$this->table_tour_types = new TableMySQLi(self::TABLES['tour_types'], $this->db);
			$this->table_tour_types->id('id');
			$this->table_tour_types->uint8('state');
			$this->table_tour_types->timestamp('date_create');
			$this->table_tour_types->timestamp('date_modify');
			$this->table_tour_types->string('name', 50);
			$this->table_tour_types->string('hash', 32);
			$this->table_tour_types->string('ext', 6);
			$this->table_tour_types->text('description');

			$this->db->PushTables($this->table_tour_types);
		}

	}