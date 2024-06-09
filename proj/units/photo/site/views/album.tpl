<?php

	namespace Proj\Site\Templates\Photo;

	use Base\Templates\Buffering;
	use Proj\Units\Consts;

	abstract class Album {

		public static function ToVar(array $data): string {
			Buffering::Start();
			self::Render($data);
			return Buffering::Read();
		}

		public static function Render($data): void { ?>
			<div class = "block page_photo_album p">
				<div></div>
				<div class = "photo_album">
					<?php foreach ($data as $item) { ?>
						<div data-id = "gallery_1" data-url = "<?= Consts\Photo::PATH_SHOW_RELATIVE_ORIGINAL . $item['image']; ?>" style = "background-image: url('<?= Consts\Photo::PATH_SHOW_RELATIVE_PREVIEW . $item['image']; ?>');" onclick = "new Gallery(this);"></div>
					<?php } ?>
				</div>
			</div>
		<?php }

	}