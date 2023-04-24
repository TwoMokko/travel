<?php

	namespace Proj\Site\Templates\General;

	use Base\Templates\Template;

	abstract class Footer {

		public static function ToVar(): string {
			Template::Start();
			self::Render();
			return Template::Read();
		}

		public static function Render(): void { ?>
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
									<a href = "https://t.me/idapohod" target = "_blank"></a>
									<a href = "https://www.youtube.com/@idapohod1718" target = "_blank"></a>
									<a href = "https://vk.com/idatravel" target = "_blank"></a>
									<a href = "https://instagram.com/idapohod" target = "_blank"></a>
								</div>
							</div>
						</div>
						<div  class = "footer_menu">
							<div><a href = "/">Главная</a></div>
							<div><a href = "/tours">Путешествия</a></div>
							<div><a href = "/about">О нас</a></div>
							<div><a href = "/stories">Наши приключения</a></div>
							<div><a href = "/photo">Фотографии</a></div>
						</div>
					</div>
					<form action = "/feedback">
						<input name = "name" type = "text" placeholder = "Имя*" class = "footer_input">
						<input name = "contact" type = "text" placeholder = "Способ связи*" class = "footer_input">
						<a class = "button semi_white" onclick = "Base.Common.Query.SendForm($(this).closest('form'), AfterSend);">Отправить</a>
					</form>
				</div>
			</div>
		<?php }

	}