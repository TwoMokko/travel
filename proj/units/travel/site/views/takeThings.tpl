<?php

    namespace Proj\Site\Templates\Travel;

    use Base\Templates\Buffering;

    abstract class TakeThings {

        public static function ToVar(): string {
			Buffering::Start();
        	self::Render();
            return Buffering::Read();
        }

        public static function Render(): void { ?>
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
         <?php }

    }