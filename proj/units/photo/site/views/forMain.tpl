<?php

	namespace Proj\Site\Templates\Photo;

	use Base\Templates\Template;
	use Proj\Site\Units\Photo;
	use Proj\Site\Units\Pages;
	use Proj\Units\Consts;

	abstract class ForMain {

		public static function ToVar(array $items): string {
			Template::Start();
			self::Render($items);
			return Template::Read();
		}

		public static function Render($items): void { ?>
			<div class = "tour_photo block p">
				<div class = "header">Фотографии</div>
				<div class = "block photo_carousel">
					<div id = "photo_adapter" class = "carousel">
						<?php foreach ($items as $item) { ?>
							<div data-id = "gallery_1" data-url = "<?= Consts\Photo::PATH_ALL_RELATIVE . $item['image']; ?>" style = "background-image: url('<?= Consts\Photo::PATH_ALL_RELATIVE . $item['image']; ?>');" onclick = "new Gallery(this);"></div>
						<?php } ?>
					</div>
				</div>
				<div>
					<?= Pages::instance()->photos->GetLink('Перейти к альбомам', [], ['class' => 'button']); ?>
				</div>
			</div>
			<script>
				$(() => new Carousel('#photo_adapter'));
			</script>
		<?php }
	}