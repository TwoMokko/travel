<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'tour/consts.inc';

	use Base\Units;
	use Base\DB\TableMySQLi;
	use Proj\Units\Consts;
	use Proj\DBObject;

	class Tour extends Units implements Consts\Tour {
		private DBObject $db;

        protected TableMySQLi $table_tour_types;
        protected TableMySQLi $table_tour;

        protected function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBObject::instance();

			$this->table_tour_types = new TableMySQLi(self::TABLES['type'], $this->db);
			$this->table_tour_types->id('id');
			$this->table_tour_types->uint8('state');
			$this->table_tour_types->timestamp('date_create');
			$this->table_tour_types->timestamp('date_modify');
			$this->table_tour_types->string('name', 50);
			$this->table_tour_types->string('alias', 50);
			$this->table_tour_types->string('hash', 32);
			$this->table_tour_types->string('ext', 6);
			$this->table_tour_types->text('description');

			$this->table_tour = new TableMySQLi(self::TABLES['tour'], $this->db);
			$this->table_tour->id('id');
			$this->table_tour->uint32('tid');
			$this->table_tour->uint32('photo_id');
			$this->table_tour->uint8('state');
			$this->table_tour->timestamp('date_create');
			$this->table_tour->timestamp('date_modify');
			$this->table_tour->string('name', 255);
            $this->table_tour->text('description');
            $this->table_tour->uint24('price');
            $this->table_tour->uint8('duration');
            $this->table_tour->string('date', 255);
            $this->table_tour->string('hash', 32);
            $this->table_tour->string('ext', 6);
            $this->table_tour->string('video', 255);

            $this->db->PushTables($this->table_tour_types, $this->table_tour);
		}

	}