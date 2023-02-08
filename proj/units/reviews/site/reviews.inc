<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'reviews/consts.inc';
	require DIR_UNITS . 'reviews/site/views/forMain.tpl';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Units;
	use Proj\Units\Consts;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\Reviews\ForMain;

	class Reviews extends Units implements Consts\Reviews {
		use Instance;

		private Action $review;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);

			$this->review = new Action();

			Controller::instance()->view->Push($this->review, [$this, 'ForMain']);
		}

		public function ForMain() {
			Layout::instance()->main->Push(ForMain::object()->ToVar());
		}

	}

	Reviews::init();