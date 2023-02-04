<?php

	namespace Proj\Site\Templates\Test;

	use Base\Templates\View;

	class Header extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render() { ?>
			<div>Top</div>
		<?php }

	}