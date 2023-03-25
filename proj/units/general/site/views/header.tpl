<?php

	namespace Proj\Site\Templates\General;

	use Base\Templates\Template;

	abstract class Header {

		public static function ToVar(): string {
			Template::Start();
			self::Render();
			return Template::Read();
		}

		public static function Render(): void { ?>
			<div class = "block top">
				<div><a href = "/"></a></div>
				<?php self::Menu(); ?>
				<div class = "open_menu" onclick = "new Menu();"></div>

			</div>
		<?php }

		private static function Menu(): void { ?>
			<div class = "block menu">
				<div><a href = "/">Главная</a></div>
				<div><a href = "/tours">Путешествия</a></div>
				<div><a href = "/about">О нас</a></div>
				<div><a href = "/stories">Наши приключения</a></div>
				<div><a href = "/photo">Фотографии</a></div>
			</div>
		<?php }

	}