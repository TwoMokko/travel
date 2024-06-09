<?php

	namespace Proj\Site\Templates\Pages;

	use Base\Templates\Buffering;
	use Proj\Site\Actions;

	abstract class Footer {

		public static function ToVar(): string {
			Buffering::Start();
			self::Render();
			return Buffering::Read();
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
							<div><?= Actions\Pages::$home->GetLinkHref('Главная'); ?></div>
							<div><?= Actions\Pages::$tours->GetLinkHref('Путешествия'); ?></div>
							<div><?= Actions\Pages::$about->GetLinkHref('О нас'); ?></div>
							<div><?= Actions\Pages::$stories->GetLinkHref('Дневник путешествий'); ?></div>
                            <div><?= Actions\Pages::$review->GetLinkHref('Отзывы'); ?></div>
                            <div><?= Actions\Pages::$albums->GetLinkHref('Фотоальбомы'); ?></div>
						</div>
					</div>
					<form action = "/feedback/add">
						<input name = "name" type = "text" placeholder = "Имя*" class = "footer_input" minlength="3" maxlength="50">
						<input name = "contact" type = "text" placeholder = "Способ связи*" class = "footer_input" minlength="3" maxlength="50">
						<a class = "button semi_white" onclick = "if (Validation.Form($(this).closest('form'))) Base.Common.Query.SendForm($(this).closest('form'), AfterSend);">Отправить</a>
					</form>
				</div>
			</div>
		<?php }

	}