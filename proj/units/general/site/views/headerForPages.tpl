<?php

    namespace Proj\Site\Templates\General;

    use Base\Templates\Template;

    abstract class HeaderForPages {

        public static function ToVar(string $image, string $title, string $text = ''): string {
			Template::Start();
            self::Render($image, $title, $text);
            return Template::Read();
        }

        public static function Render(string $image, string $title, string $text = ''): void { ?>
            <div class = "block hat other">
                <div style = "background-image: url('<?= $image; ?>');"></div>
                <?php Header::Render(); ?>
                <div>
                    <div><?= $title; ?></div>
                    <div><?= $text; ?></div>
                </div>
            </div>
        <?php }

    }