<?php

    namespace Proj\Site\Templates\Tour;

    use Base\Templates\Template;

    abstract class Video {

        public static function ToVar(array $data): string {
			Template::Start();
        	self::Render($data);
            return Template::Read();
        }

        public static function Render(array $data): void { ?>
			<div class = "tour_video block">
				<div>
					<div class = "header">Видео с путешествия</div>
					<!--                    <div class = "play">-->
					<!--                        <div></div>-->
					<!--                    </div>-->
					<iframe class = "play_iframe" src = "<?= $data['video']; ?>" allowfullscreen frameborder = "0"></iframe>
				</div>
			</div>
         <?php }

    }