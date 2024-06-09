<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'travel/admin/travel.structure.inc';
	require DIR_UNITS . 'travel/admin/travel.model.inc';

	require DIR_UNITS . 'travel/admin/editors/tour/tour.editor.inc';
	require DIR_UNITS . 'travel/admin/editors/type/type.editor.inc';
	require DIR_UNITS . 'travel/admin/editors/direction/direction.editor.inc';

	use Base\Instance;
	use Proj\Admin\Structure;
	use Proj\Admin\Model;
	use Proj\Admin\Editor;
	use Proj\Editor\Consts as EditorConsts;

	class Travel extends Structure\Travel {
		use Instance;

		public Model\Travel $model;

		public Editor\Travel\Type $editor_type;
		public Editor\Travel\Direction $editor_direction;
		public Editor\Travel\Tour $editor_tour;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->model = Model\Travel::instance();
			$this->model->AcceptTables([$this->table_types, $this->table_group, $this->table_tour]);

			$this->editor_type = new Editor\Travel\Type(EditorConsts\ID_TOUR_TYPE, self::NAME . '_type', $this->table_types, 'Тип тура (редактор)');
			$this->editor_direction = new Editor\Travel\Direction(EditorConsts\ID_TOUR_DIRECTION, self::NAME . '_direction', [$this->table_group, $this->table_expense, $this->table_additional_expense], 'Направление туров (редактор)');
			$this->editor_tour = new Editor\Travel\Tour(EditorConsts\ID_TOUR,self::NAME . '_tour', [$this->table_tour, $this->table_program], 'Тур (редактор)');
		}

	}

	Travel::init();