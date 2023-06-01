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
		protected TableMySQLi $table_image;

		protected function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBObject::instance();

			$this->table_text = new TableMySQLi(self::TABLES['text'], $this->db);
			$this->table_text->id('id');
			$this->table_text->uint8('state');
//			$this->table_text->timestamp('date_create');
//			$this->table_text->timestamp('date_modify');
			$this->table_text->string('alias', 20);
			$this->table_text->text('text');

			$this->table_image = new TableMySQLi(self::TABLES['image'], $this->db);
			$this->table_image->id('id');
			$this->table_image->uint8('state');
			$this->table_image->string('name', 50);
			$this->table_image->string('hash', 32);
			$this->table_image->string('ext', 6);

			$this->db->PushTables($this->table_text, $this->table_image);
		}

	}