<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'tour/admin/tour.structure.inc';
	require DIR_UNITS . 'tour/admin/typeTour.editor.inc';
	require DIR_UNITS . 'tour/admin/tour.editor.inc';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Proj\Units\Consts;
	use Proj\Admin\Editor\TypeTour;
	use Proj\Admin\Editor\Tour;
	use Proj\Admin\Structure;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Group;

	class Tours extends Structure\Tour {
		use Instance;

		private TypeTour $editor_tour_types;
		private Tour $editor_tour;

		private Action $out_menu;

		private function __construct() {
			parent::__construct();

			$this->editor_tour_types = new TypeTour(self::NAME . '_type', $this->table_tour_types);
			$this->editor_tour = new Tour(self::NAME, $this->table_tour);

			$this->out_menu = new Action();

			Controller::instance()->view->Push($this->out_menu, [$this, 'OutMenu']);
		}

		public function OutMenu() {
			Layout::instance()->menu->Push(
				Group::ToVar('Типы туров', [
					$this->editor_tour_types->select->GetLink('Список типов туров', ['page' => 1]),
					$this->editor_tour_types->create->GetLink('Добавить тип тура')
				])
			);

			Layout::instance()->menu->Push(
				Group::ToVar('Тур', [
					$this->editor_tour->select->GetLink('Список туров', ['page' => 1]),
					$this->editor_tour->create->GetLink('Добавить тур')
				])
			);
		}

		public function GetTypes(): array {
			$state = Consts\Tour::STATE_ACTIVE;
			$result = $this->table_tour_types->Select(['id', 'name'], "`state` = {$state}");
			return $this->table_tour_types->FetchAll($result, function(& $types, $type) {
				$types[$type['id']] = $type['name'];
			});
		}

	}

	Tours::init();