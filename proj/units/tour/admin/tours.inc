<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'tour/admin/tour.structure.inc';
	require DIR_UNITS . 'tour/admin/typeTour.editor.inc';
	require DIR_UNITS . 'tour/admin/tourGroup.editor.inc';
	require DIR_UNITS . 'tour/admin/tour.editor.inc';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Proj\Units\Consts;
	use Proj\Admin\Editor;
	use Proj\Admin\Structure;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Group;

	class Tours extends Structure\Tour {
		use Instance;

		private Editor\TypeTour $editor_tour_types;
		private Editor\TourGroup $editor_tour_group;
		private Editor\Tour $editor_tour;

		private Action $out_menu;

		private function __construct() {
			parent::__construct();

			$this->editor_tour_types = new Editor\TypeTour(self::NAME . '_type', $this->table_types);
			$this->editor_tour_group = new Editor\TourGroup(self::NAME . '_group', [$this->table_group, $this->table_expense, $this->table_additional_expense]);
			$this->editor_tour = new Editor\Tour(self::NAME, [$this->table_tour, $this->table_program]);

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
				Group::ToVar('Направление тура', [
					$this->editor_tour_group->select->GetLink('Список направлений тура', ['page' => 1]),
					$this->editor_tour_group->create->GetLink('Добавить направление тура')
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
			$result = $this->table_types->Select(['id', 'name'], "`state` = {$state}");
			return $this->table_types->FetchAll($result, function(& $types, $type) {
				$types[$type['id']] = $type['name'];
			});
		}

		public function GetGroupTour(): array {
			$state = Consts\Tour::STATE_ACTIVE;
			$result = $this->table_group->Select(['id', 'name'], "`state` = {$state}");
			return $this->table_group->FetchAll($result, function(& $groups, $group) {
                $groups[$group['id']] = $group['name'];
			});
		}

        public function GetTours(): array {
            $state_active = Consts\Tour::STATE_ACTIVE;
            $state_inactive = Consts\Tour::STATE_INACTIVE;
            $result = $this->table_tour->Select(['id', 'name'], "`state` = {$state_active} OR `state` = {$state_inactive}");
            return $this->table_tour->FetchAll($result, function(& $tours, $tour) {
                $tours[$tour['id']] = $tour['name'];
            });
        }

	}

	Tours::init();