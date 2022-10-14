<?php

    function Title(): string {
        return 'Главная';
    }

    function Head() {
        ?><div class = "block hat">
            <div></div>
            <div>
                <div>Авторские туры</div>
                <div>АйДаПоход</div>
                <div>Организуем путешествия на основе ваших пожеланий,
					а так же по подготовленным нами маршрутам</div>
                <div>Смотреть видео</div>
            </div>
        </div><?php
    }

    function Main() {
    	?><div class = "block check_tour">
			<div>
				<form>
					<div>
						<div>Выберите категорию</div>
						<select>
							<option>Индивидуальное сопровождение</option>
							<option>Путешествия</option>
							<option>Короткие путешествия</option>
						</select>
					</div>
					<div>
						<div>Выберите путешествие и дату</div>
						<select>
							<option>Байкал, остров Ольхон. 28 декабря - 6 января</option>
							<option>Чулышманская долина. 1-8 мая</option>
							<option>Ак-туру. 24-30 июня</option>
							<option>Чулышманская долина. 20-29 июля</option>
							<option>Каракольские озера. 2-10 августа</option>
							<option>Ак-туру. 27 августа - 3 сентября</option>
						</select>
					</div>
					<div>
						<div>Количество человек</div>
						<input type = "text">
					</div>
					<div>
						<input type = "submit" value = "Забронировать">
					</div>
				</form>
			</div>

		</div>
		<div class = "block about_us">
			<div>О нас</div>
			<div>Наша команда организует путешествия по различным маршутам и направлениям</div>
			<div>
				Для нас важно показать уникальность посещаемых мест и зарядить положительными эмоциями и впечатлениями
				В наших приключениях мы стараемся отключиться от влияния внешнего мира, чтобы ничего не мешало нам получать удовольствие и умиротворение от происходящего
				Мы сторонники свободного распорядка дня. В путешествиях у нас нет временных рамок, но мы везде успеваем
				Мы считаем, что в путешествиях человек познает себя и заряжается для свершений в жизни
			</div>
		</div>
		<div class = "block tour">
			<div>
				<div></div>
				<div>Индивидуальное сопровождение</div>
				<div>Краткое описание</div>
			</div>
			<div>
				<div></div>
				<div>Путешествия</div>
				<div>Краткое описание</div>
			</div>
			<div>
				<div></div>
				<div>Короткие путешествия</div>
				<div>Краткое описание</div>
			</div>
		</div>
		<div class = "block adventure"></div>
		<div class = "block photo"><?php
	}

    require 'templates/footer.tpl';
    require 'templates/main.tpl';
