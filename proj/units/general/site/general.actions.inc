<?php

	namespace Proj\Site\Actions;

	require DIR_UNITS . 'general/general.consts.inc';

	use Base\Unit;
	use Proj\Units\Consts;

	abstract class General extends Unit implements Consts\General {

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		public static function RegActions() {  }

	}

	General::RegActions();