<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'feedback/admin/feedback.actions.inc';

	use Base\DB\MySQLi\Table;
	use Proj\Admin\Actions;
	use Proj\DBObject;

	class Feedback extends Actions\Feedback {
		private DBObject $db;

		protected Table $table_feedback;

		protected function __construct(string $file) {
			parent::__construct($file);
			$this->db = DBObject::instance();

			$this->table_feedback = new Table(self::TABLES['feedback'], $this->db);
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