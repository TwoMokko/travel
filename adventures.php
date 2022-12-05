<?php

require 'templates/top.tpl';
require 'templates/footer.tpl';
require 'templates/main.tpl';

function Title(): string {
    return 'Наши приключения';
}

function Head(): void {
    ?><div class = "block hat other">
    <div class = "adventure_hat"></div>
    <?php Top(); ?>
    <div>
        <div>Наши приключения</div>
        <div>Возможно, текст</div>
    </div>
    </div><?php
}


function Main(): void {
    ?><div class = "block page_adventure p">
        <div class = "cards_adventure">
            <div>
				<div></div>
				<div>
					<div>Происшествие на грибах</div>
					<div>Спускались мы с Каменных грибов и натолкнулись на одну девушку, которая "застряла" на полпути.</div>
					<div>
                        <a href = "/adventure">Читать дальше</a>
                    </div>
				</div>
            </div>
            <div>
				<div></div>
				<div>
					<div>Байкальские байки</div>
					<div>Однажды во время поездки на Байкал произошла такая вот история. Пошли прогуляться мы до такого-то места, а по пути нам встретилась необычная компания. Мы разговорились.</div>
                    <div>
						<a href = "/adventure">Читать дальше</a>
                    </div>
				</div>
            </div>
            <div>
				<div></div>
				<div>
					<div>Зеленые тапочки</div>
					<div>Из путешествий часто привозят различные сувениры. Обычно их покупают в лавках. Этот сувенир необычным образом оказался у нас.</div>
                    <div>
						<a href = "/adventure">Читать дальше</a>
                    </div>
				</div>
            </div>
            <div>
				<div></div>
				<div>
					<div>Чую на чуе ночую</div>
					<div>В пути случаеются разные ситуации, которые немного сдвигают планы. Так произошло и в той-то поездке. Нам пришлось искать ночлег, не доехав до забронированных домиков на базе.</div>
                    <div>
						<a href = "/adventure">Читать дальше</a>
                    </div>
				</div>
            </div>
            <div>
				<div></div>
				<div>
					<div>Рыбья удача</div>
					<div>Описание</div>
                    <div>
						<a href = "/adventure">Читать дальше</a>
                    </div>
				</div>
            </div>
        </div>
    </div>
    <script>
        $(() => ScrollTop('main'));
    </script>
    <?php
}
