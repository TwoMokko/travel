<?php

	namespace Proj\Site\Templates\Photo;

	use Base\Templates\Template;
	use Proj\Site\Units\Photo;
	use Proj\Units\Consts;

	abstract class All {

		public static function ToVar(array $items): string {
			Template::Start();
			self::Render($items);
			return Template::Read();
		}

		public static function Render($items): void { ?>
			<div class = "block page_photo p">
				<div></div>
				<div class = "photo_albums">
					<?php foreach ($items as $item) echo Photo::instance()->show->GetLink(self::ItemToVar($item), ['id' => $item['id']], ['style' => 'background-image: url(' . Consts\Photo::PATH_ALL_RELATIVE . $item['image'] . ');']); ?>
				</div>
			</div>
		<?php }

		private static function Item($data): void { ?>
			<div><?= $data['header']; ?></div>
		<?php }

		public static function ItemToVar(array $item): string {
			Template::Start();
			self::Item($item);
			return Template::Read();
		}

	}