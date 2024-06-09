<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'story/site/story.actions.inc';
	require DIR_UNITS . 'story/site/story.model.inc';

	require DIR_UNITS . 'story/site/views/all.tpl';
	require DIR_UNITS . 'story/site/views/show.tpl';
	require DIR_UNITS . 'story/site/views/carousel.tpl';

	use Base\Instance;
	use Proj\Site\Actions;
	use Proj\Site\Model;
	use Proj\Site\Templates as TPLs;

	class Story extends Actions\Story {
		use Instance;

		private function __construct() {
			parent::__construct(__FILE__);
		}

        public function HeaderForItem(int $id): string {
			$title = Model\Story::instance()->GetTitle($id);

            $image = Model\General::instance()->GetImage('story');
            $text = Model\General::instance()->GetText('subhead_one_story');

            return TPLs\General\HeaderForPages::ToVar($image, $title, $text);
		}

		public function List(): string {
			$items = Model\Story::instance()->GetList();
			return TPLs\Story\All::ToVar($items);
		}

		public function Show(int $id): string {
			$item = Model\Story::instance()->GetStoryByID($id);

			return $item ? TPLs\Story\Show::ToVar($item) : '';
		}

        public function Carousel(int $id, int $limit): string {
            $items = Model\Story::instance()->GetListNotId($id, $limit);

            return $items ? TPLs\Story\Carousel::ToVar($items) : '';
        }

	}

	Story::init();