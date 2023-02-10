<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'general/consts.inc';
	require DIR_UNITS . 'general/site/views/header.tpl';
	require DIR_UNITS . 'general/site/views/footer.tpl';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Units;
	use Proj\Units\Consts;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\General\Header;
	use Proj\Site\Templates\General\Footer;

	class General extends Units implements Consts\General {
		use Instance;

		private Action $header;
		private Action $tours;
		private Action $tour;
		private Action $footer;
		private Action $set_data_page;
		private Action $set_seo_main;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);

			$this->set_data_page	= new Action('always', 'always');
			$this->set_seo_main	= new Action();

			$this->header = new Action('always', 'always');
			$this->footer = new Action('always', 'always');

			Controller::instance()->view->Push($this->set_data_page, [$this, 'SetDataPage']);
			Controller::instance()->view->Push($this->set_seo_main, [$this, 'SetSeoForMain']);

			Controller::instance()->view->Push($this->header, [$this, 'Top']);
			Controller::instance()->view->Push($this->footer, [$this, 'Footer']);
		}

		public function Top() {
			Layout::instance()->header->Push(Header::object()->ToVar());
		}

		public function Footer() {
			Layout::instance()->footer->Push(Footer::object()->ToVar());
		}

		public function SetDataPage() {
			$path = [];
			if (Controller::$area != 'null') $path[] = Controller::$area;
			if (Controller::$part != 'null') $path[] = Controller::$part;
			$value = $path ? implode('_', $path) : 'main';
			Layout::SetDataPage($value);
		}

		public function SetSeoForMain() {
			Layout::SetTitle('I Da Travel | Главная');
			Layout::SetDescription('Недорогие туры на Алтай. Всем рады.');
		}

	}

	General::init();