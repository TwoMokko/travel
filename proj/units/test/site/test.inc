<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'test/consts.inc';
	require 'views/header.tpl';
	require 'views/footer.tpl';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Units;
	use Proj\Units\Consts;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\Test\Header;
	use Proj\Site\Templates\Test\Footer;

	class Test extends Units implements Consts\Test {
		use Instance;

		private Action $header;
		private Action $tours;
		private Action $tour;
		private Action $footer;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);

			$this->header = new Action('always', 'always');
//			$this->tours = new Action('tours');
//			$this->tour = new Action('tour');
			$this->footer = new Action('always', 'always');

			Controller::instance()->view->Push($this->header, [$this, 'Top']);
//			Controller::instance()->view->Push($this->tours, [$this, 'Tours']);
//			Controller::instance()->view->Push($this->tour, [$this, 'Tour']);
			Controller::instance()->view->Push($this->footer, [$this, 'Footer']);
		}

		public function Top() {
			Layout::instance()->header->Push(Header::object()->ToVar());
		}

		public function Tours() { ?>
			<div>Туры</div>
		<?php }

		public function Tour() { ?>
			<div>Тур</div>
		<?php }

		public function Footer() {
			Layout::instance()->footer->Push(Footer::object()->ToVar());
		}

	}

	Test::init();