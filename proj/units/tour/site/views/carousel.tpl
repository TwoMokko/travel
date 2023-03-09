<?php

	namespace Proj\Site\Templates\Tour;

	use Base\Templates\View;
	use Proj\Site\Units\Tour;

	class Carousel extends View {

		public function ToVarCarousel(array $items): string {
			$this->Start();
			$this->Carousel($items);
			return $this->Read();
		}

		public function Carousel($items) { ?>
			<div class = "other_publication block p">
				<div>
					<span class = "header" onclick = " window.location.href = '/tours';">Другие путешествия</span>
				</div>
				<div id = "other_publication" class = "carousel">
					<?php foreach ($items as $item) echo Tour::instance()->item->GetLink($this->Item($item), ['id' => $item['id']], ['class' => 'other_public other_tour']); ?>
				</div>
			</div>
			<script>
				$(() => new Carousel('#other_publication', 4));
			</script>
		<?php }

		private function Item($data): string {
			$this->Start();
		?>
			<span><?= $data['name']; ?></span>
			<span>
				<span><?= $data['date']; ?></span>
				<span><?= $data['price']; ?> </span>
			</span>
		<?php
			return $this->Read();
		}
	}