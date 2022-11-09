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
                <div class = "about_text">
                    <div>что-то</div>
                    <div>Организуем путешествия на основе ваших пожеланий,
						<br>а так же по подготовленным нами маршрутам
						<br>Организуем путешествия на основе ваших пожеланий,
						<br>а так же по подготовленным нами маршрутам</div>
                    <div class = "right_text">Еще какой-то текст подлиннее, например, что-то немного о создании или о миссии или о ценностях</div>
                </div>
                <div class = "about_pic"></div>
            </div>
            <div>
				<div></div>
			</div>
            <div class = "block p">
                <div class = "about_text">
                    <div>Организатор</div>
                    <div>Ишмурзина Нина</div>
                    <div>Еще какой-то текст подлиннее, например, что-то немного о создании или о миссии или о ценностях</div>
                </div>
                <div class = "about_pic"></div>
            </div>
            <div class = "block p">
                <div class = "about_pic"></div>
                <div class = "about_text">
                    <div>Водитель</div>
                    <div>Меховников Сергей</div>
                    <div>Супер крутое описание человека которыей чем-то занимается в этой компании</div>
                </div>
            </div>
        </div><?php
    }
