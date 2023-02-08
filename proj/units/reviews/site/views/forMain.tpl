<?php

namespace Proj\Site\Templates\Reviews;

use Base\Templates\View;

class ForMain extends View {

	public function ToVar(): string {
		$this->Start();
		$this->Render();
		return $this->Read();
	}

	public function Render() { ?>
		<div>1</div>
	<?php }

}