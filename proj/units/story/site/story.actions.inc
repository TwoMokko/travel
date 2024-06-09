<?php

	namespace Proj\Site\Actions;

	require DIR_UNITS . 'story/story.consts.inc';

	use Base\Unit;
	use Proj\Units\Consts;

	abstract class Story extends Unit implements Consts\Story {

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		public static function RegActions() {  }

	}

	Story::RegActions();