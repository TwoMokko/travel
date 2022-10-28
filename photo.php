<?php

require 'templates/top.tpl';
require 'templates/footer.tpl';
require 'templates/main.tpl';

function Title() {
    return 'Фотографии';
}

function Head() {
    ?><div class = "block hat other">
    <div class = ""></div>
    <?php Top(); ?>
    <div>
        <div>Фотографии</div>
        <div>Возможно, текст</div>
    </div>
    </div><?php
}


function Main() {
    ?><div class = "block page_photo">
        <div></div>
        <div></div>
        <div></div>
    </div><?php
}
