<?php

    function Top() {
        ?><div class = "block top">
            <div>
                <a href = "/"></a>
            </div>
           <?php Menu(); ?>
        </div><?php
    }

    function Menu() {
        ?><div class = "block menu">
            <div>Главная</div>
            <div>Путешествия</div>
            <div>О нас</div>
            <div>Наши приключения</div>
            <div>Фотографии</div>
        </div><?php
    }