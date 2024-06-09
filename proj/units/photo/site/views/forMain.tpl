<?php

	namespace Proj\Site\Templates\Photo;

	use Base\Templates\Buffering;
	use Proj\Site\Actions\Pages;
	use Proj\Units\Consts;

	abstract class ForMain {

		public static function ToVar(array $items): string {
			Buffering::Start();
			self::Render($items);
			return Buffering::Read();
		}

		public static function Render($items): void { ?>
			<div class = "tour_photo block p">
				<div class = "header">Фотографии</div>
				<div class = "block photo_carousel">
					<div id = "photo_adapter" class = "carousel">
						<?php foreach ($items as $item) { ?>
							<div data-id = "gallery_1" data-url = "<?= Consts\Photo::PATH_ALL_ORIGINAL_RELATIVE . $item['image']; ?>" style = "background-image: url('<?= Consts\Photo::PATH_ALL_PREVIEW_RELATIVE . $item['image']; ?>');" onclick = "new Gallery(this);"></div>
						<?php } ?>
					</div>
				</div>
				<div>
					<?= Pages::$albums->GetLinkHref('Перейти к альбомам', [], ['class' => 'button']); ?>
				</div>
			</div>
			<script>
				$(() => new Carousel('#photo_adapter'));
			</script>
		<?php }
	}