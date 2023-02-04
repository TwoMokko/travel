<?php

	namespace Proj\Site\Templates\Test;

	use Base\Templates\View;

	class Footer extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render() { ?>
			<div class = "block footer">
				<div class = "block p">
					<div>
						<div class = "footer_contact">
							<div>
								<a href = "/"></a>
							</div>
							<div>
								<div class = "number">+7-909-545-11-29</div>
								<div class = "contact">
									<a href = " https://t.me/idapohod"></a>
									<a href = "https://www.youtube.com/@idapohod1718"></a>
									<a href = "https://vk.com/idatravel"></a>
									<a href = "https://instagram.com/idapohod"></a>
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
					<form action = "/feedback">
						<input name = "name" type = "text" placeholder = "Имя*" class = "footer_input">
						<input name = "contact" type = "text" placeholder = "Способ связи*" class = "footer_input">
						<a class = "button semi_white" onclick = "Base.Common.Query.SendForm($(this).closest('form'), AfterSend);/*AfterSend(this); event.preventDefault();*/">Отправить</a>
<!--					<input type = "submit" value = "Отправить" class = "semi_white" onclick = "AfterSend(); event.preventDefault();" >-->
					</form>
				</div>
			</div>
		<?php }

	}