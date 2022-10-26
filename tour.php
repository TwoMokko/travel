<?php

    require 'templates/top.tpl';
    require 'templates/footer.tpl';
    require 'templates/main.tpl';

    function Title(): string {
        return 'Путешествия';
    }

    function Head() {
        ?><div class = "block hat other">
        <div class = "tour"></div>
        <?php Top(); ?>
        <div>
            <div>Путешествия</div>
            <div>Возможно, текст</div>
        </div>
        </div><?php
    }

    function Main() {
        ?>
        <div class = "block travels">
            <div>Индивидуальное сопровождение</div>
            <div class = "cards_tour">
                <div>
                    <div>Картинка</div>
                    <div>
                        <div>Название</div>
                        <div>Дата</div>
                        <div>Цена</div>
                    </div>
                    <div>Описание</div>
                    <div>
                        <input type = "button" value = "Подробнее">
                        <input type = "button" value = "Оставить заявку">
                    </div>
                </div>
                <div>
                    <div>Картинка</div>
                    <div>
                        <div>Название</div>
                        <div>Дата</div>
                        <div>Цена</div>
                    </div>
                    <div>Описание</div>
                    <div>
                        <input type = "button" value = "Подробнее">
                        <input type = "button" value = "Оставить заявку">
                    </div>
                </div>
            </div>
        </div>
        <div class = "block travels">
            <div>Путешествия</div>
            <div class = "cards_tour">
                <div>
                    <div>Картинка</div>
                    <div>
                        <div>Название</div>
                        <div>Дата</div>
                        <div>Цена</div>
                    </div>
                    <div>Описание</div>
                    <div>
                        <input type = "button" value = "Подробнее">
                        <input type = "button" value = "Оставить заявку">
                    </div>
                </div>
            </div>
        </div>
        <div class = "block travels">
            <div>Короткие путешествия</div>
            <div class = "cards_tour">
                <div>
                    <div>Картинка</div>
                    <div>
                        <div>Название</div>
                        <div>Дата</div>
                        <div>Цена</div>
                    </div>
                    <div>Описание</div>
                    <div>
                        <input type = "button" value = "Подробнее">
                        <input type = "button" value = "Оставить заявку">
                    </div>
                </div>
            </div>
        </div>
        <?php
    }