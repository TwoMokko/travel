<?php

    namespace Proj\Site\Templates\Reviews;

    use Base\Templates\Template;
	use Proj\Site\Units;
    use Proj\Units\Consts;

	abstract class Lists {

		public static function ToVarCarousel(array $items, array $avatars): string {
			Template::Start();
			self::Carousel($items, $avatars);
			return Template::Read();
		}

		public static function Carousel($items, $avatars): void { ?>
			<div class = "block p reviews">
				<div class = "leave_review">
					<a class = "header" onclick = "window.location.href = '<?= Units\Pages::instance()->review->GetPath(); ?>';" href = "<?= Units\Pages::instance()->review->GetPath(); ?>">Отзывы</a>
					<span onclick = 'LeaveReview(<?= json_encode($avatars); ?>);' title = "оставить отзыв"></span>
				</div>
				<div id = "review" class = "carousel">
					<?php foreach ($items as $item) self::Item($item); ?>
				</div>
			</div>
			<script>
				$(() => new Carousel('#review'));
			</script>
		<?php }

		public static function ToVarGrid(array $items, array $avatars): string {
			Template::Start();
			self::Grid($items, $avatars);
			return Template::Read();
		}

        public static function Grid($items, $avatars): void { ?>

            <div class = "block p page_reviews">
				<div class = "leave_review" onclick = 'LeaveReview(<?= json_encode($avatars); ?>);' title = "оставить отзыв">
					<a class = "header">Отавить отзыв</a>
					<span></span>
				</div>
                <div class = "review_cards">
					<?php foreach ($items as $item) self::Item($item); ?>
                </div>
            </div>
        <?php }

        private static function Item($data): void { ?>
            <div class = "review_card" onclick = "GetReview('<?= Units\Reviews::instance()->get->GetPath(); ?>', <?= $data['id']; ?>);">
                <div class = "review_person">
                    <div style = "background-image: url(<?= Consts\Reviews::AVATARS[$data['avatar']] ?>);"></div>
                    <div><?= htmlspecialchars($data['name']); ?></div>
                </div>
                <div class = "review_text"><?= htmlspecialchars($data['text']); ?></div>
            </div>
        <?php }

    }