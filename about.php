<?php

	require 'templates/top.tpl';
	require 'templates/footer.tpl';
	require 'templates/main.tpl';

    function Title(): string {
        return 'О нас';
    }

    function Head(): void {
        ?><div class = "block hat other">
			<div class = "about"></div>
			<?php Top(); ?>
            <div>
				<div>О нас</div>
				<div>Возможно, текст</div>
			</div>
        </div><?php
    }


    function Main(): void {
        ?><div class = "block page_about_us p">
            <div>Описание</div>
        </div><?php
    }
