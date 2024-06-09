<?php

	namespace Proj\Site\Templates\Travel;

	use Base\Templates\Buffering;
	use Proj\Units\Consts;
	use Proj\Site\Actions;

	abstract class Carousel {

		public static function ToVar(array $items): string {
			Buffering::Start();
			self::Render($items);
			return Buffering::Read();
		}

		public static function Render($items): void { ?>
			<div class = "other_publication block p">
				<div>
					<span class = "header" onclick = "window.location.href = '<?= Actions\Pages::$tours->GetPath(); ?>';">Другие путешествия</span>
				</div>
				<div id = "other_publication">
					<?php foreach ($items as $item) {
						$url = Consts\Travel::PATH_TOUR_PREVIEW_RELATIVE . $item['image'];
						echo Actions\Pages::$tour->GetLinkHref(self::GetItem($item), ['id' => $item['id']], ['class' => 'other_public other_tour', 'style' => "background-image: url('{$url}');"]);
					} ?>
				</div>
			</div>
			<script>
				$(() => new Carousel('#other_publication'));
			</script>
		<?php }

		private static function GetItem($data): string {
			Buffering::Start();
		?>
			<span><?= $data['name']; ?></span>
			<span>
				<span><?= $data['date']; ?></span>
				<span><?= MoneyFormat($data['price']); ?> </span>
			</span>
		<?php
			return Buffering::Read();
		}
	}