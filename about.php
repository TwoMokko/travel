<?php

	require 'templates/top.tpl';
	require 'templates/footer.tpl';
	require 'templates/main.tpl';

    function Title(): string {
        return 'О нас';
    }

    function Head() {
        ?><div class = "about block hat">
			<?php Top(); ?>
			<div></div>
            <div>
				<div>О нас</div>
			</div>
        </div><?php
    }

    function Main() {
    	?><div>
			<div>Описание</div>
		</div><?php
	}
