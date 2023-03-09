<?php

	namespace Proj\Site\Templates\Story;

	use Base\Templates\View;
    use Proj\Site\Units\Story;

    class All extends View {

		public function ToVar(array $items): string {
			$this->Start();
			$this->Render($items);
			return $this->Read();
		}

		public function Render($items) { ?>
			<div class = "block page_adventure p">
				<div class = "cards_adventure">
					<?php foreach ($items as $item) echo Story::instance()->show->GetLink($this->ItemToVar($item), ['id' => $item['id']]); ?>
				</div>
			</div>
		<?php }

		private function Item($data) { ?>
            <div></div>
            <div>
                <div><?= $data['header']; ?></div>
                <div><?= $data['text']; ?></div>
                <!--					<div>Читать дальше</div>-->
            </div>
		<?php }

        public function ItemToVar(array $item): string {
            $this->Start();
            $this->Item($item);
            return $this->Read();
        }

	}