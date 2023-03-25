<?php

	namespace Proj\Admin\Templates;

	use Base\Instance;
	use Base\Templates\Section;
	use Base\Templates\Versions as BaseVersions;
	use Proj\Templates\Admin\Versions as AdminVersions;

	class Layout extends \Base\Templates\Layout {
		use Instance;

		public Section $header;
		public Section $menu;
		public Section $main;
		public Section $footer;

		public function __construct() {
			parent::__construct();

			$this->header = new Section();
			$this->menu = new Section();
			$this->main = new Section();
			$this->footer = new Section();
		}

	}

	Layout::init();