<?php

	namespace Proj\Site\Model;

	use Base\Model;
	use Base\Instance;
	use Proj\Units\Consts;
	use Proj\DBQuery;

	class General extends Model {
		use Instance;

		private DBQuery $db;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->db = DBQuery::instance();
		}

		public function GetImage(string $name): string { return Consts\General::PATH_IMAGE_RELATIVE . $this->db->SelectOneFieldCalc(Consts\General::TABLES['image'], "CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`", 'image',  "`alias` = '{$name}'"); }

		public function GetText(string $alias): string { return $this->db->SelectOneField(Consts\General::TABLES['text'], 'text', "(`alias` = '{$alias}')") ?: ''; }

	}

	General::init();