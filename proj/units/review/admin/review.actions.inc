<?php

	namespace Proj\Admin\Actions;

	require DIR_UNITS . 'review/review.consts.inc';

	use Base\UnitAccess;
	use Proj\Units\Consts;

	abstract class Review extends UnitAccess implements Consts\Review {

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		public static function RegActions() {  }

	}

	Review::RegActions();