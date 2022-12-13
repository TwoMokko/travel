<?php

    require 'templates/top.tpl';
    require 'templates/footer.tpl';
	require 'templates/main.tpl';



    function Title(): string {
        return 'Главная';
    }

    function Head() {
        ?><div class = "block hat main">
            <div></div>
            <?php Top(); ?>
            <div>
                <div>Авторские туры</div>
                <div>i Da Travel</div>
                <div>Организуем путешествия
                    <br>на основе ваших пожеланий,
					<br>а так же по подготовленным
                    <br>нами маршрутам</div>
                <div>
                    <span>
                       <span></span>
                    <span>Смотреть видео</span>
                    </span>
                </div>
            </div>
        </div><?php
    }

    function Main(): void {
    	?><div class = "block check_tour">
			<div>
				<form>
					<div>
						<div>Выберите категорию</div>
						<select>
							<option>Основные путешествия</option>
							<option>Индивидуальное сопровождение</option>
							<option>ВИП</option>
							<option>Выходного дня</option>
						</select>
					</div>
					<div>
						<div>Выберите путешествие</div>
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
						<input type = "submit" value = "Оставить заявку">
					</div>
				</form>
			</div>

		</div>
		<div class = "block about_us p">
			<div></div>
			<div>Наша команда организует путешествия
                <br>по различным маршутам и направлениям</div>
			<div>
				Для нас важно показать уникальность посещаемых мест и зарядить положительными эмоциями и впечатлениями
				В наших приключениях мы стараемся отключиться от влияния внешнего мира, чтобы ничего не мешало нам получать удовольствие и умиротворение от происходящего
				Мы сторонники свободного распорядка дня. В путешествиях у нас нет временных рамок, но мы везде успеваем
				Мы считаем, что в путешествиях человек познает себя и заряжается для свершений в жизни
			</div>
		</div>
		<div class = "block tours p">
			<div>
				<div>Типы путешествий</div>
				<div>
					<div>Основные путешествия</div>
					<div>Индивидуальное сопровождение</div>
					<div>ВИП</div>
					<div>Выходного дня</div>
				</div>
				<div>
					<div></div>
					<div>
						<div>Индивидуальное сопровождение</div>
						<div>Небольшое количество человек. Можем организовать путешествие на основе ваших пожеланий. Едем на хорошей машине.</div>
						<div>
							<a class = "button" href = "/tours">Выбрать путешествие</a>
<!--							<input type = "button" value = "Выбрать путешествие" onclick = " window.location.href = '/tours';">-->
						</div>
					</div>
				</div>
			</div>
		</div>
		<div class = "block adventure">
            <div>
                <div>Наши приключения</div>
                <div>Истории из наших путешествий,
                    <br>рассказанные участниками</div>
				<a class = "button semi_white" href = "/adventures">Читать</a>
            </div>
        </div>
		<div class = "block photo p">
			<div class = "head_photo">
				<div>Фотографии с наших путешествий</div>
				<div>
					<div></div>
					<div></div>
				</div>
			</div>

			<div class = "mini_photo">
				<div>
					<div>Ак-туру</div>
				</div>
				<div>
					<div>Байкал</div>
				</div>
				<div>
					<div>Каппадокия</div>
				</div>
			</div>
			<div>
				<a class = "button" href = "/photo">Перейти к альбомам</a>
			</div>
		</div>
<!--		<div class = "block form p">-->
<!--			<div class = "form_input">-->
<!--				<div>Связаться с нами</div>-->
<!--				<div>-->
<!--					<input type = "text" placeholder = "Имя*">-->
<!--				</div>-->
<!--				<div>-->
<!--					<input type = "text" placeholder = "Телефон*">-->
<!--				</div>-->
<!--				<div>-->
<!--					<input type = "text" placeholder = "E-mail">-->
<!--				</div>-->
<!--				<div>-->
<!--					<input type = "button" value = "Оставить заявку">-->
<!--				</div>-->
<!--			</div>-->
<!--			<div class = "form_contact">-->
<!--				<div>-->
<!--					<div class = "form_text">-->
<!--						<div>Ишмурзина Нина</div>-->
<!--						<div>Организатор</div>-->
<!--						<div class = "contact_person">-->
<!--							<div>-->
<!--								<div>Тел:</div>-->
<!--								<div>+7-909-545-11-29</div>-->
<!--							</div>-->
<!--							<div>-->
<!--								<div></div>-->
<!--								<div></div>-->
<!--							</div>-->
<!--						</div>-->
<!--					</div>-->
<!--					<div class = "form_photo"></div>-->
<!--				</div>-->
<!--				<div>-->
<!--					<div class = "form_text">-->
<!--						<div>Меховникова Сергей</div>-->
<!--						<div>Должность</div>-->
<!--						<div class = "contact_person">-->
<!--							<div>-->
<!--								<div>Тел:</div>-->
<!--								<div>+7-924-424-25-55</div>-->
<!--							</div>-->
<!--							<div>-->
<!--								<div></div>-->
<!--								<div></div>-->
<!--							</div>-->
<!--						</div>-->
<!--					</div>-->
<!--					<div class = "form_photo"></div>-->
<!--				</div>-->
<!--			</div>-->
<!--		</div>-->
        <script>
            $(() => ScrollTop('main'));
        </script>
        <?php
	}


