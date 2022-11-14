<?php

    require 'templates/top.tpl';
    require 'templates/footer.tpl';
    require 'templates/main.tpl';

    function Title(): string {
        return 'Путешествия';
    }

    function Head(): void {
        ?><div class = "block hat other">
        <div class = "tours_hat"></div>
        <?php Top(); ?>
        <div>
            <div>Путешествия</div>
            <div>Возможно, текст</div>
        </div>
        </div><?php
    }

    function Main(): void {
        ?>
        <div class = "block page_tours p">
            <div>Основные путешествия</div>
            <div class = "cards_tours">
                <div>
                    <div></div>
                    <div>
                        <div>Дата</div>
						<div>Название</div>
						<div>Описание</div>
                        <div>Цена</div>
                        <div>
                            <input type = "button" value = "Подробнее" class = "border" class = "border" onclick = " window.location.href = '/tour';">
                            <input type = "button" value = "Поехать">
                        </div>
					</div>
                </div>
                <div>
                    <div></div>
					<div>
                        <div>Дата</div>
						<div>Название</div>
						<div>Описание</div>
                        <div>Цена</div>
                        <div>
                            <input type = "button" value = "Подробнее" class = "border" class = "border" onclick = " window.location.href = '/tour';">
                            <input type = "button" value = "Поехать">
                        </div>
					</div>
                </div>
                <div>
                    <div></div>
					<div>
                        <div>Дата</div>
						<div>Название</div>
						<div>Описание</div>
                        <div>Цена</div>
                        <div>
                            <input type = "button" value = "Подробнее" class = "border" class = "border" onclick = " window.location.href = '/tour';">
                            <input type = "button" value = "Поехать">
                        </div>
					</div>
                </div>
                <div>
                    <div></div>
					<div>
                        <div>Дата</div>
						<div>Название</div>
						<div>Описание</div>
                        <div>Цена</div>
                        <div>
                            <input type = "button" value = "Подробнее" class = "border" class = "border" onclick = " window.location.href = '/tour';">
                            <input type = "button" value = "Поехать">
                        </div>
					</div>
                </div>
                <div>
                    <div></div>
					<div>
                        <div>Дата</div>
						<div>Название</div>
						<div>Описание</div>
                        <div>Цена</div>
                        <div>
                            <input type = "button" value = "Подробнее" class = "border" class = "border" onclick = " window.location.href = '/tour';">
                            <input type = "button" value = "Поехать">
                        </div>
					</div>
                </div>
                <div>
                    <div></div>
					<div>
                        <div>Дата</div>
						<div>Название</div>
						<div>Описание</div>
                        <div>Цена</div>
                        <div>
                            <input type = "button" value = "Подробнее" class = "border" onclick = " window.location.href = '/tour';">
                            <input type = "button" value = "Поехать">
                        </div>
					</div>
                </div>
                <div>
                    <div></div>
					<div>
                        <div>Дата</div>
						<div>Название</div>
						<div>Описание</div>
                        <div>Цена</div>
                        <div>
                            <input type = "button" value = "Подробнее" class = "border" class = "border" onclick = " window.location.href = '/tour';">
                            <input type = "button" value = "Поехать">
                        </div>
					</div>
                </div>
                <div>
                    <div></div>
					<div>
                        <div>Дата</div>
						<div>Название</div>
						<div>Описание</div>
                        <div>Цена</div>
                        <div>
                            <input type = "button" value = "Подробнее" class = "border" class = "border" onclick = " window.location.href = '/tour';">
                            <input type = "button" value = "Поехать">
                        </div>
					</div>
                </div>
                <div>
                    <div></div>
					<div>
                        <div>Дата</div>
						<div>Название</div>
						<div>Описание</div>
                        <div>Цена</div>
                        <div>
                            <input type = "button" value = "Подробнее" class = "border" class = "border" onclick = " window.location.href = '/tour';">
                            <input type = "button" value = "Поехать">
                        </div>
					</div>
                </div>
            </div>
        </div>
        <div class = "block page_tours p">
            <div>Индивидуальное сопровождение</div>
            <div class = "cards_tours">
                <div>
                    <div></div>
					<div>
                        <div>Дата</div>
						<div>Название</div>
						<div>Описание</div>
                        <div>Цена</div>
						<div>
                            <input type = "button" value = "Подробнее" class = "border" class = "border" onclick = " window.location.href = '/tour';">
                            <input type = "button" value = "Поехать">
						</div>
					</div>
                </div>
				<div>
					<div></div>
					<div>
						<div>Дата</div>
						<div>Название</div>
						<div>Описание</div>
						<div>Цена</div>
						<div>
							<input type = "button" value = "Подробнее" class = "border" class = "border" onclick = " window.location.href = '/tour';">
							<input type = "button" value = "Поехать">
						</div>
					</div>
				</div>
				<div>
					<div></div>
					<div>
						<div>Дата</div>
						<div>Название</div>
						<div>Описание</div>
						<div>Цена</div>
						<div>
							<input type = "button" value = "Подробнее" class = "border" class = "border" onclick = " window.location.href = '/tour';">
							<input type = "button" value = "Поехать">
						</div>
					</div>
				</div>
            </div>
        </div>
        <div class = "block page_tours p">
            <div>ВИП</div>
            <div class = "cards_tours">
				<div>
					<div></div>
					<div>
						<div>Дата</div>
						<div>Название</div>
						<div>Описание</div>
						<div>Цена</div>
						<div>
							<input type = "button" value = "Подробнее" class = "border" class = "border" onclick = " window.location.href = '/tour';">
							<input type = "button" value = "Поехать">
						</div>
					</div>
				</div>
				<div>
					<div></div>
					<div>
						<div>Дата</div>
						<div>Название</div>
						<div>Описание</div>
						<div>Цена</div>
						<div>
							<input type = "button" value = "Подробнее" class = "border" class = "border" onclick = " window.location.href = '/tour';">
							<input type = "button" value = "Поехать">
						</div>
					</div>
				</div>
            </div>
        </div>
		<div class = "block page_tours p">
			<div>Выходного дня</div>
			<div class = "cards_tours">
				<div>
					<div></div>
					<div>
						<div>Дата</div>
						<div>Название</div>
						<div>Описание</div>
						<div>Цена</div>
						<div>
							<input type = "button" value = "Подробнее" class = "border" class = "border" onclick = " window.location.href = '/tour';">
							<input type = "button" value = "Поехать">
						</div>
					</div>
				</div>
				<div>
					<div></div>
					<div>
						<div>Дата</div>
						<div>Название</div>
						<div>Описание</div>
						<div>Цена</div>
						<div>
							<input type = "button" value = "Подробнее" class = "border" class = "border" onclick = " window.location.href = '/tour';">
							<input type = "button" value = "Поехать">
						</div>
					</div>
				</div>
			</div>
		</div>
        <?php
    }