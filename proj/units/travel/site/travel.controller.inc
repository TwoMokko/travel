<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'travel/site/travel.actions.inc';
	require DIR_UNITS . 'travel/site/travel.model.inc';

	require DIR_UNITS . 'travel/site/views/takeThings.tpl';
	require DIR_UNITS . 'travel/site/views/carousel.tpl';
	require DIR_UNITS . 'travel/site/views/about.tpl';
	require DIR_UNITS . 'travel/site/views/video.tpl';
	require DIR_UNITS . 'travel/site/views/expense.tpl';
	require DIR_UNITS . 'travel/site/views/program.tpl';
	require DIR_UNITS . 'travel/site/views/select.tpl';
	require DIR_UNITS . 'travel/site/views/types.tpl';
	require DIR_UNITS . 'travel/site/views/tours.tpl';

	use Base\Instance;
	use Proj\Units\Consts;
	use Proj\Site\Actions;
	use Proj\Site\Model;
	use Proj\Site\Templates as TPLs;

	class Travel extends Actions\Travel {
		use Instance;

		private function __construct() {
			parent::__construct(__FILE__);
		}

		public function Show(array $data): array {
			$expenses = Model\Travel::instance()->GetExpense($data['gid']);
			$additional_expenses = Model\Travel::instance()->GetAdditionalExpense($data['gid']);
			$program = Model\Travel::instance()->GetProgram($data['id']);

			return [
				TPLs\Travel\About::ToVar($data),
				$data['video'] ? TPLs\Travel\Video::ToVar($data) : '',
				TPLs\Travel\Expense::ToVar($data, $expenses, $additional_expenses),
				TPLs\Travel\Program::ToVar($program)
			];
		}

        public function GetHeaderForItem($id): string {
			$data = Model\Travel::instance()->GetInfoForHeader($id);

			$path = Consts\Travel::PATH_TOUR_ORIGINAL_RELATIVE . $data['image'];

			return TPLs\General\HeaderForPages::ToVar($path, $data['name'], $data['date']);
        }

		public function GetThings(): string { return TPLs\Travel\TakeThings::ToVar(); }

		public function GetCarousel($id): string {
			$items = Model\Travel::instance()->GetToursForCarousel($id);

            if (!$items) return '';

			return TPLs\Travel\Carousel::ToVar($items);
		}

        public function GetViewSelect(): string {
			$data = Model\Travel::instance()->GetDataForSelect();

			return TPLs\Travel\Select::ToVar($data);
        }

        public function GetViewTypes(): string {
			$data = Model\Travel::instance()->GetTypes();

            return TPLs\Travel\Types::ToVar($data);
        }

		public function HeaderTours(): string {
			$image = Model\General::instance()->GetImage('tour');
			$subhead = Model\General::instance()->GetText('subhead_tours');

			return TPLs\General\HeaderForPages::ToVar($image, 'Путешествия', $subhead);
		}

        public function GetViewTours(): string {
			$items = Model\Travel::instance()->GetTours();

            return TPLs\Travel\Tours::ToVar($items);
        }

	}

	Travel::init();