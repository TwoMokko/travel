<?php

    function Top(): void {
        ?><div class = "block top">
            <div>
                <a href = "/"></a>
            </div>
           <?php Menu(); ?>
			<div class = "open_menu"></div>
        </div><?php
    }

    function Menu(): void {
        ?><div class = "block menu">
			<div>
				<a href = "/">Главная</a>
			</div>
			<div>
				<a href = "/tours">Путешествия</a>
			</div>
			<div>
				<a href = "/about">О нас</a>
			</div>
			<div>
				<a href = "/adventures">Наши приключения</a>
			</div>
			<div>
				<a href = "/photo">Фотографии</a>
			</div>
        </div><?php
    }