<?php

	namespace Proj\Site\Templates\Tour;

	use Base\Templates\Template;
	use Proj\Site\Units\Tour;
	use Proj\Units\Consts;

	abstract class Carousel {

		public static function ToVarCarousel(array $items): string {
			Template::Start();
			self::Carousel($items);
			return Template::Read();
		}

		public static function Carousel($items): void { ?>
			<div class = "other_publication block p">
				<div>
					<span class = "header" onclick = " window.location.href = '/tours';">Другие путешествия</span>
				</div>
				<div id = "other_publication">
					<?php foreach ($items as $item) {
						$url = Consts\Tour::PATH_TOUR_RELATIVE . $item['image'];
						echo Tour::instance()->item->GetLink(self::Item($item), ['id' => $item['id']], ['class' => 'other_public other_tour', 'style' => "background-image: url('{$url}');"]);
					} ?>
				</div>
			</div>
			<script>
				$(() => new Carousel('#other_publication', 4));
			</script>
		<?php }

		private static function Item($data): string {
			Template::Start();
		?>
			<span><?= $data['name']; ?></span>
			<span>
				<span><?= $data['date']; ?></span>
				<span><?= $data['price']; ?> </span>
			</span>
		<?php
			return Template::Read();
		}
	}