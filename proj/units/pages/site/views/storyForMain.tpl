<?php

    namespace Proj\Site\Templates\Pages;

	use Proj\Site\Actions;
    use Base\Templates\Template;

    abstract class StoryForMain {

        public static function ToVar(string $header, string $text, string $button): string {
            Template::Start();
            self::Render($header, $text, $button);
            return Template::Read();
        }

        public static function Render(string $header, string $text, string $button): void { ?>
			<div class = "block adventure">
				<div>
					<div class = "header"><?= nl2br($header); ?></div>
					<div><?= nl2br($text); ?></div>
					<?= Actions\Pages::$stories->GetLinkHref(nl2br($button), [], ['class' => 'button semi_white']); ?>
				</div>
			</div>
        <?php }

    }