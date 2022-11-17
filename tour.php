<?php

    require 'templates/top.tpl';
    require 'templates/footer.tpl';
    require 'templates/main.tpl';

    function Title(): string {
        return 'Одно путешествие';
    }

    function Head(): void {
        ?><div class = "block hat other">
        <div class = "tour_hat"></div>
        <?php Top(); ?>
        <div>
            <div>Одно путешествие</div>
            <div>30 декабря - 5 января</div>
        </div>
        </div><?php
    }

    function Main(): void {
        ?><div class = "block page_one_tour">
			<div class = "about_tour"></div>
			<div class = "tour_price"></div>
			<div class = "tour_take_things"></div>
			<div class = "tour_program block p">
				<div class = "map"></div>
				<div class = "days">
					<div>
						<div>1</div>
						<div>Встреча группы в Иркутске.
							Приезжаем на остров Ольхон 30 декабря после обеда.
							Заселение и ознакомительная экскурсия.</div>
					</div>
					<div>
						<div>2</div>
						<div>Прогулка по посёлку и к роднику.
							Подготовка к встрече Нового года, баня.</div>
					</div>
					<div>
						<div>3</div>
						<div>Пешая прогулка на смотровую площадку.</div>
					</div>
					<div>
						<div>4</div>
						<div>Поездка на мыс Хобой,
							экскурсия по северу острова.</div>
					</div>
					<div>
						<div>5</div>
						<div>Трекинг на мыс Хатха (поперёк острова),
							альтернатива пешая прогулка по льду озера,
							катание на коньках.</div>
					</div>
					<div>
						<div>6</div>
						<div>Свободное время, катание на коньках,
							прогулки по острову.</div>
					</div>
					<div>
						<div>7</div>
						<div>Выезд с острова в Иркутск.</div>
					</div>
				</div>
			</div>
			<div class = "tour_video"></div>
			<div class = "tour_dates"></div>
			<div class = "tour_photo"></div>
			<div class = "tour_form"></div>
        </div><?php
    }
