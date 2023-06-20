<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'general/consts.inc';
	require DIR_UNITS . 'general/site/views/header.tpl';
    require DIR_UNITS . 'general/site/views/headerForMain.tpl';
    require DIR_UNITS . 'general/site/views/headerForPages.tpl';
    require DIR_UNITS . 'general/site/views/footer.tpl';
    require DIR_UNITS . 'general/site/views/other.tpl';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Units;
	use Proj\DBQuery;
	use Proj\Site\Templates\Template;
	use Proj\Units\Consts;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\General\HeaderForMain;
	use Proj\Site\Templates\General\Footer;
	use Proj\Site\Templates\General\Other;

	class General extends Units implements Consts\General {
		use Instance;

		private DBQuery $db;

		private Action $header;
		private Action $tours;
		private Action $tour;
		private Action $footer;
		private Action $set_data_page;
		private Action $scroll_top;
		private Action $set_seo_main;
		private Action $about_main;
		private Action $about_page;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBQuery::instance();

			$this->set_data_page 	= new Action('always', 'always');
			$this->scroll_top 	    = new Action('always', 'always');
			$this->set_seo_main		= new Action();
			$this->about_main		= new Action();
			$this->about_page		= new Action('about');

			$this->header 			= new Action();
			$this->footer 			= new Action('always', 'always');

			Controller::instance()->view->Push($this->set_data_page, [$this, 'SetDataPage']);
			Controller::instance()->view->Push($this->scroll_top, [$this, 'ScrollTop']);
			Controller::instance()->view->Push($this->set_seo_main, [$this, 'SetSeoForMain']);
			Controller::instance()->view->Push($this->about_main, [$this, 'AboutMain'], [$this, 'StoryMain']);
			Controller::instance()->view->Push($this->about_page, [$this, 'AboutPage'], [$this, 'SetSeoForAbout']);

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

        public function ScrollTop() {
            Layout::instance()->main->Push(Other::ScrollTop());
        }

		public function SetSeoForMain() {
			Template::instance()->SetTitle('I Da Travel | Главная');
			Template::instance()->SetDescription('Недорогие туры на Алтай. Всем рады.');
		}

		public function AboutMain(): void {
			$main_about_header = $this->db->SelectOneField(self::TABLES['text'], 'text', "(`alias` = 'main_about_header')") ?: '';
			$main_about_text = $this->db->SelectOneField(self::TABLES['text'], 'text', "(`alias` = 'main_about_text')") ?: '';

			Layout::instance()->main->Push(Other::AboutMain($main_about_header, $main_about_text));
		}

		public function StoryMain(): void {
			$main_story_header = $this->db->SelectOneField(self::TABLES['text'], 'text', "(`alias` = 'main_story_header')") ?: '';
			$main_story_text = $this->db->SelectOneField(self::TABLES['text'], 'text', "(`alias` = 'main_story_text')") ?: '';
			$main_story_button = $this->db->SelectOneField(self::TABLES['text'], 'text', "(`alias` = 'main_story_button')") ?: '';

			Layout::instance()->main->Push(Other::StoryMain($main_story_header, $main_story_text, $main_story_button));
		}

		public function AboutPage(): void {
			$page_about_header = $this->db->SelectOneField(self::TABLES['text'], 'text', "(`alias` = 'page_about_header')") ?: '';
			$page_about_text = $this->db->SelectOneField(self::TABLES['text'], 'text', "(`alias` = 'page_about_text')") ?: '';
			$page_about_mini_text = $this->db->SelectOneField(self::TABLES['text'], 'text', "(`alias` = 'page_about_mini_text')") ?: '';
			$image = $this->GetImage('about_description');

			Layout::instance()->main->Push(Other::AboutPage($page_about_header, $page_about_text, $page_about_mini_text, $image));
		}

		public function SetSeoForAbout() {
			Template::instance()->SetTitle('О нас');
			Template::instance()->SetDescription('');
		}

		public function GetImage(string $name): string {
			return Consts\General::PATH_IMAGE_RELATIVE . $this->db->SelectOneFieldCalc(self::TABLES['image'], "CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`", 'image',  "`name` = '{$name}'");
		}

		public function GetText(string $alias): string {
			return $this->db->SelectOneField(self::TABLES['text'], 'text', "(`alias` = '{$alias}')") ?: '';
		}

	}

	General::init();