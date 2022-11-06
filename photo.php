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
        <div></div>
        <div></div>
    </div><?php
}
