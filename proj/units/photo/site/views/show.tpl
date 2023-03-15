<?php

	namespace Proj\Site\Templates\Photo;

	use Base\Templates\View;
	use Proj\Units\Consts;

	class Show extends View {

		public function ToVar(array $data): string {
			$this->Start();
			$this->Render($data);
			return $this->Read();
		}

		public function Render($data) { ?>
			<div class = "block page_photo_album p">
				<div></div>
				<div class = "photo_album">
					<?php foreach ($data as $item) { ?>
						<div data-id = "gallery_1" data-url = "<?= Consts\Photo::PATH_SHOW_RELATIVE . $item['image']; ?>" style = "background-image: url('<?= Consts\Photo::PATH_SHOW_RELATIVE . $item['image']; ?>');" onclick = "new Gallery(this);"></div>
					<?php } ?>
				</div>
			</div>
		<?php }

	}