<?php

	namespace Proj\Site\Templates\General;

	use Base\Templates\Template;

	abstract class Other {

		public static function AboutMain(string $header, string $text): string {
			Template::Start();
			self::Render($header, $text);
			return Template::Read();
		}

		public static function Render(string $header, string $text): void { ?>
			<div class = "block about_us p">
				<div></div>
				<div class = "header"><?= nl2br($header); ?></div>
				<div><?= nl2br($text); ?></div>
			</div>
		<?php }

	}