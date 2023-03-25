<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'general/consts.inc';
	require DIR_UNITS . 'general/site/views/header.tpl';
    require DIR_UNITS . 'general/site/views/headerForMain.tpl';
    require DIR_UNITS . 'general/site/views/headerForPages.tpl';
    require DIR_UNITS . 'general/site/views/footer.tpl';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Units;
	use Proj\Site\Templates\Template;
	use Proj\Units\Consts;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\General\HeaderForMain;
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

			$this->set_data_page = new Action('always', 'always');
			$this->set_seo_main	= new Action();

			$this->header = new Action();
			$this->footer = new Action('always', 'always');

			Controller::instance()->view->Push($this->set_data_page, [$this, 'SetDataPage']);
			Controller::instance()->view->Push($this->set_seo_main, [$this, 'SetSeoForMain']);

			Controller::instance()->view->Push($this->header, [$this, 'Header']);
			Controller::instance()->view->Push($this->footer, [$this, 'Footer']);
		}

		public function Header() {
            Layout::instance()->header->Push(HeaderForMain::ToVar());
		}

		public function Footer() {
			Layout::instance()->footer->Push(Footer::ToVar());
		}

		public function SetDataPage() {
			$path = [];
			if (Controller::$area != 'null') $path[] = Controller::$area;
			if (Controller::$part != 'null') $path[] = Controller::$part;
			$value = $path ? implode('_', $path) : 'main';
			Template::instance()->SetDataPage($value);
		}

		public function SetSeoForMain() {
			Template::instance()->SetTitle('I Da Travel | Главная');
			Template::instance()->SetDescription('Недорогие туры на Алтай. Всем рады.');
		}

	}

	General::init();