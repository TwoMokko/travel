<?php

    namespace Proj\Site\Templates\Reviews;

    use Base\Templates\Template;
	use Proj\Site\Units;
    use Proj\Units\Consts;

	abstract class Lists {

		public static function ToVarCarousel(array $items): string {
			Template::Start();
			self::Carousel($items);
			return Template::Read();
		}

		public static function ToVarGrid(array $items): string {
			Template::Start();
			self::Grid($items);
			return Template::Read();
		}

        public static function Carousel($items): void { ?>
            <div class = "block p reviews">
                <div>
                    <div class = "header" onclick = "window.location.href = '<?= Units\Reviews::instance()->for_list->GetPath(); ?>';">Отзывы</div>
                    <span onclick = "LeaveReview();" title = "оставить отзыв"></span>
                </div>
                <div id = "review" class = "carousel">
                    <?php foreach ($items as $item) self::Item($item); ?>
                </div>
            </div>
            <script>
                $(() => new Carousel('#review', 2));
            </script>
        <?php }

        public static function Grid($items): void { ?>
            <div class = "block p page_reviews">
                <div class = "review_cards">
					<?php foreach ($items as $item) self::Item($item); ?>
                </div>
            </div>
        <?php }

        private static function Item($data): void { ?>
            <div class = "review_card" onclick = "GetReview('<?= Units\Reviews::instance()->get->GetPath(); ?>', <?= $data['id']; ?>);">
                <div class = "review_person">
                    <div style = "background-image: url(<?= Consts\Reviews::PATH_AVATAR_RELATIVE, $data['image']; ?>);"></div>
                    <div><?= $data['name']; ?></div>
                </div>
                <div class = "review_text"><?= $data['text']; ?></div>
            </div>
        <?php }

    }