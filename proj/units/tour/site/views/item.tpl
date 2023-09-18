<?php

    namespace Proj\Site\Templates\Tour;

    use Base\Templates\Template;

    abstract class Item {

        public static function ToVar(array $data, array $program, array $expense, array $additional_expense): string {
			Template::Start();
        	self::Render($data, $program, $expense, $additional_expense);
            return Template::Read();
        }

        public static function Render(array $data, array $program, array $expense, array $additional_expense): void { ?>
			<?php if ($expense && $additional_expense) self::Expenses($data, $expense, $additional_expense); ?>
			<?php /*if ($expense && $additional_expense) self::Expenses($data, $expense, $additional_expense);*/ ?>
            <?php if ($program) self::Program($program); ?>
<!--            <div class = "tour_photo block p">-->
<!--                <div class = "header">Фотографии</div>-->
<!--                <div class = "block tour_mini_photo">-->
<!--                    <div></div>-->
<!--                    <div></div>-->
<!--                    <div></div>-->
<!--                    <div></div>-->
<!--                    <div></div>-->
<!--                    <div></div>-->
<!--                </div>-->
<!--                <div>-->
<!--                    <a class = "button" href = "/photoalbum" >Смотреть альбом</a>-->
<!--                </div>-->
<!--            </div>-->
            <div class = "tour_take_things block p print">
                <div>
                    <div class = "header">Что взять с собой</div>
                    <span onclick = "window.print();" class = "print_btn" title="распечатать"></span>
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

<!--            <div class = "block p">-->
<!--                <div class = "other_publication other_tour">-->
<!--                    <div>-->
<!--                        <span class = "header" onclick = " window.location.href = '/tours';">Другие путешествия</span>-->
<!--                    </div>-->
<!--                    <div id = "carousel">-->
<!--                        <div class = "arrow_left"></div>-->
<!--                        <div>-->
<!--                            <a href = "/tour">-->
<!--                                <span>Ликийская тропа, Каппадокия</span>-->
<!--                                <span>-->
<!--                                <span>1-10 октября</span>-->
<!--                                <span>65 000 </span>-->
<!--                            </span>-->
<!--                            </a>-->
<!--                            <a href = "/tour">-->
<!--                                <span>Каракольские озера</span>-->
<!--                                <span>-->
<!--                                <span>24-30 июня</span>-->
<!--                                <span>40 000 </span>-->
<!--                            </span>-->
<!--                            </a>-->
<!--                            <a href = "/tour">-->
<!--                                <span>Чулышманская долина</span>-->
<!--                                <span>-->
<!--                                <span>6-13 мая</span>-->
<!--                                <span>35 000 </span>-->
<!--                            </span>-->
<!--                            </a>-->
<!--                            <a href = "/tour">-->
<!--                                <span>Байкал, о. Ольхон, встреча Нового Года</span>-->
<!--                                <span>-->
<!--                                <span>30 дек-5 янв</span>-->
<!--                                <span>33 000 </span>-->
<!--                            </span>-->
<!--                            </a>-->
<!--                        </div>-->
<!--                        <div class = "arrow_right"></div>-->
<!--                    </div>-->
<!--                </div>-->
<!--            </div>-->
        <?php }

        public static function Expense(string $expense): void { ?>
			<div>
				<div>-</div>
				<div><?= $expense; ?></div>
			</div>
        <?php }

        public static function AdditionalExpense(string $expense): void { ?>
			<div>
				<div>-</div>
				<div><?= $expense; ?></div>
			</div>
        <?php }

		public static function ProgramItem($item): void { ?>
			<div>
				<div><?= $item['day']; ?></div>
				<div><?= $item['description']; ?></div>
			</div>
		<?php }

        private static function Program(array $program): void { ?>
            <div class = "tour_program block p">
                <div class = "header">Маршрут</div>
                <div>
                    <div class = "map"></div>
                    <div class = "days"><?php foreach ($program as $item) self::ProgramItem($item); ?></div>
                </div>

            </div>
        <?php }

        public static function Expenses($data, $expenses, $additional_expenses): void { ?>
			<div class = "tour_price block p">
				<div>Что входит в стоимость</div>
				<div>
					<div>
						<div>Цена <?= MoneyFormat($data['price']); ?> ₽ включает:</div>
						<div class = "list"><?php foreach ($expenses as $item) self::Expense($item); ?></div>
					</div>
					<div>
						<div>Дополнительные расходы:</div>
						<div class = "list"><?php foreach ($additional_expenses as $item) self::AdditionalExpense($item); ?></div>
					</div>
				</div>
			</div>
        <?php }

    }