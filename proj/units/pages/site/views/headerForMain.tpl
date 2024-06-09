<?php

    namespace Proj\Site\Templates\Pages;

    use Base\Templates\Buffering;

    abstract class HeaderForMain {

        public static function ToVar(string $main_header1, string $main_header2, string $main_header3): string {
			Buffering::Start();
            self::Render($main_header1, $main_header2, $main_header3);
            return Buffering::Read();
        }

        public static function Render(string $main_header1, string $main_header2, string $main_header3): void { ?>
            <div class = "block hat main">
                <div></div>
                <?php Header::Render(); ?>
                <div>
                    <div><?= nl2br($main_header1); ?></div>
                    <div><?= nl2br($main_header2); ?></div>
                    <div><?= nl2br($main_header3); ?></div>
                    <div>
                    <span onclick = "ShowVideo();">
                       <span></span>
                    <span>Смотреть видео</span>
                    </span>
                    </div>
                </div>
            </div>
        <?php }

    }