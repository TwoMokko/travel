<?php

	namespace Proj\Site\Templates\Story;

	use Base\Templates\Template;
	use Proj\Site\Units\Pages;
	use Proj\Site\Units\Story;
	use Proj\Units\Consts;

	abstract class Show {

		public static function ToVar(array $data): string {
			Template::Start();
			self::Render($data);
			return Template::Read();
		}

		public static function Render($data): void { ?>
            <div class = "block p page_one_adventure">
                <div class = "adventure_text">
                    <div><?= $data['text']; ?></div>
                    <div>
                        <div data-id = "1" data-url = "<?= Consts\Story::PATH_COVER_RELATIVE . $data['image']; ?>" style = "background-image: url(<?= Consts\Story::PATH_COVER_RELATIVE . $data['image']; ?>););" onclick = "new Gallery(this);"></div>
<!--                        <div data-id = "1" data-url = "css/pic/photoalbum/18.jpg" style = "background-image: url('proj/templates/site/css/pic/photoalbum/18.jpg');" onclick = "new Gallery(this);"></div>-->
                    </div>
                </div>
            </div>
		<?php }

        public static function ToVarCarousel(array $items): string {
			Template::Start();
            self::Carousel($items);
            return Template::Read();
        }

        public static function Carousel($items): void { ?>
            <div class = "other_publication block p">
                <div>
                    <span class = "header" onclick = " window.location.href = '/stories';">Другие приключения</span>
                </div>
                <div id = "story" class = "carousel">
                   <?php foreach ($items as $item) {
					   $url = Consts\Story::PATH_COVER_RELATIVE . $item['image'];
					   echo Pages::instance()->story->GetLink(self::Item($item), ['id' => $item['id']], ['class' => 'other_public other_story', 'style' => "background-image: url('{$url}');"]);
					   /*Story::instance()->show->GetLink(self::Item($item), ['id' => $item['id']], ['class' => 'other_public other_story', 'style' => "background-image: url('{$url}');"]);*/
				   } ?>
                </div>
            </div>
            <script>
                $(() => new Carousel('#story'));
            </script>
        <?php }

		private static function Item($data): string {
			Template::Start();
			?>
			<span><?= $data['header']; ?></span>
			<?php
			return Template::Read();
		}

	}