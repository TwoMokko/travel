<?php

    namespace Proj\Site\Templates\General;

    use Base\Templates\Template;

    abstract class HeaderForMain {

        public static function ToVar(string $main_header1, string $main_header2, string $main_header3): string {
            Template::Start();
            self::Render($main_header1, $main_header2, $main_header3);
            return Template::Read();
        }

        public static function Render(string $main_header1, string $main_header2, string $main_header3): void { ?>
            <div class = "block hat main">
                <div></div>
                <?php Header::Render(); ?>
                <div>
                    <div><?= nl2br($main_header1); ?></div>
                    <div><?= nl2br($main_header2); ?></div>
                    <div>
                        <?= nl2br($main_header3); ?>
<!--                        Организуем путешествия-->
<!--                        <br>на основе ваших пожеланий,-->
<!--                        <br>а так же по подготовленным-->
<!--                        <br>нами маршрутам-->
                    </div>
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