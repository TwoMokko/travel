<?php

	namespace Proj\Site\Model;

	use Base\Model;
	use Base\Instance;

	class People extends Model {
		use Instance;

		private function __construct() {
			parent::__construct(__FILE__);
		}

	}

	People::init();