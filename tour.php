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
			<div class = "about_tour block p">
				<div>Ольхон - самый большой остров на озере Байкал. Протяженность около 80 км и ширина 15 км.
					Именно в новогодние праздники из года в год Байкал застывает в прозрачный лёд.</div>
				<div class = "about_mini">
					<div>
						<div>Стоимость</div>
						<div>25 000 ₽</div>
					</div>
					<div>
						<div>Длительность</div>
						<div>7 дней</div>
					</div>
				</div>
			</div>
			<div class = "tour_video block p">
				<div>
					<div class = "header">Видео с путешествия</div>
					<div class = "play">
						<div></div>
					</div>
				</div>
			</div>
			<div class = "tour_price block p">
				<div>Что входит в стоимость</div>
				<div>
					<div>
						<div>Цена 25 000 ₽ включает:</div>
						<div class = "list">
							<div>
								<div>-</div>
								<div>Трансфер с места сбора и обратно</div>
							</div>
							<div>
								<div>-</div>
								<div>Питание</div>
							</div>
							<div>
								<div>-</div>
								<div>Проживание в домике</div>
							</div>
							<div>
								<div>-</div>
								<div>Обслуживание по программе</div>
							</div>
						</div>
					</div>
					<div>
						<div>Дополнительные расходы:</div>
						<div class = "list">
							<div>
								<div>-</div>
								<div>Билет на самолет/поезд до места встречи группы в Иркутске</div>
							</div>
							<div>
								<div>-</div>
								<div>Карманные расходы</div>
							</div>
						</div>
					</div>
				</div>
			</div>
			<div class = "tour_program block p">
				<div class = "header">Маршрут</div>
				<div>
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

			</div>
			<div class = "tour_photo block p">
				<div class = "header">Фотографии</div>
				<div class = "tour_mini_photo">
					<div></div>
					<div></div>
					<div></div>
					<div></div>
					<div></div>
					<div></div>
				</div>
				<div>
					<a class = "button" href = "/photoalbum" >Смотреть альбом</a>
				</div>
			</div>
            <div class = "tour_take_things block p">
				<div>
					<div class = "header">Что взять с собой</div>
					<span class = "print" title="распечатать"></span>
				</div>
                <div>
                    <div>
                        <div>Одежда</div>
                        <div>
                            <label><input type = "checkbox"><span>Термобелье</span></label>
                            <label><input type = "checkbox"><span>Футболки</span></label>
                            <label><input type = "checkbox"><span>Штаны</span></label>
                            <label><input type = "checkbox"><span>Флисовая кофта</span></label>
                            <label><input type = "checkbox"><span>Мембранная куртка</span></label>
                            <label><input type = "checkbox"><span>Шапка, перчатки</span></label>
                            <label><input type = "checkbox"><span>Носки для треккинга</span></label>
                            <label><input type = "checkbox"><span>Шерстяные носки</span></label>
                            <label><input type = "checkbox"><span>Чистая одежда</span></label>
                            <label><input type = "checkbox"><span>Треккинговые ботинки</span></label>
                            <label><input type = "checkbox"><span>Темные очки</span></label>
                            <label><input type = "checkbox"><span>Сланцы</span></label>
                            <label><input type = "checkbox"><span>Еще пункт</span></label>
                            <label><input type = "checkbox"><span>Еще пункт</span></label>
                        </div>
                    </div>
                    <div>
                        <div>Предметы личной гигиены</div>
                        <div>
                            <label><input type = "checkbox"><span>Гигиеническая помада</span></label>
                            <label><input type = "checkbox"><span>Зубная щетка, паста</span></label>
                            <label><input type = "checkbox"><span>Гель для душа, шампунь</span></label>
                            <label><input type = "checkbox"><span>Мочалка</span></label>
                            <label><input type = "checkbox"><span>Полотенце</span></label>
                        </div>
                    </div>
                    <div>
                        <div>Документы</div>
                        <div>
                            <label><input type = "checkbox"><span>Паспорт</span></label>
                            <label><input type = "checkbox"><span>Деньги (карточка)</span></label>
                            <label><input type = "checkbox"><span>Телефон</span></label>
                            <label><input type = "checkbox"><span>Медицинская страховка</span></label>
                        </div>
                    </div>
                    <div>
                        <div>Лекарства</div>
                        <div>
                            <label><input type = "checkbox"><span>Крем от солнечного загара</span></label>
                            <label><input type = "checkbox"><span>Индивидуальные препараты</span></label>
                        </div>
                    </div>
                </div>
            </div>
			<div class = "tour_dates block p"></div>
			<div class = "tour_form block p">
				<div class = "header">Оставить заявку</div>
				<div>
					<div>
						<div></div>
					</div>
					<div>
						<div>
							<div>
								<input type = "text" placeholder = "Имя*">
							</div>
							<div>
								<input type = "text" placeholder = "Способ связи*">
							</div>
						</div>
						<div>
							<textarea rows="5" placeholder = "Напишите сообщение или оставьте поле пустым"></textarea>
						</div>
						<!--					<div>-->
						<!--						<div>-->
						<!--							<div>Выберите путешествие и дату</div>-->
						<!--							<select class = "select_style">-->
						<!--								<option>Байкал, остров Ольхон. 28 декабря - 6 января</option>-->
						<!--								<option>Байкал, остров Ольхон. Аршан. 12 - 20 сентября</option>-->
						<!--							</select>-->
						<!--						</div>-->
						<!--						<div>-->
						<!--							<div>Количество человек</div>-->
						<!--							<select class = "select_style">-->
						<!--								<option>1</option>-->
						<!--								<option>2</option>-->
						<!--								<option>3</option>-->
						<!--								<option>4</option>-->
						<!--								<option>5</option>-->
						<!--								<option>группа</option>-->
						<!--							</select>-->
						<!--						</div>-->
						<!--					</div>-->
						<div>
							<input type = "button" value = "Оставить заявку">
						</div>
					</div>
				</div>

			</div>
            <div class = "block p">
                <div class = "other_publication other_tour">
                    <div>
                        <span onclick = " window.location.href = '/tours';">Другие путешествия</span>
                    </div>
                    <div>
                        <a href = "/tour">
                            <span>Ликийская тропа, Каппадокия</span>
                            <span>
                                <span>25 000 </span>
                                <span>Дата</span>
                            </span>
                        </a>
                        <a href = "/tour">Каракольские озера</a>
                        <a href = "/tour">Чулышманская долина</a>
                        <a href = "/tour">Название</a>
                    </div>
                </div>
            </div>

        </div>
        <script>
            $(() => ScrollTop('body'));
        </script>
        <?php
    }
