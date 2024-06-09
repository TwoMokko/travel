<?php

	namespace Proj\Site\Templates\Photo;

	use Base\Templates\Buffering;
	use Proj\Units\Consts;
	use Proj\Site\Actions;

	abstract class ForTour {

		public static function ToVar(array $items, $albumId): string {
			Buffering::Start();
			self::Render($items, $albumId);
			return Buffering::Read();
		}

		public static function Render($items, $albumId): void { ?>
			<div class = "tour_photo block p">
				<div class = "header">Фотографии</div>
				<div class = "block tour_mini_photo">
					<?php foreach ($items as $item) { ?>
						<div data-id = "gallery_1" data-url = "<?= Consts\Photo::PATH_SHOW_RELATIVE_ORIGINAL . $item['image']; ?>" style = "background-image: url('<?= Consts\Photo::PATH_SHOW_RELATIVE_PREVIEW . $item['image']; ?>');" onclick = "new Gallery(this);"></div>
					<?php } ?>
				</div>
				<div class = "block tour_mini_photo_carousel">
					<div id = "photo_adapter" class = "carousel">
						<?php foreach ($items as $item) { ?>
							<div data-id = "gallery_2" data-url = "<?= Consts\Photo::PATH_SHOW_RELATIVE_ORIGINAL . $item['image']; ?>" style = "background-image: url('<?= Consts\Photo::PATH_SHOW_RELATIVE_PREVIEW . $item['image']; ?>');" onclick = "new Gallery(this);"></div>
						<?php } ?>
					</div>
				</div>
				<div>
					<?= Actions\Pages::$album->GetLinkHref('Смотреть альбом', ['id' => $albumId], ['class' => 'button']); ?>
				</div>
			</div>
			<script>
				$(() => new Carousel('#photo_adapter'));
			</script>
		<?php }
	}