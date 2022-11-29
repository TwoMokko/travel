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
			<div onclick = " window.location.href = '/photoalbum';">
				<div>Ак-туру</div>
			</div>
			<div onclick = " window.location.href = '/photoalbum';">
				<div>Байкал</div>
			</div>
			<div onclick = " window.location.href = '/photoalbum';">
				<div>Чулышманская долина</div>
			</div>
			<div onclick = " window.location.href = '/photoalbum';">
				<div>Дагестан</div>
			</div>
			<div onclick = " window.location.href = '/photoalbum';">
				<div>Каракольские озера</div>
			</div>
			<div onclick = " window.location.href = '/photoalbum';">
				<div>Каппадокия</div>
			</div>
			<div onclick = " window.location.href = '/photoalbum';">
				<div>Карелия</div>
			</div>
			<div onclick = " window.location.href = '/photoalbum';">
				<div>Телецкое озеро</div>
			</div>
			<div onclick = " window.location.href = '/photoalbum';">
				<div>Походы выходного дня</div>
			</div>
		</div>
    </div><?php
}
