<?php

	require 'templates/top.tpl';
	require 'templates/footer.tpl';
	require 'templates/main.tpl';

    function Title() {
        return 'О нас';
    }

    function Head() {
        ?><div class = "block hat other">
			<div class = "about"></div>
			<?php Top(); ?>
            <div>
				<div>О нас</div>
				<div>Возможно, текст</div>
			</div>
        </div><?php
    }


    function Main() {
        ?><div class = "block page_about_us">
            <div>Описание</div>
        </div><?php
    }
