<?php

    function Title(): string {
        return 'Главная';
    }

    function Head() {
        ?><div>
            <div>Авторские туры</div>
            <div>АйДаПоход</div>
            <div>Организуем путешествия на основе ваших пожеланий, а так же по подготовленным нами маршрутам</div>
            <div>Смотреть видео</div>
        </div>
        <div>
            <div>О нас</div>
        </div>
        <div>
            <div>Туры</div>
        </div>
        <div></div><?php
    }

    require 'templates/footer.tpl';
    require 'templates/main.tpl';
