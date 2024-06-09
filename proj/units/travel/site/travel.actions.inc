<?php

	namespace Proj\Site\Actions;

	require DIR_UNITS . 'travel/travel.consts.inc';

	use Base\Unit;
	use Proj\Units\Consts;

	abstract class Travel extends Unit implements Consts\Travel {

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		public static function RegActions() {  }

	}

	Travel::RegActions();