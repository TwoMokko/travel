<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'feedback/consts.inc';

	use Base\Units;
	use Base\DB\TableMySQLi;
	use Proj\Units\Consts;
	use Proj\DBObject;

	class Feedback extends Units implements Consts\Feedback {
		private DBObject $db;

		protected TableMySQLi $table_feedback;

		protected function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBObject::instance();

			$this->table_feedback = new TableMySQLi(self::TABLES['feedback'], $this->db);
			$this->table_feedback->id('id');
			$this->table_feedback->uint32('tour_id');
			$this->table_feedback->uint8('state');
            $this->table_feedback->timestamp('date_create');
            $this->table_feedback->string('name', 50);
            $this->table_feedback->string('contact', 50);
            $this->table_feedback->text('text');

			$this->db->PushTables($this->table_feedback);
		}

	}