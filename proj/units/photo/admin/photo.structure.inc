<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'photo/admin/photo.actions.inc';

	use Base\DB\MySQLi\Table;
	use Proj\Admin\Actions;
	use Proj\DBObject;

	class Photo extends Actions\Photo {
		private DBObject $db;

		protected Table $table_photo_all;
		protected Table $table_photo_show;

		protected function __construct(string $file) {
			parent::__construct($file);
			$this->db = DBObject::instance();

			$this->table_photo_all = new Table(self::TABLES['photo_all'], $this->db);
			$this->table_photo_all->id('id');
			$this->table_photo_all->uint8('state');
			$this->table_photo_all->timestamp('date_create');
			$this->table_photo_all->timestamp('date_modify');
			$this->table_photo_all->string('header', 50);
			$this->table_photo_all->string('hash', 32);
			$this->table_photo_all->string('ext', 6);

			$this->table_photo_show = new Table(self::TABLES['photo_show'], $this->db);
			$this->table_photo_show->id('id');
			$this->table_photo_show->uint32('all_id');
			$this->table_photo_show->string('u_id', 13);
			$this->table_photo_show->uint8('state');
			$this->table_photo_show->timestamp('date_create');
			$this->table_photo_show->timestamp('date_modify');
			$this->table_photo_show->string('hash', 32);
			$this->table_photo_show->string('ext', 6);

			$this->db->PushTables($this->table_photo_all, $this->table_photo_show);
		}

	}