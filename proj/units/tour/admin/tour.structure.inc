<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'tour/consts.inc';

	use Base\Units;
	use Base\DB\TableMySQLi;
	use Proj\Units\Consts;
	use Proj\DBObject;

	class Tour extends Units implements Consts\Tour {
		private DBObject $db;

        protected TableMySQLi $table_types;
        protected TableMySQLi $table_tour;
        protected TableMySQLi $table_group;
        protected TableMySQLi $table_program;

        protected function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBObject::instance();

			$this->table_types = new TableMySQLi(self::TABLES['type'], $this->db);
			$this->table_types->id('id');
			$this->table_types->uint8('state');
			$this->table_types->timestamp('date_create');
			$this->table_types->timestamp('date_modify');
			$this->table_types->string('name', 50);
			$this->table_types->string('alias', 50);
			$this->table_types->string('hash', 32);
			$this->table_types->string('ext', 6);
			$this->table_types->text('description');

            $this->table_group = new TableMySQLi(self::TABLES['group'], $this->db);
            $this->table_group->id('id');
            $this->table_group->uint8('state');
            $this->table_group->string('name', 255);
            $this->table_group->string('video', 255);
            $this->table_group->uint32('photo_id');

            $this->table_tour = new TableMySQLi(self::TABLES['tour'], $this->db);
			$this->table_tour->id('id');
			$this->table_tour->uint32('tid');
			$this->table_tour->uint32('gid');
			$this->table_tour->uint8('state');
			$this->table_tour->timestamp('date_create');
			$this->table_tour->timestamp('date_modify');
            $this->table_tour->text('description');
            $this->table_tour->uint24('price');
            $this->table_tour->uint8('duration');
            $this->table_tour->string('date', 255);
            $this->table_tour->string('hash', 32);
            $this->table_tour->string('ext', 6);

            $this->table_program = new TableMySQLi(self::TABLES['program'], $this->db);
            $this->table_program->uint32('tour_id');
            $this->table_program->uint8('day');
            $this->table_program->string('description', 1000);

            $this->db->PushTables($this->table_types, $this->table_group, $this->table_tour, $this->table_program);
		}

	}