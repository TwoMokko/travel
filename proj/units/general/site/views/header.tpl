<?php

	namespace Proj\Site\Templates\General;

	use Base\Templates\Template;
    use Proj\Site\Units;

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
				<div><a href = "<?= Units\Tour::instance()->all->GetPath(); ?>">Путешествия</a></div>
				<div><a href = "<?= Units\People::instance()->people->GetPath(); ?>">О нас</a></div>
				<div><a href = "<?= Units\Story::instance()->all->GetPath(); ?>">Наши приключения</a></div>
				<div><a href = "<?= Units\Photo::instance()->all->GetPath(); ?>">Фотографии</a></div>
			</div>
		<?php }

	}