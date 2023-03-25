<?php

	namespace Proj\Site\Templates\Photo;

	use Base\Templates\Template;
	use Proj\Site\Units\Photo;
	use Proj\Units\Consts;

	abstract class ForTour {

		public static function ToVar(array $items, $photo_id): string {
			Template::Start();
			self::Render($items, $photo_id);
			return Template::Read();
		}

		public static function Render($items, $photo_id): void { ?>
			<div class = "tour_photo block p">
				<div class = "header">Фотографии</div>
				<div class = "block tour_mini_photo">
					<?php foreach ($items as $item) { ?>
						<div data-id = "gallery_1" data-url = "<?= Consts\Photo::PATH_SHOW_RELATIVE . $item['image']; ?>" style = "background-image: url('<?= Consts\Photo::PATH_SHOW_RELATIVE . $item['image']; ?>');" onclick = "new Gallery(this);"></div>
					<?php } ?>
				</div>
				<div class = "block tour_mini_photo_carousel">
					<div id = "photo_adapter" class = "carousel">
						<?php foreach ($items as $item) { ?>
							<div data-id = "gallery_2" data-url = "<?= Consts\Photo::PATH_SHOW_RELATIVE . $item['image']; ?>" style = "background-image: url('<?= Consts\Photo::PATH_SHOW_RELATIVE . $item['image']; ?>');" onclick = "new Gallery(this);"></div>
						<?php } ?>
					</div>
				</div>
				<div>
					<?= Photo::instance()->show->GetLink('Смотреть альбом', ['id' => $photo_id], ['class' => 'button']); ?>
				</div>
			</div>
			<script>
				$(() => new Carousel('#photo_adapter', 2));
			</script>
		<?php }
	}