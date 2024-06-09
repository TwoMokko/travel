<?php

	namespace Proj\Site\Actions;

	require DIR_UNITS . 'pages/pages.consts.inc';

	use Base\Unit;
	use Base\Action;
	use Proj\Units\Consts;

	abstract class Pages extends Unit implements Consts\Pages {
		public static Action $set_data_page;

		public static Action $footer;

		public static Action $home;
		public static Action $tours;
		public static Action $tour;
		public static Action $about;
		public static Action $stories;
		public static Action $story;
		public static Action $review;
		public static Action $albums;
		public static Action $album;

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		public static function RegActions() {
			/* html */
			self::$set_data_page		= new Action('always', 'always');

			self::$footer				= new Action('always', 'always');

			self::$home					= new Action('null', 'null', 'default');
			self::$tours                = new Action('tours', 'null', 'default');
			self::$tour                 = new Action('tours', 'show', '/tours/show?id=%id%');
			self::$about				= new Action('about', 'null', 'default');
			self::$stories              = new Action('stories', 'null', 'default');
			self::$story                = new Action('story', 'null', '/story?id=%id%');
			self::$review               = new Action('review', 'null', 'default');
			self::$albums               = new Action('albums', 'null', 'default');
			self::$album                = new Action('album', 'null', '/album?id=%id%');
		}

	}

	Pages::RegActions();