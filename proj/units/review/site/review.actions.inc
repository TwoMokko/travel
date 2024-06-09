<?php

	namespace Proj\Site\Actions;

	require DIR_UNITS . 'review/review.consts.inc';

	use Base\Unit;
	use Base\Action;
	use Proj\Units\Consts;

	abstract class Review extends Unit implements Consts\Review {

		public static Action $get;
		public static Action $add;

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		public static function RegActions() {
			self::$get = new Action('review', 'get');
			self::$add = new Action('review', 'add');
		}

	}

	Review::RegActions();