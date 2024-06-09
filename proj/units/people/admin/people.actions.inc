<?php

	namespace Proj\Admin\Actions;

	require DIR_UNITS . 'people/people.consts.inc';

	use Base\UnitAccess;
	use Proj\Units\Consts;

	abstract class People extends UnitAccess implements Consts\People {

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		public static function RegActions() {  }

	}

	People::RegActions();