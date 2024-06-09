<?php

	namespace Proj\Site\Model;

	use Base\Instance;
	use Base\Model;
	use Proj\DBQuery;
	use Proj\Units\Consts;

	class Feedback extends Model {
		use Instance;

		private DBQuery $db;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->db = DBQuery::instance();
		}

		public function AddFeedback(array $data): void {
			$data['name'] = $this->db->Escaping($data['name']);
			$data['contact'] = $this->db->Escaping($data['contact']);
			$data['text'] = $this->db->Escaping($data['text']);

			$this->db->Insert(Consts\Feedback::TABLES['feedback'], $data);
		}

	}

	Feedback::init();