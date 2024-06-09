<?php

	namespace Proj\Admin\Actions;

	require DIR_UNITS . 'travel/travel.consts.inc';

	use Base\UnitAccess;
	use Proj\Units\Consts;

	abstract class Travel extends UnitAccess implements Consts\Travel {

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		public static function RegActions() {  }

	}

	Travel::RegActions();