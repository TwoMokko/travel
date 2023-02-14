<?php

    namespace Proj\Site\Templates\Reviews;

    use Base\Templates\View;
	use Proj\Site\Units;
    use Proj\Units\Consts;

	class Lists extends View {

		public function ToVarCarousel(array $items): string {
			$this->Start();
			$this->Carousel($items);
			return $this->Read();
		}

		public function ToVarGrid(array $items): string {
			$this->Start();
			$this->Grid($items);
			return $this->Read();
		}

        public function Carousel($items) { ?>
            <div class = "block p reviews">
                <div>
                    <div class = "header" onclick = "window.location.href = '<?= Units\Reviews::instance()->for_list->GetPath(); ?>';">Отзывы</div>
                    <span title = "оставить отзыв"></span>
                </div>
                <div>
                    <div class = "arrow_left"></div>
                    <div class = "review_cards">
                        <?php foreach ($items as $item) $this->Item($item); ?>
                    </div>
                    <div class = "arrow_right"></div>
                </div>
            </div>
        <?php }

        public function Grid($items) { ?>
            <div class = "block p page_reviews">
                <div class = "review_cards">

                </div>
            </div>
        <?php }

        private function Item($data) { ?>
            <div class = "review_card" onclick = "GetReview('<?= Units\Reviews::instance()->get->GetPath(); ?>', <?= $data['id']; ?>);">
                <div class = "review_person">
                    <div style = "background-image: url(<?= Consts\Reviews::PATH_AVATAR_RELATIVE, $data['image']; ?>);"></div>
                    <div><?= $data['name']; ?></div>
                </div>
                <div class = "review_text"><?= $data['text']; ?></div>
            </div>
        <?php }

    }