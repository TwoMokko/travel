<?php

require 'templates/top.tpl';
require 'templates/footer.tpl';
require 'templates/main.tpl';

function Title(): string {
    return 'Фотографии';
}

function Head(): void {
    ?><div class = "block hat other">
    <div class = "photo_hat"></div>
    <?php Top(); ?>
    <div>
        <div>Фотографии</div>
        <div>Возможно, текст</div>
    </div>
    </div><?php
}


function Main(): void {
    ?><div class = "block page_photo p">
        <div></div>
        <div class = "photo_albums">
			<div>
				<div>Ак-туру</div>
			</div>
			<div>
				<div>Байкал</div>
			</div>
			<div>
				<div>Чулышманская долина</div>
			</div>
			<div>
				<div>Дагестан</div>
			</div>
			<div>
				<div>Каракольские озера</div>
			</div>
			<div>
				<div>Каппадокия</div>
			</div>
			<div>
				<div>Карелия</div>
			</div>
			<div>
				<div>Телецкое озеро</div>
			</div>
			<div>
				<div>Походы выходного дня</div>
			</div>
		</div>
    </div><?php
}
