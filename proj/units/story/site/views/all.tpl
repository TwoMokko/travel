<?php

	namespace Proj\Site\Templates\Story;

	use Base\Templates\Buffering;
	use Proj\Units\Consts;
	use Proj\Site\Actions;

    abstract class All {

		public static function ToVar(array $items): string {
			Buffering::Start();
			self::Render($items);
			return Buffering::Read();
		}

		public static function Render($items): void { ?>
			<div class = "block page_adventure p">
				<div class = "cards_adventure">
					<?php foreach ($items as $item) echo Actions\Pages::$story->GetLinkHref(self::ItemToVar($item), ['id' => $item['id']]); ?>
				</div>
			</div>
		<?php }

		private static function Item($data): void { ?>
            <div style = "background-image: url(<?= Consts\Story::PATH_COVER_PREVIEW_RELATIVE, $data['image']; ?>);"></div>
            <div>
                <div><?= $data['header']; ?></div>
                <div><?= $data['text']; ?></div>
            </div>
		<?php }

        public static function ItemToVar(array $item): string {
			Buffering::Start();
            self::Item($item);
            return Buffering::Read();
        }

	}