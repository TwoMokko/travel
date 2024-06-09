<?php

    namespace Proj\Site\Templates\General;

    use Base\Templates\Buffering;
	use Proj\Site\Templates as TPLs;

	abstract class HeaderForPages {

        public static function ToVar(string $image, string $title, string $text = ''): string {
			Buffering::Start();
            self::Render($image, $title, $text);
            return Buffering::Read();
        }

        public static function Render(string $image, string $title, string $text = ''): void { ?>
            <div class = "block hat other">
                <div style = "background-image: url('<?= $image; ?>');"></div>
                <?php TPLs\Pages\Header::Render(); ?>
                <div>
                    <div><?= $title; ?></div>
                    <div><?= $text; ?></div>
                </div>
            </div>
        <?php }

    }