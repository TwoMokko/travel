<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'review/site/review.actions.inc';
	require DIR_UNITS . 'review/site/review.model.inc';

	require DIR_UNITS . 'review/site/views/item.tpl';
	require DIR_UNITS . 'review/site/views/grid.tpl';
	require DIR_UNITS . 'review/site/views/carousel.tpl';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Helper\Response;
	use Base\Instance;
	use Proj\Units\Consts;
	use Proj\Site\Actions;
	use Proj\Site\Model;
	use Proj\Site\Templates as TPLs;
	use Closure;

	class Review extends Actions\Review {
		use Instance;

		private function __construct() {
			parent::__construct(__FILE__);

			self::$work->Push([self::ENTRY_XHR], self::$add, Closure::fromCallable([$this, 'Add']));
			self::$work->Push([self::ENTRY_XHR], self::$get, Closure::fromCallable([$this, 'Show']));
		}

		public function Header(): string {
			$image = Model\General::instance()->GetImage('review');
			$subhead = Model\General::instance()->GetText('subhead_review');

			return TPLs\General\HeaderForPages::ToVar($image, 'Отзывы', $subhead);
		}

		public function List(): string {
			return TPLs\Review\Grid::ToVar(Model\Review::instance()->GetList(), Consts\Review::AVATARS);
		}

		public function GetReviewsCarousel(): string {
			if (!$items = Model\Review::instance()->GetList()) return '';

			return TPLs\Review\Carousel::ToVar($items, Consts\Review::AVATARS);
		}

		public function GetReviewsCarouselByTourId(int $tourID): string {
			$items = Model\Review::instance()->GetReviewByTourID($tourID);

			if (!$items) return '';

			return TPLs\Review\Carousel::ToVar($items, []);
		}

		#region XHR

		#[NoReturn] public function Show(): void {
			$id = GetInt('id');

			$item = Model\Review::instance()->GetReviewByID($id);

			Response::PushData($item);
			Response::SendJSON();
		}

		#[NoReturn] public function Add(): void {
			$name = GetParam('name', '');
			$text = GetParam('text', '');
			$avatar = GetInt('avatar');

			if (!isset(self::AVATARS[$avatar])) $avatar = rand(1, count(self::AVATARS));

			$data = [
				'name' => $name,
				'text' => $text,
				'state' => Consts\Review::STATE_UNVERIFIED,
				'avatar' => $avatar
			];

			Model\Review::instance()->Add($data);

			Response::PushData([]);
			Response::SendJSON();
		}

		#endregion XHR

	}

	Review::init();