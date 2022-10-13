<?php

    function Title(): string {
        return 'Главная';
    }

    function Head() {
        ?><div class = "block hat">
            <div></div>
            <div>
                <div>Авторские туры</div>
                <div>АйДаПоход</div>
                <div>Организуем путешествия на основе ваших пожеланий, а так же по подготовленным нами маршрутам</div>
                <div>Смотреть видео</div>
            </div>
        </div><?php
    }

    require 'templates/footer.tpl';
    require 'templates/main.tpl';
