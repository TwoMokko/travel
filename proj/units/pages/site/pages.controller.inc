<?php

	namespace Proj\Site\Units;

    require DIR_UNITS . 'pages/site/pages.actions.inc';

	require DIR_UNITS . 'pages/site/views/footer.tpl';
	require DIR_UNITS . 'pages/site/views/scroll.tpl';
	require DIR_UNITS . 'pages/site/views/header.tpl';
	require DIR_UNITS . 'pages/site/views/headerForMain.tpl';
	require DIR_UNITS . 'pages/site/views/headerForPages.tpl';
    require DIR_UNITS . 'pages/site/views/aboutForMain.tpl';
    require DIR_UNITS . 'pages/site/views/aboutForAbout.tpl';
    require DIR_UNITS . 'pages/site/views/storyForMain.tpl';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Instance;
	use Proj\Site\Actions;
	use Proj\Site\Model;
	use Proj\Site\Model\General;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\Template;
	use Proj\Site\Templates as TPLs;
	use Proj\Params;
	use Closure;

	class Pages extends Actions\Pages {
		use Instance;

		private function __construct() {
			parent::__construct(__FILE__);

			self::$view->Push([self::ENTRY_HTML], self::$set_data_page, Closure::fromCallable([$this, 'SetDataPage']));

			self::$view->Push([self::ENTRY_HTML], self::$home, Closure::fromCallable([$this, 'Home']));
			self::$view->Push([self::ENTRY_HTML], self::$tours, Closure::fromCallable([$this, 'Tours']));
			self::$view->Push([self::ENTRY_HTML], self::$tour, Closure::fromCallable([$this, 'Tour']));
			self::$view->Push([self::ENTRY_HTML], self::$about, Closure::fromCallable([$this, 'About']));
			self::$view->Push([self::ENTRY_HTML], self::$stories, Closure::fromCallable([$this, 'Stories']));
			self::$view->Push([self::ENTRY_HTML], self::$story, Closure::fromCallable([$this, 'Story']));
			self::$view->Push([self::ENTRY_HTML], self::$review, Closure::fromCallable([$this, 'Review']));
			self::$view->Push([self::ENTRY_HTML], self::$albums, Closure::fromCallable([$this, 'Albums']));
			self::$view->Push([self::ENTRY_HTML], self::$album, Closure::fromCallable([$this, 'Album']));

			self::$view->Push([self::ENTRY_HTML], self::$footer, Closure::fromCallable([$this, 'OutFooter']));
		}

		#region HTML

		private function SetDataPage() {
			$path = [];
			if (self::$area != 'null') $path[] = self::$area;
			if (self::$part != 'null') $path[] = self::$part;
			$value = $path ? implode('_', $path) : 'main';
			Template::instance()->SetDataPage($value);
		}

		private function Home() {
			Template::instance()->SetTitle(Params::$company['name'] . ' | Главная');
			Template::instance()->SetDescription('');
			Template::instance()->SetKeywords('');

			Layout::instance()->header->Push(
				TPLs\Pages\HeaderForMain::ToVar(
					Model\General::instance()->GetText('main_header1'),
					Model\General::instance()->GetText('main_header2'),
					Model\General::instance()->GetText('main_header3')
				),
				Travel::instance()->GetViewSelect(),
				TPLs\Pages\AboutForMain::ToVar(
					Model\General::instance()->GetText('main_about_header'),
					Model\General::instance()->GetText('main_about_text')
				),
				Travel::instance()->GetViewTypes(),
				TPLs\Pages\StoryForMain::ToVar(
					Model\General::instance()->GetText('main_story_header'),
					Model\General::instance()->GetText('main_story_text'),
					Model\General::instance()->GetText('main_story_button')
				),
				Photo::instance()->ForMain(),
				Review::instance()->GetReviewsCarousel()
			);
		}

		private function About() {
			Template::instance()->SetTitle(Params::$company['name'] . ' | О нас');
			Template::instance()->SetDescription('');
			Template::instance()->SetKeywords('');

			$page_about_header = General::instance()->GetText('page_about_header');
			$page_about_text = General::instance()->GetText('page_about_text');
			$page_about_mini_text = General::instance()->GetText('page_about_mini_text');
			$page_about_video = General::instance()->GetText('page_about_video');
			$image = General::instance()->GetImage('about_description');

			Layout::instance()->header->Push(People::instance()->Header());
			Layout::instance()->main->Push(
				TPLs\Pages\AboutForAbout::ToVar($page_about_header, $page_about_text, $page_about_mini_text, $page_about_video, $image),
				People::instance()->Team()
			);
		}

		public function Review(): void {
			Template::instance()->SetTitle(Params::$company['name'] . ' | Отзывы');
			Template::instance()->SetDescription('');
			Template::instance()->SetKeywords('');

			Layout::instance()->header->Push(Review::instance()->Header());
			Layout::instance()->main->Push(Review::instance()->List());
		}

		public function Tours(): void {
			Template::instance()->SetTitle(Params::$company['name'] . ' | Путешествия');
			Template::instance()->SetDescription('');
			Template::instance()->SetKeywords('');

			Layout::instance()->header->Push(Travel::instance()->HeaderTours());
			Layout::instance()->main->Push(Travel::instance()->GetViewTours());
		}

		public function Tour(): void {
			$id = GetInt('id');

			$data = Model\Travel::instance()->GetData($id);
			if (!$data) Pages::instance()->Error404();

			$seo = Model\Travel::instance()->GetSeoForTour($id);
			Template::instance()->SetTitle(Params::$company['name'] . " | {$seo['title']}");
			Template::instance()->SetDescription($seo['description']);
			Template::instance()->SetKeywords('');

			Layout::instance()->header->Push(Travel::instance()->GetHeaderForItem($id));
			Layout::instance()->main->Push(...Travel::instance()->Show($data));
			Layout::instance()->main->Push(
				Photo::instance()->ForTour($data['photo_id']),
				Travel::instance()->GetThings(),
				Feedback::instance()->ForTour($id),
				Travel::instance()->GetCarousel($id),
				Review::instance()->GetReviewsCarouselByTourId($id)
			);
		}

		public function OutFooter(): void {
			Layout::instance()->footer->Push(TPLs\Pages\Footer::ToVar());
			Layout::instance()->footer->Push(TPLs\Pages\Scroll::ToVar());
		}

		public function Stories(): void {
			Template::instance()->SetTitle(Params::$company['name'] . ' | Приключения');
			Template::instance()->SetDescription('');
			Template::instance()->SetKeywords('');

			$image = General::instance()->GetImage('story');
			$text = General::instance()->GetText('subhead_stories');

			Layout::instance()->header->Push(
				TPLs\General\HeaderForPages::ToVar($image, 'Дневник путешествий', $text)
			);
			Layout::instance()->main->Push(
				Story::instance()->List()
			);
		}

		public function Story(): void {
			$id = GetInt('id');

			$title = Model\Story::instance()->GetTitle($id);

			Template::instance()->SetTitle(Params::$company['name'] . " | {$title}");
			Template::instance()->SetDescription('');
			Template::instance()->SetKeywords('');

			Layout::instance()->header->Push(Story::instance()->HeaderForItem($id));
			Layout::instance()->main->Push(
				Story::instance()->Show($id),
				Story::instance()->Carousel($id, 20)
			);
		}

		public function Albums(): void {
			Template::instance()->SetTitle(Params::$company['name'] . ' | Фотоальбомы');
			Template::instance()->SetDescription('');
			Template::instance()->SetKeywords('');

			Layout::instance()->header->Push(Photo::instance()->HeaderForAlbums());
			Layout::instance()->main->Push(Photo::instance()->Albums());
		}

		public function Album(): void {
			if (!$id = GetInt('id')) die;

			Template::instance()->SetTitle(Params::$company['name'] . ' | Фотоальбом');
			Template::instance()->SetDescription('');
			Template::instance()->SetKeywords('');

			Layout::instance()->header->Push(Photo::instance()->HeaderForItem($id));
			Layout::instance()->main->Push(Photo::instance()->Album());
		}

		#endregion HTML

		#[NoReturn] public function Error404(): void {
			header('Location: ' . self::$home->GetHref());
			die;
		}

	}

	Pages::init();