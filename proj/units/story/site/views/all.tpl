<?php

	namespace Proj\Site\Templates\Story;

	use Base\Templates\Template;
	use Proj\Site\Units\Pages;
	use Proj\Site\Units\Story;
	use Proj\Units\Consts;

    abstract class All {

		public static function ToVar(array $items): string {
			Template::Start();
			self::Render($items);
			return Template::Read();
		}

		public static function Render($items): void { ?>
			<div class = "block page_adventure p">
				<div class = "cards_adventure">
					<?php foreach ($items as $item) echo Pages::instance()->story->GetLink(self::ItemToVar($item), ['id' => $item['id']]);
					/* Story::instance()->show->GetLink(self::ItemToVar($item), ['id' => $item['id']]);*/ ?>
				</div>
			</div>
		<?php }

		private static function Item($data): void { ?>
            <div style = "background-image: url(<?= Consts\Story::PATH_COVER_PREVIEW_RELATIVE, $data['image']; ?>);"></div>
            <div>
                <div><?= $data['header']; ?></div>
                <div><?= $data['text']; ?></div>
                <!--					<div>Читать дальше</div>-->
            </div>
		<?php }

        public static function ItemToVar(array $item): string {
			Template::Start();
            self::Item($item);
            return Template::Read();
        }

	}