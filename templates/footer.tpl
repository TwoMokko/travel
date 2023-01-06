<?php

    function Footer(): void {
        ?><div class = "block footer">
			<div class = "block p">
				<div>
					<div class = "footer_contact">
						<div>
							<a href = "/"></a>
						</div>
						<div>
							<div class = "number">+7-909-545-11-29</div>
							<div class = "contact">
								<div></div>
								<div></div>
								<div></div>
								<div></div>
							</div>
						</div>
					</div>
					<div  class = "footer_menu">
						<div><a href = "/">Главная</a></div>
						<div><a href = "/tours">Путешествия</a></div>
						<div><a href = "/about">О нас</a></div>
						<div><a href = "/adventures">Наши приключения</a></div>
						<div><a href = "/photo">Фотографии</a></div>
					</div>
				</div>
				<form>
					<input type = "text" placeholder="Имя*" class = "footer_input">
					<input type = "text" placeholder="Способ связи*" class = "footer_input">
					<input type = "submit" value = "Отправить" class = "semi_white" onclick = "AfterSend(); event.preventDefault();" >
				</form>
			</div>
<!--            <div class = "block p">-->
<!--                <div>-->
<!--					<div>-->
<!--						<a href = "/"></a>-->
<!--					</div>-->
<!--                    <div>-->
<!--                        <div class = "contact">-->
<!--                            <div></div>-->
<!--                            <div></div>-->
<!--                            <div></div>-->
<!--                            <div></div>-->
<!--                        </div>-->
<!--                        <div>+7-909-545-11-29</div>-->
<!--                    </div>-->
<!--                    <div>-->
<!--                        <input type = "text" placeholder="Имя*" class = "footer_input">-->
<!--                        <input type = "text" placeholder="Способ связи*" class = "footer_input">-->
<!--                        <input type = "button" value = "Отправить" class = "semi_white">-->
<!--                    </div>-->
<!--                </div>-->
<!--                <div  class = "footer_menu">-->
<!--                    <a href = "/">Главная</a>-->
<!--                    <a href = "/tours">Путешествия</a>-->
<!--                    <a href = "/about">О нас</a>-->
<!--                    <a href = "/adventures">Наши приключения</a>-->
<!--                    <a href = "/photo">Фотографии</a>-->
<!--                </div>-->
<!--            </div>-->
<!--            <div class = "block p">-->
<!--                <div class = "footer_left">-->
<!--                    <div>-->
<!--						<a href = "/"></a>-->
<!--					</div>-->
<!--                    <div>Организуем<br>путешествия</div>-->
<!--                </div>-->
<!--                <div class = "footer_right">-->
<!--                    <div class = "footer_menu">-->
<!--                        <a href = "/tours.php">Путешествия</a>-->
<!--                        <a href = "/about">О нас</a>-->
<!--                        <a href = "/adventures.php">Наши приключения</a>-->
<!--                        <a href = "/photo">Фотографии</a>-->
<!--                    </div>-->
<!--                    <div  class = "footer_right_down">-->
<!--						<div>-->
<!--							<div></div>-->
<!--							<div></div>-->
<!--							<div></div>-->
<!--							<div></div>-->
<!--						</div>-->
<!--                        <div>+7-909-545-11-29</div>-->
<!--                        <div>-->
<!--                            <input type = "button" value = "Написать" class = "transparent">-->
<!--                        </div>-->
<!--                    </div>-->
<!--                </div>-->
<!--            </div>-->
        </div><?php
    }