<?php

    function Top(): void {
        ?><div class = "block top">
            <div>
                <a href = "/"></a>
            </div>
           <?php Menu(); ?>
			<div class = "open_menu" onclick = "new Menu();"></div>

        </div><?php
    }

    function Menu(): void {
        ?><div class = "block menu">
			<div>
				<a href = "/">Главная</a>
			</div>
			<div>
				<a href = "../../site.php">Путешествия</a>
			</div>
			<div>
				<a href = "../../site.php">О нас</a>
			</div>
			<div>
				<a href = "../../site.php">Дневник Путешествий</a>
			</div>
			<div>
				<a href = "../../site.php">Фотоальбомы</a>
			</div>
        </div>
		<?php
    }