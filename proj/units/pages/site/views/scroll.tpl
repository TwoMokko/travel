<?php

	namespace Proj\Site\Templates\Pages;

	use Base\Templates\Buffering;

	abstract class Scroll {

		public static function ToVar(): string {
			Buffering::Start();
			self::Render();
			return Buffering::Read();
		}

		public static function Render(): void { ?>
			<script>
                $(() => ScrollTop('main'));
			</script>
		<?php }

	}