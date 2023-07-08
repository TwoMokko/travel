<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'general/consts.inc';

	use Base\Units;
	use Base\DB\MySQLi\Table;
	use Proj\Units\Consts;
	use Proj\DBObject;

	class General extends Units implements Consts\General {
		private DBObject $db;

		protected Table $table_text;
		protected Table $table_image;

		protected function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBObject::instance();

			$this->table_text = new Table(self::TABLES['text'], $this->db);
			$this->table_text->id('id');
			$this->table_text->uint8('state');
//			$this->table_text->timestamp('date_create');
//			$this->table_text->timestamp('date_modify');
			$this->table_text->string('description', 100);
			$this->table_text->string('alias', 50);
			$this->table_text->text('text');

			$this->table_image = new Table(self::TABLES['image'], $this->db);
			$this->table_image->id('id');
			$this->table_image->uint8('state');
			$this->table_image->string('description', 100);
			$this->table_image->string('alias', 50);
			$this->table_image->string('hash', 32);
			$this->table_image->string('ext', 6);

			$this->db->PushTables($this->table_text, $this->table_image);
		}

	}