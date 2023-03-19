<?php

	namespace Proj\Site\Templates\Photo;

	use Base\Templates\View;
	use Proj\Site\Units\Photo;
	use Proj\Units\Consts;

	class ForTour extends View {

		public function ToVar(array $items, $photo_id): string {
			$this->Start();
			$this->Render($items, $photo_id);
			return $this->Read();
		}

		public function Render($items, $photo_id) { ?>
			<div class = "tour_photo block p">
				<div class = "header">Фотографии</div>
				<div class = "block tour_mini_photo">
					<?php foreach ($items as $item) { ?>
						<div data-id = "gallery_1" data-url = "<?= Consts\Photo::PATH_SHOW_RELATIVE . $item['image']; ?>" style = "background-image: url('<?= Consts\Photo::PATH_SHOW_RELATIVE . $item['image']; ?>');" onclick = "new Gallery(this);"></div>
					<?php } ?>
				</div>
				<div>
					<?= Photo::instance()->show->GetLink('Смотреть альбом', ['id' => $photo_id], ['class' => 'button']); ?>
				</div>
			</div>
			<div>

			</div>
		<?php }

	}