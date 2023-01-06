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
                <div>
					<div>Организуем путешествия</div>
                    <div>на основе ваших пожеланий,</div>
					<div>а так же по подготовленным</div>
					<div>нами маршрутам</div>
				</div>
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
						<div>
							<div>Выберите категорию</div>
							<select id = "categories"></select>
						</div>
						<div>
							<div>Выберите путешествие</div>
							<select id = "tours"></select>
						</div>
					</div>
					<div>
                        <a id = "see_tour" class = "button" href = "/tour">Подробнее о путешествии</a>
<!--						<input type = "submit" value = "Подробнее о путешествии">-->
					</div>
<!--					<div>-->
<!--						<div>Количество человек</div>-->
<!--						<select>-->
<!--							<option>1</option>-->
<!--							<option>2</option>-->
<!--							<option>3</option>-->
<!--							<option>4</option>-->
<!--							<option>5</option>-->
<!--							<option>группа</option>-->
<!--						</select>-->
<!--					</div>-->

				</form>
			</div>

		</div>
		<div class = "block about_us p">
			<div></div>
			<div class = "header">Наша команда организует путешествия
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
				<div class = "header">Типы путешествий</div>
				<div class = "switch_menu">
					<div>Основные путешествия</div>
					<div>Индивидуальное сопровождение</div>
					<div>ВИП</div>
					<div>Выходного дня</div>
				</div>
                <div class = "switch_list">
                    <div>
                        <div></div>
                        <div>
                            <div>Основные путешествия</div>
                            <div>Небольшое количество человек. Можем организовать путешествие на основе ваших пожеланий. Едем на хорошей машине.</div>
                            <div>
                                <a class = "button" href = "/tours#major_travel">Выбрать путешествие</a>
                                <!--							<input type = "button" value = "Выбрать путешествие" onclick = " window.location.href = '/tours';">-->
                            </div>
                        </div>
                    </div>
                    <div>
                        <div></div>
                        <div>
                            <div>Индивидуальное сопровождение</div>
                            <div>Небольшое количество человек. Можем организовать путешествие на основе ваших пожеланий. Едем на хорошей машине.</div>
                            <div>
                                <a class = "button" href = "/tours#individual_support">Выбрать путешествие</a>
                                <!--							<input type = "button" value = "Выбрать путешествие" onclick = " window.location.href = '/tours';">-->
                            </div>
                        </div>
                    </div>
                    <div>
                        <div></div>
                        <div>
                            <div>ВИП</div>
                            <div>Небольшое количество человек. Можем организовать путешествие на основе ваших пожеланий. Едем на хорошей машине.</div>
                            <div>
                                <a class = "button" href = "/tours#VIP">Выбрать путешествие</a>
                                <!--							<input type = "button" value = "Выбрать путешествие" onclick = " window.location.href = '/tours';">-->
                            </div>
                        </div>
                    </div>
                    <div>
                        <div></div>
                        <div>
                            <div>Выходного дня</div>
                            <div>Небольшое количество человек. Можем организовать путешествие на основе ваших пожеланий. Едем на хорошей машине.</div>
                            <div>
                                <a class = "button" href = "/tours#weekend_tour">Выбрать путешествие</a>
                                <!--							<input type = "button" value = "Выбрать путешествие" onclick = " window.location.href = '/tours';">-->
                            </div>
                        </div>
                    </div>
                </div>
			</div>
		</div>
		<div class = "block adventure">
            <div>
                <div class = "header">Наши приключения</div>
                <div>Истории из наших путешествий,
                    <br>рассказанные участниками</div>
				<a class = "button semi_white" href = "/adventures">Читать</a>
            </div>
        </div>
		<div class = "block photo p">
			<div class = "head_photo">
				<div class = "header">Фотографии с наших путешествий</div>
<!--				<div>-->
<!--					<div></div>-->
<!--					<div></div>-->
<!--				</div>-->
			</div>
			<div>
				<div class = "arrow_left"></div>
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
				<div  class = "arrow_right"></div>
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
            let data = [
                { id: 1, name: 'Основные путешествия', tours: [
                        { id: 1, name: 'Байкал, остров Ольхон. 28 декабря - 6 января', href: '/tour/1' },
                        { id: 2, name: 'Чулышманская долина. 1-8 мая', href: '/tour/2' },
                        { id: 3, name: 'Ак-туру. 24-30 июня', href: '/tour/3' },
                        { id: 4, name: 'Чулышманская долина. 20-29 июля', href: '/tour/4' },
                        { id: 5, name: 'Каракольские озера. 2-10 августа', href: '/tour/5' },
                        { id: 6, name: 'Ак-туру. 27 августа - 3 сентября', href: '/tour/6' }
                    ] },
                { id: 2, name: 'Индивидуальное сопровождение', tours: [
                        { id: 1, name: 'Турция. 16-29 мая', href: '/tour/7' },
                        { id: 2, name: 'Чулышманская долина. 20-29 июля', href: '/tour/8' },
                        { id: 3, name: 'Каракольские озера. 12-20 сентября', href: '/tour/9' },
                        { id: 4, name: 'Дагестан. 28 октября - 4 ноября', href: '/tour/10' }
                    ] },
                { id: 3, name: 'ВИП', tours: [
                        { id: 1, name: 'Дагестан. 6-12 июля', href: '/tour/11' },
                        { id: 2, name: 'Каракольские озера. 21-26 августа', href: '/tour/12' }
                    ] },
                { id: 4, name: 'Выходного дня', tours: [
                        { id: 1, name: 'Маяк. 10 января', href: '/tour/13' },
                        { id: 2, name: 'Парабель. 17-19 марта', href: '/tour/14' },
                        { id: 3, name: 'Таловские чаши. 15 февраля', href: '/tour/15' },
                    ] }
            ];
            $(() => {
                ScrollTop('main');
                new SelectTour(data);
                Switcher('.switch_menu', '.switch_list');
            });
        </script>
        <?php
	}

