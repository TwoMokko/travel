<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'test/consts.inc';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Units;
	use Proj\Units\Consts;

	class Test extends Units implements Consts\Test {
		use Instance;

		private Action $top;
		private Action $tours;
		private Action $tour;
		private Action $footer;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);

			$this->top = new Action('always', 'always');
			$this->tours = new Action('tours');
			$this->tour = new Action('tour');
			$this->footer = new Action('always', 'always');

			Controller::instance()->view->Push($this->top, [$this, 'Top']);
			Controller::instance()->view->Push($this->tours, [$this, 'Tours']);
			Controller::instance()->view->Push($this->tour, [$this, 'Tour']);
			Controller::instance()->view->Push($this->footer, [$this, 'Footer']);
		}

		public function Top() { ?>
			<div>Top</div>
		<?php }

		public function Tours() { ?>
			<div>Туры</div>
		<?php }

		public function Tour() { ?>
			<div>Тур</div>
		<?php }

		public function Footer() { ?>
			<div>Footer</div>
		<?php }

	}

	Test::init();