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

			$this->main = new Action('null', 'null');
			$this->tours = new Action('tours', 'null');
			$this->tour = new Action('tours', 'show', '/tours/show?id=%id%');
			$this->about = new Action('about', 'null');
			$this->stories = new Action('stories', 'null', 'default');
			$this->story = new Action('stories', 'show', '/stories/show?id=%id%');
			$this->photos = new Action('photo', 'null');
			$this->photo = new Action('photo', 'show', '/photo/show?id=%id%');
			$this->review = new Action('review', 'null');

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

        public function Main(): void {
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
			Layout::instance()->main->Push(
				Tour::instance()->GetHeaderForAll(),
				Tour::instance()->GetAllTours()
			);
		}

		public function Tour(): void {
			$id = GetInt('id');
			if (!$id) $this->Error404();
//			Tour::instance()->GetHeaderForItem($id);
			Tour::instance()->Show($id);
			Photo::instance()->ForTour();
			Tour::instance()->GetThings();
			Feedback::instance()->ForTour();
			Tour::instance()->GetCarousel();
			Reviews::instance()->ForTour();
		}

		public function About(): void {
			Layout::instance()->main->Push(
				General::instance()->AboutPage(),
				People::instance()->Team()
			);
		}

		public function Stories(): void {
			Layout::instance()->main->Push(
				Story::instance()->All()
			);
		}

		public function Story(): void {
			Layout::instance()->main->Push(
				Story::instance()->Show(),
				Story::instance()->Carousel()
			);
		}

		public function Photos(): void {
			Layout::instance()->main->Push(
				Photo::instance()->All()
			);
		}

		public function Photo(): void {
			Layout::instance()->main->Push(
				Photo::instance()->Show()
			);
		}

		public function Review(): void {
			Layout::instance()->main->Push(
				Reviews::instance()->ForList()
			);
		}

		#[NoReturn] public function Error404(): void {
			header("Location: {$this->main->GetHref()}"); die;
		}

	}

	Pages::init();