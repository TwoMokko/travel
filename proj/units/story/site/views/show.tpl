<?php

	namespace Proj\Site\Templates\Story;

	use Base\Templates\Buffering;
	use Proj\Units\Consts;

	abstract class Show {

		public static function ToVar(array $data): string {
			Buffering::Start();
			self::Render($data);
			return Buffering::Read();
		}

		public static function Render($data): void { ?>
            <div class = "block p page_one_adventure">
                <div class = "adventure_text">
                    <div><?= nl2br($data['text']); ?></div>
                    <div>
                        <div data-id = "1" data-url = "<?= Consts\Story::PATH_COVER_ORIGINAL_RELATIVE . $data['image']; ?>" style = "background-image: url(<?= Consts\Story::PATH_COVER_PREVIEW_RELATIVE . $data['image']; ?>););" onclick = "new Gallery(this);"></div>
                    </div>
                </div>
            </div>
		<?php }

	}