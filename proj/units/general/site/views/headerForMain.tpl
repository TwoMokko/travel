<?php

    namespace Proj\Site\Templates\General;

    use Base\Templates\Template;

    abstract class HeaderForMain {

        public static function ToVar(): string {
            Template::Start();
            self::Render();
            return Template::Read();
        }

        public static function Render(): void { ?>
            <div class = "block hat main">
                <div></div>
                <?php Header::Render(); ?>
                <div>
                    <div>Авторские туры</div>
                    <div>i Da Travel</div>
                    <div>
                        <div>Организуем путешествия</div>
                        <div>на основе ваших пожеланий,</div>
                        <div>а так же по подготовленным</div>
                        <div>нами маршрутам</div>
                    </div>
                    <div>
                    <span>
                       <span></span>
                    <span>Смотреть видео</span>
                    </span>
                    </div>
                </div>
            </div>
        <?php }

    }