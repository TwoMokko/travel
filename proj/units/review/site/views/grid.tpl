<?php

	namespace Proj\Site\Templates\Review;

	use Base\Templates\Buffering;

	abstract class Grid extends Item {

		public static function ToVar(array $items, array $avatars): string {
			Buffering::Start();
			self::Render($items, $avatars);
			return Buffering::Read();
		}

		public static function Render($items, $avatars): void { ?>
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

	}