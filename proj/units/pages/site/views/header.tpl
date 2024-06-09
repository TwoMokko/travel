<?php

	namespace Proj\Site\Templates\Pages;

	use Base\Templates\Template;
	use Proj\Site\Actions;

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
				<div><?= Actions\Pages::$home->GetLinkHref('Главная') ?></div>
				<div><?= Actions\Pages::$tours->GetLinkHref('Путешествия') ?></div>
				<div><?= Actions\Pages::$about->GetLinkHref('О нас'); ?></div>
				<div><?= Actions\Pages::$stories->GetLinkHref('Дневник путешествий') ?></div>
				<div><?= Actions\Pages::$review->GetLinkHref('Отзывы'); ?></div>
				<div><?= Actions\Pages::$albums->GetLinkHref('Фотоальбомы'); ?></div>
			</div>
		<?php }

	}