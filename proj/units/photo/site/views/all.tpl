<?php

	namespace Proj\Site\Templates\Photo;

	use Base\Templates\View;
	use Proj\Site\Units\Photo;
	use Proj\Units\Consts;

	class All extends View {

		public function ToVar(array $items): string {
			$this->Start();
			$this->Render($items);
			return $this->Read();
		}

		public function Render($items) { ?>
			<div class = "block page_photo p">
				<div></div>
				<div class = "photo_albums">
					<?php foreach ($items as $item) echo Photo::instance()->show->GetLink($this->ItemToVar($item), ['id' => $item['id']], ['style' => 'background-image: url(' . Consts\Photo::PATH_ALL_RELATIVE . $item['image'] . ');']); ?>
				</div>
			</div>
		<?php }

		private function Item($data) { ?>
			<div><?= $data['header']; ?></div>
		<?php }

		public function ItemToVar(array $item): string {
			$this->Start();
			$this->Item($item);
			return $this->Read();
		}

	}