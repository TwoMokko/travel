<?php

	require 'templates/top.tpl';
	require 'templates/footer.tpl';
	require 'templates/main.tpl';

    function Title(): string {
        return 'О нас';
    }

    function Head(): void {
        ?><div class = "block hat other">
			<div class = "about_hat"></div>
			<?php Top(); ?>
            <div>
				<div>О нас</div>
				<div>Возможно, текст</div>
			</div>
        </div><?php
    }


    function Main(): void {
        ?><div class = "page_about_us">
            <div class = "about_header block p">
                <div>
                    <div>что-то</div>
                    <div>
						<div>Организуем путешествия на основе ваших пожеланий,</div>
						<div>а так же по подготовленным нами маршрутам</div>
						<div>Организуем путешествия на основе ваших пожеланий,</div>
						<div>а так же по подготовленным нами маршрутам</div>
					</div>
                    <div class = "right_text">Еще какой-то текст подлиннее, например, что-то немного о создании или о миссии или о ценностях</div>
                </div>
                <div></div>
            </div>
            <div class = "block p"">
            <div class = "play">
                <div></div>
            </div>
            </div>
			<div class = "block p team">
				<div>
					<div class = "about_pic"></div>
					<div class = "about_text">
<!--						<div>Организатор</div>-->
						<div>Ишмурзина Нина</div>
						<div>Еще какой-то текст подлиннее, например, что-то немного о создании или о миссии или о ценностях</div>
						<div class = "contact_person">
							<div>
								<div>Тел:</div>
								<div>+7-909-545-11-29</div>
							</div>
							<div>
								<div></div>
								<div></div>
							</div>
						</div>
					</div>
				</div>
				<div>
					<div class = "about_pic"></div>
					<div class = "about_text">
<!--						<div>Должность</div>-->
						<div>Меховников Сергей</div>
						<div>Супер крутое описание человека которыей чем-то занимается в этой компании</div>
						<div class = "contact_person">
							<div>
								<div>Тел:</div>
								<div>+7-923-424-52-22</div>
							</div>
							<div>
								<div></div>
								<div></div>
							</div>
						</div>
					</div>
				</div>
			</div>
        </div>
        <script>
            $(() => ScrollTop('main'));
        </script>
        <?php
    }
