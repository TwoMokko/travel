<?php

	namespace Proj\Admin\Actions;

	require DIR_UNITS . 'photo/photo.consts.inc';

	use Base\UnitAccess;
	use Proj\Units\Consts;

	abstract class Photo extends UnitAccess implements Consts\Photo {

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		public static function RegActions() {  }

	}

	Photo::RegActions();