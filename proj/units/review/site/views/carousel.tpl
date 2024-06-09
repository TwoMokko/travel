<?php

    namespace Proj\Site\Templates\Review;

    use Base\Templates\Buffering;
	use Proj\Site\Actions;

	abstract class Carousel extends Item {

		public static function ToVar(array $items, array $avatars): string {
			Buffering::Start();
			self::Render($items, $avatars);
			return Buffering::Read();
		}

		public static function Render($items, $avatars): void { ?>
			<div class = "block p reviews">
				<div class = "leave_review">
					<?= Actions\Pages::$review->GetLinkHref('Отзывы', [], ['class' => 'header']); ?>
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

    }