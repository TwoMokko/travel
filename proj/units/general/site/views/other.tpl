<?php

	namespace Proj\Site\Templates\General;

	use Base\Templates\Template;
	use Proj\Site\Units\Pages;
	use Proj\Units\Consts;

	abstract class Other {

		public static function AboutMain(string $header, string $text): string {
			Template::Start();
			self::RenderAboutMain($header, $text);
			return Template::Read();
		}

		public static function RenderAboutMain(string $header, string $text): void { ?>
			<div class = "block about_us p">
				<div></div>
				<div class = "header"><?= nl2br($header); ?></div>
				<div><?= nl2br($text); ?></div>
			</div>
		<?php }

		public static function StoryMain(string $header, string $text, string $button): string {
			Template::Start();
			self::RenderStoryMain($header, $text, $button);
			return Template::Read();
		}

		public static function RenderStoryMain(string $header, string $text, $button): void { ?>
            <div class = "block adventure">
                <div>
                    <div class = "header"><?= nl2br($header); ?></div>
                    <div><?= nl2br($text); ?></div>
					<?= Pages::instance()->stories->GetLink(nl2br($button), [], ['class' => 'button semi_white']); ?>
<!--                    <a class = "button semi_white" href = "/stories">--><?//= nl2br($button); ?><!--</a>-->
                </div>
            </div>
		<?php }

		public static function AboutPage(string $header, string $text, string $mini_text, string $video, string $image): string {
			Template::Start();
			self::RenderAboutPage($header, $text, $mini_text, $video, $image);
			return Template::Read();
		}

		public static function RenderAboutPage(string $header, string $text, string $mini_text, string $video, string $image): void { ?>

            <div class = "page_about_us">
                <div class = "about_header block p">
                    <div>
                        <div><?= nl2br($header); ?></div>
                        <div><?= nl2br($text); ?></div>
                        <div class = "right_text"><?= nl2br($mini_text); ?></div>
                    </div>
                    <div style = "background-image: url('<?= $image; ?>');"></div>
                </div>
                <div class = "block p"">
<!--                <div class = "play">-->
<!--                    <div ></div>-->
<!--                </div>-->
				<iframe class = "play_iframe" src = "<?= nl2br($video); ?>" allowfullscreen frameborder = "0"></iframe>
            </div>
		<?php }

        public static function ScrollTop(): string {
            Template::Start();
            self::RenderScrollTop();
            return Template::Read();
        }


        public static function RenderScrollTop(): void { ?>
            <script>
                $(() => ScrollTop('main'));
            </script>
        <?php }
	}