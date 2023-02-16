<?php

	namespace Proj\Site\Templates\Stories;

	use Base\Templates\View;

	class All extends View {

		public function ToVar(array $items): string {
			$this->Start();
			$this->Render($items);
			return $this->Read();
		}

		public function Render($items) { ?>
			<div class = "block page_adventure p">
				<div class = "cards_adventure">
					<?php foreach ($items as $item) $this->Item($item); ?>
				</div>
			</div>
		<?php }

		private function Item($data) { ?>
			<a href = "/stories/show">
				<div></div>
				<div>
					<div><?= $data['header']; ?></div>
					<div><?= $data['text']; ?></div>
					<!--					<div>Читать дальше</div>-->
				</div>
			</a>
		<?php }

	}