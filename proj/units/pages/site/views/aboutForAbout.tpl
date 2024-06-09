<?php

	namespace Proj\Site\Templates\Pages;

	use Base\Templates\Buffering;

	abstract class AboutForAbout {

		public static function ToVar(string $header, string $text, string $mini_text, string $video, string $image): string {
			Buffering::Start();
			self::Render($header, $text, $mini_text, $video, $image);
			return Buffering::Read();
		}

		public static function Render(string $header, string $text, string $mini_text, string $video, string $image): void { ?>
			<div class = "page_about_us">
				<div class = "about_header block p">
					<div>
						<div><?= nl2br($header); ?></div>
						<div><?= nl2br($text); ?></div>
						<div class = "right_text"><?= nl2br($mini_text); ?></div>
					</div>
					<div style = "background-image: url('<?= $image; ?>');"></div>
				</div>
				<div class = "block p">
					<iframe class = "play_iframe" src = "<?= nl2br($video); ?>" allowfullscreen frameborder = "0"></iframe>
				</div>
			</div>
		<?php }

	}