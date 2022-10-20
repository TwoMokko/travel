<?php

    require 'templates/top.tpl';
    require 'templates/footer.tpl';
    require 'templates/main.tpl';


    function Title(): string {
        return 'Главная';
    }

    function Head() {
        ?><div class = "block hat">
            <div></div>
            <?php Top(); ?>
            <div>
                <div>Авторские туры</div>
                <div>АйДаПоход</div>
                <div>Организуем путешествия на основе ваших пожеланий,
					<br>а так же по подготовленным нами маршрутам</div>
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
						<select>
							<option>1</option>
							<option>2</option>
							<option>3</option>
							<option>4</option>
							<option>5</option>
							<option>группа</option>
						</select>
					</div>
					<div>
						<input type = "submit" value = "Забронировать">
					</div>
				</form>
			</div>

		</div>
		<div class = "block about_us">
			<div>О НАС</div>
			<div>Наша команда организует путешествия
                <br>по различным маршутам и направлениям</div>
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
                <input type = "button" value = "Выбрать путешествие">
			</div>
			<div>
				<div></div>
				<div>Путешествия</div>
				<div>Краткое описание</div>
                <input type = "button" value = "Выбрать путешествие">
			</div>
			<div>
				<div></div>
				<div>Короткие путешествия</div>
				<div>Краткое описание</div>
                <input type = "button" value = "Выбрать путешествие">
			</div>
		</div>
		<div class = "block adventure">
            <div>
                <div>Наши приключения</div>
                <input type = "button" value = "Читать">
            </div>
        </div>
		<div class = "block photo">
			<div class = "main">
				<div class = "header photo">Фотографии с путешествий</div>
				<div class = "main_photo">
					<div>Ак-туру</div>
					<div></div>
				</div>
			</div>
			<div class = "mini_photo">
				<div></div>
				<div></div>
				<div></div>
				<div></div>
			</div>
		</div><?php
	}


