<?php

require 'templates/top.tpl';
require 'templates/footer.tpl';
require 'templates/main.tpl';

function Title() {
    return 'Наши приключения';
}

function Head() {
    ?><div class = "block hat other">
    <div class = ""></div>
    <?php Top(); ?>
    <div>
        <div>Наши приключения</div>
        <div>Возможно, текст</div>
    </div>
    </div><?php
}


function Main() {
    ?><div class = "block page_adventure">
        <div class = "cards_adventure">
            <div>
                <div>Картинка</div>
                <div>Название тура</div>
                <div>Описание</div>
                <div>
                    <input type = "button" value = "Подробнее">
                </div>
            </div>
            <div>
                <div>Картинка</div>
                <div>Название тура</div>
                <div>Описание</div>
                <div>
                    <input type = "button" value = "Подробнее">
                </div>
            </div>
            <div>
                <div>Картинка</div>
                <div>Название тура</div>
                <div>Описание</div>
                <div>
                    <input type = "button" value = "Подробнее">
                </div>
            </div>
            <div>
                <div>Картинка</div>
                <div>Название тура</div>
                <div>Описание</div>
                <div>
                    <input type = "button" value = "Подробнее">
                </div>
            </div>
            <div>
                <div>Картинка</div>
                <div>Название тура</div>
                <div>Описание</div>
                <div>
                    <input type = "button" value = "Подробнее">
                </div>
            </div>
        </div>
    </div><?php
}
