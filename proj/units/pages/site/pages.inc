<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'pages/consts.inc';


	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Units;
	use JetBrains\PhpStorm\NoReturn;
	use Proj\Site\Templates\Template;
	use Proj\Units\Consts;
	use Proj\Site;
	use Proj\Site\Templates\Layout;

	class Pages extends Units implements Consts\Pages {
		use Instance;

		public Action $always;
		public Action $main;
		public Action $tours;
		public Action $tour;
		public Action $about;
		public Action $stories;
		public Action $story;
		public Action $photos;
		public Action $photo;
		public Action $review;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);

			$this->always = new Action('always', 'always');
			$this->main = new Action('null', 'null');
			$this->tours = new Action('tours', 'null', 'default');
			$this->tour = new Action('tours', 'show', '/tours/show?id=%id%');
			$this->about = new Action('about', 'null', 'default');
			$this->stories = new Action('stories', 'null', 'default');
			$this->story = new Action('stories', 'show', '/stories/show?id=%id%');
			$this->photos = new Action('photo', 'null', 'default');
			$this->photo = new Action('photo', 'show', '/photo/show?id=%id%');
			$this->review = new Action('review', 'null', 'default');

			Controller::instance()->view->Push($this->always, [$this, 'Always']);
			Controller::instance()->view->Push($this->main, [$this, 'Main']);
			Controller::instance()->view->Push($this->tours, [$this, 'Tours']);
			Controller::instance()->view->Push($this->tour, [$this, 'Tour']);
			Controller::instance()->view->Push($this->about, [$this, 'About']);
			Controller::instance()->view->Push($this->stories, [$this, 'Stories']);
			Controller::instance()->view->Push($this->story, [$this, 'Story']);
			Controller::instance()->view->Push($this->photos, [$this, 'Photos']);
			Controller::instance()->view->Push($this->photo, [$this, 'Photo']);
			Controller::instance()->view->Push($this->review, [$this, 'Review']);
		}

		public function Always(): void {
			General::instance()->SetDataPage();
			Layout::instance()->main->Push(General::instance()->ScrollTop());
			Layout::instance()->footer->Push(General::instance()->Footer());
		}

        public function Main(): void {
			Template::instance()->SetTitle('I Da Travel | Главная');
			Template::instance()->SetDescription('Недорогие туры на Алтай. Всем рады.');
			Layout::instance()->header->Push(General::instance()->GetHeader());
			Layout::instance()->main->Push(
				Tour::instance()->GetSelect(),
				General::instance()->GetAboutMain(),
				Tour::instance()->GetTypes(),
				General::instance()->GetStoryMain(),
				Photo::instance()->ForMain(),
				Reviews::instance()->GetReviewsForMain()
			);
        }

		public function Tours(): void {
			Template::instance()->SetTitle('Путешествия');
			Template::instance()->SetDescription('Недорогие туры на Алтай. Всем рады.');
			Layout::instance()->header->Push(Tour::instance()->GetHeaderForAll());
			Layout::instance()->main->Push(Tour::instance()->GetAllTours());
		}

		public function Tour(): void {
			$id = GetInt('id');
			if (!$id) $this->Error404();
			Tour::instance()->SetSeoForItem($id);
			Layout::instance()->header->Push(Tour::instance()->GetHeaderForItem($id));
			Tour::instance()->Show($id);
			Layout::instance()->main->Push(
				Photo::instance()->ForTour(),
				Tour::instance()->GetThings(),
				Feedback::instance()->ForTour($id),
				Tour::instance()->GetCarousel($id),
				Reviews::instance()->ForTour($id)
			);
		}

		public function About(): void {
			Template::instance()->SetTitle('О нас');
			Template::instance()->SetDescription('');
			Layout::instance()->header->Push(People::instance()->Header());
			Layout::instance()->main->Push(
				General::instance()->AboutPage(),
				People::instance()->Team()
			);
		}

		public function Stories(): void {
			Template::instance()->SetTitle('Приключения');
			Template::instance()->SetDescription('');
			Layout::instance()->header->Push(Story::instance()->HeaderForAll());
			Layout::instance()->main->Push(
				Story::instance()->All()
			);
		}

		public function Story(): void {
			Story::instance()->SetSeoForShow();
			Layout::instance()->header->Push(Story::instance()->HeaderForItem());
			Layout::instance()->main->Push(
				Story::instance()->Show(),
				Story::instance()->Carousel()
			);
		}

		public function Photos(): void {
			Template::instance()->SetTitle('Фотографии');
			Template::instance()->SetDescription('');
			Layout::instance()->header->Push(Photo::instance()->HeaderForAll());
			Layout::instance()->main->Push(Photo::instance()->All());
		}

		public function Photo(): void {
			Photo::instance()->SetSeoForShow();
			Layout::instance()->header->Push(Photo::instance()->HeaderForItem());
			Layout::instance()->main->Push(Photo::instance()->Show());
		}

		public function Review(): void {
			Template::instance()->SetTitle('Отзывы');
			Template::instance()->SetDescription('');
			Layout::instance()->header->Push(Reviews::instance()->Header());
			Layout::instance()->main->Push(Reviews::instance()->ForList());
		}

		#[NoReturn] public function Error404(): void {
			header("Location: {$this->main->GetHref()}"); die;
		}

	}

	Pages::init();