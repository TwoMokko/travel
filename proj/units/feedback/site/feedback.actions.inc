<?php

	namespace Proj\Site\Actions;

	require DIR_UNITS . 'feedback/feedback.consts.inc';

	use Base\Unit;
	use Base\Action;
	use Proj\Units\Consts;

	abstract class Feedback extends Unit implements Consts\Feedback {
		public static Action $feedback_add;

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		public static function RegActions() {
			/* xhr */
			self::$feedback_add         = new Action('feedback', 'add', '/feedback/add?id=%id%');
		}

	}

	Feedback::RegActions();