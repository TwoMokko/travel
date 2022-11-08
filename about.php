<?php

	require 'templates/top.tpl';
	require 'templates/footer.tpl';
	require 'templates/main.tpl';

    function Title(): string {
        return 'О нас';
    }

    function Head(): void {
        ?><div class = "block hat other">
			<div class = "about_hat"></div>
			<?php Top(); ?>
            <div>
				<div>О нас</div>
				<div>Возможно, текст</div>
			</div>
        </div><?php
    }


    function Main(): void {
        ?><div class = "block page_about_us">
            <div class = "about_header block p">
                <div>
                    <div>что-то</div>
                    <div>Мы такие-то такие <br>вот текст такой</div>
                    <div>Еще какой-то текст подлиннее, например, что-то немного о создании или о миссии или о ценностях</div>
                </div>
                <div>picture</div>
            </div>
            <div></div>
            <div class = "block p">
                <div>
                    <div>что-то</div>
                    <div>Мы такие-то такие <br>вот текст такой</div>
                    <div>Еще какой-то текст подлиннее, например, что-то немного о создании или о миссии или о ценностях</div>
                </div>
                <div>picture</div>
            </div>
            <div class = "block p">
                <div>picture</div>
                <div>
                    <div></div>
                    <div></div>
                    <div></div>
                </div>
            </div>
        </div><?php
    }
