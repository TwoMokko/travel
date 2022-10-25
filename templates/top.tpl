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
            <a href = "/">Главная</a>
            <a>Путешествия</a>
            <a href = "/about">О нас</a>
            <a>Наши приключения</a>
            <a>Фотографии</a>
        </div><?php
    }