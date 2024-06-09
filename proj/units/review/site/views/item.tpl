<?php

	namespace Proj\Site\Templates\Review;

	use Proj\Units\Consts;
	use Proj\Site\Actions\Review;

	abstract class Item {

		protected static function Item($data): void { ?>
			<div class = "review_card" onclick = "GetReview('<?= Review::$get->GetPath(); ?>', <?= $data['id']; ?>);">
				<div class = "review_person">
					<div style = "background-image: url(<?= Consts\Review::AVATARS[$data['avatar']] ?>);"></div>
					<div><?= htmlspecialchars($data['name']); ?></div>
				</div>
				<div class = "review_text"><?= htmlspecialchars($data['text']); ?></div>
			</div>
		<?php }

	}