<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'general/site/general.actions.inc';
	require DIR_UNITS . 'general/site/general.model.inc';

	use Base\Instance;
	use Proj\Site\Actions;

	class General extends Actions\General {
		use Instance;

		private function __construct() {
			parent::__construct(__FILE__);
		}

	}

	General::init();