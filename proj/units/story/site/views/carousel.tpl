<?php

	namespace Proj\Site\Templates\Story;

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
					<span class = "header" onclick = " window.location.href = '<?= Actions\Pages::$stories->GetHref(); ?>';">Другие приключения</span>
				</div>
				<div id = "story" class = "carousel">
					<?php foreach ($items as $item) {
						$url = Consts\Story::PATH_COVER_PREVIEW_RELATIVE . $item['image'];
						echo Actions\Pages::$story->GetLinkHref("<span>{$item['header']}</span>", ['id' => $item['id']], ['class' => 'other_public other_story', 'style' => "background-image: url('{$url}');"]);
					} ?>
				</div>
			</div>
			<script>
                $(() => new Carousel('#story'));
			</script>
		<?php }

	}