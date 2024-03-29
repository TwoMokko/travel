<?php

	namespace Proj\Site\Templates\Tour;

	use Base\Templates\Template;
	use Proj\Site\Units\Pages;
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
					<span class = "header" onclick = "window.location.href = '<?= Pages::instance()->tours->GetPath(); ?>';">Другие путешествия</span>
				</div>
				<div id = "other_publication">
					<?php foreach ($items as $item) {
						$url = Consts\Tour::PATH_TOUR_PREVIEW_RELATIVE . $item['image'];
						echo Pages::instance()->tour->GetLink(self::Item($item), ['id' => $item['id']], ['class' => 'other_public other_tour', 'style' => "background-image: url('{$url}');"]);
					} ?>
				</div>
			</div>
			<script>
				$(() => new Carousel('#other_publication'));
			</script>
		<?php }

		private static function Item($data): string {
			Template::Start();
		?>
			<span><?= $data['name']; ?></span>
			<span>
				<span><?= $data['date']; ?></span>
				<span><?= MoneyFormat($data['price']); ?> </span>
			</span>
		<?php
			return Template::Read();
		}
	}