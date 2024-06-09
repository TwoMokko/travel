<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'review/admin/review.actions.inc';

	use Base\DB\MySQLi\Table;
	use Proj\Admin\Actions;
	use Proj\DBObject;

	class Review extends Actions\Review {
		private DBObject $db;

		protected Table $table_reviews;

		protected function __construct(string $file) {
			parent::__construct($file);
			$this->db = DBObject::instance();

			$this->table_reviews = new Table(self::TABLES['review'], $this->db);
			$this->table_reviews->id('id');
			$this->table_reviews->uint32('gid');
			$this->table_reviews->uint8('state');
            $this->table_reviews->timestamp('date_create');
            $this->table_reviews->string('name', 50);
            $this->table_reviews->uint8('avatar');
            $this->table_reviews->text('text');

			$this->db->PushTables($this->table_reviews);
		}

	}