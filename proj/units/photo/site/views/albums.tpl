<?php

	namespace Proj\Site\Templates\Photo;

	use Base\Templates\Buffering;
	use Proj\Units\Consts;
	use Proj\Site\Actions;

	abstract class Albums {

		public static function ToVar(array $items): string {
			Buffering::Start();
			self::Render($items);
			return Buffering::Read();
		}

		public static function Render($items): void { ?>
			<div class = "block page_photo p">
				<div></div>
				<div class = "photo_albums">
					<?php foreach ($items as $item) echo Actions\Pages::$album->GetLinkHref(self::ItemToVar($item), ['id' => $item['id']], ['style' => 'background-image: url(' . Consts\Photo::PATH_ALL_PREVIEW_RELATIVE . $item['image'] . ');']); ?>
				</div>
			</div>
		<?php }

		private static function Item($data): void { ?>
			<div><?= $data['header']; ?></div>
		<?php }

		public static function ItemToVar(array $item): string {
			Buffering::Start();
			self::Item($item);
			return Buffering::Read();
		}

	}