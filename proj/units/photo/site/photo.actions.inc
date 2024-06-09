<?php

	namespace Proj\Site\Actions;

	use Base\Unit;
	use Proj\Units\Consts;

	require DIR_UNITS . 'photo/photo.consts.inc';

	abstract class Photo extends Unit implements Consts\Photo {

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		public static function RegActions() {  }

	}

	Photo::RegActions();