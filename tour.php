<?php

    require 'templates/top.tpl';
    require 'templates/footer.tpl';
    require 'templates/main.tpl';

    function Title(): string {
        return 'Путешествия';
    }

    function Head(): void {
        ?><div class = "block hat other">
        <div class = "tour"></div>
        <?php Top(); ?>
        <div>
            <div>Путешествия</div>
            <div>Возможно, текст</div>
        </div>
        </div><?php
    }

    function Main(): void {
        ?>
        <div class = "block page_tour p">
            <div>Индивидуальное сопровождение</div>
            <div class = "cards_tour">
                <div>
                    <div></div>
                    <div>
						<div>Название</div>
						<div>Дата</div>
						<div>Описание</div>
						<div>
							<div>
								<div>Цена</div>
							</div>
							<div>
								<input type = "button" value = "Оставить заявку">
							</div>
						</div>
					</div>
                </div>
                <div>
                    <div></div>
					<div>
						<div>Название</div>
						<div>Дата</div>
						<div>Описание</div>
						<div>
							<div>
								<div>Цена</div>
							</div>
							<div>
								<input type = "button" value = "Оставить заявку">
							</div>
						</div>
					</div>
                </div>
                <div>
                    <div></div>
					<div>
						<div>Название</div>
						<div>Дата</div>
						<div>Описание</div>
						<div>
							<div>
								<div>Цена</div>
							</div>
							<div>
								<input type = "button" value = "Оставить заявку">
							</div>
						</div>
					</div>
                </div>
                <div>
                    <div></div>
					<div>
						<div>Название</div>
						<div>Дата</div>
						<div>Описание</div>
						<div>
							<div>
								<div>Цена</div>
							</div>
							<div>
								<input type = "button" value = "Оставить заявку">
							</div>
						</div>
					</div>
                </div>
                <div>
                    <div></div>
					<div>
						<div>Название</div>
						<div>Дата</div>
						<div>Описание</div>
						<div>
							<div>
								<div>Цена</div>
							</div>
							<div>
								<input type = "button" value = "Оставить заявку">
							</div>
						</div>
					</div>
                </div>
                <div>
                    <div></div>
					<div>
						<div>Название</div>
						<div>Дата</div>
						<div>Описание</div>
						<div>
							<div>
								<div>Цена</div>
							</div>
							<div>
								<input type = "button" value = "Оставить заявку">
							</div>
						</div>
					</div>
                </div>
                <div>
                    <div></div>
					<div>
						<div>Название</div>
						<div>Дата</div>
						<div>Описание</div>
						<div>
							<div>
								<div>Цена</div>
							</div>
							<div>
								<input type = "button" value = "Оставить заявку">
							</div>
						</div>
					</div>
                </div>
                <div>
                    <div></div>
					<div>
						<div>Название</div>
						<div>Дата</div>
						<div>Описание</div>
						<div>
							<div>
								<div>Цена</div>
							</div>
							<div>
								<input type = "button" value = "Оставить заявку">
							</div>
						</div>
					</div>
                </div>
                <div>
                    <div></div>
					<div>
						<div>Название</div>
						<div>Дата</div>
						<div>Описание</div>
						<div>
							<div>
								<div>Цена</div>
							</div>
							<div>
								<input type = "button" value = "Оставить заявку">
							</div>
						</div>
					</div>
                    </div>
                </div>
            </div>
        </div>
        <div class = "block page_tour p">
            <div>Путешествия</div>
            <div class = "cards_tour">
                <div>
                    <div></div>
					<div>
						<div>Название</div>
						<div>Дата</div>
						<div>Описание</div>
						<div>
							<div>
								<div>Цена</div>
							</div>
							<div>
								<input type = "button" value = "Оставить заявку">
							</div>
						</div>
					</div>
                </div>
            </div>
        </div>
        <div class = "block page_tour p">
            <div>Короткие путешествия</div>
            <div class = "cards_tour">
                <div>
                    <div></div>
					<div>
						<div>Название</div>
						<div>Дата</div>
						<div>Описание</div>
						<div>
							<div>
								<div></div>
							</div>
							<div>
								<input type = "button" value = "Оставить заявку">
								<input type = "button" value = "Оставить заявку">
							</div>
						</div>
					</div>
                </div>
            </div>
        </div>
        <?php
    }