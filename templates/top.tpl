<?php

    function Top(): void {
        ?><div class = "block top">
            <div>
                <a href = "/"></a>
            </div>
           <?php Menu(); ?>
        </div><?php
    }

    function Menu(): void {
        ?><div class = "block menu">
            <a href = "/">Главная</a>
            <a href = "/tours.php">Путешествия</a>
            <a href = "/about">О нас</a>
            <a href = "/adventures.php">Наши приключения</a>
            <a href = "/photo">Фотографии</a>
        </div><?php
    }