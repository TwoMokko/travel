<?php

    namespace Proj\Site\Templates\General;

    use Base\Templates\View;

    class HeaderForMain extends View {

        public function ToVar(): string {
            $this->Start();
            $this->Render();
            return $this->Read();
        }

        public function Render() { ?>
            <div class = "block hat main">
                <div></div>
                <?php Header::object()->Render(); ?>
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