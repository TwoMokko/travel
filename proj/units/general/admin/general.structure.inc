<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'general/consts.inc';

	use Base\Units;
	use Base\DB\TableMySQLi;
	use Proj\Units\Consts;
	use Proj\DBObject;

	class General extends Units implements Consts\General {
		private DBObject $db;

		protected TableMySQLi $table_text;

		protected function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBObject::instance();

			$this->table_text = new TableMySQLi(self::TABLES['text'], $this->db);
			$this->table_text->id('id');
			$this->table_text->uint8('state');
			$this->table_text->timestamp('date_create');
			$this->table_text->timestamp('date_modify');
			$this->table_text->string('alias', 20);
			$this->table_text->text('text');

			$this->db->PushTables($this->table_text);
		}

	}