<?php

	namespace Proj\Site\Templates\Photo;

	use Base\Templates\Template;
	use Proj\Units\Consts;

	abstract class Show {

		public static function ToVar(array $data): string {
			Template::Start();
			self::Render($data);
			return Template::Read();
		}

		public static function Render($data): void { ?>
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