<?php

	namespace Proj\Site\Templates\Stories;

	use Base\Templates\View;

	class Show extends View {

		public function ToVar(array $data): string {
			$this->Start();
			$this->Render($data);
			return $this->Read();
		}

		public function Render($data) { ?>
            <div class = "block p page_one_adventure">
                <div class = "adventure_text">
                    <div><?= $data['text']; ?></div>
                    <div>
                        <div data-id = "1" data-url = "css/pic/photoalbum/22.jpg" style = "background-image: url('proj/templates/site/css/pic/photoalbum/22.jpg');" onclick = "new Gallery(this);"></div>
                        <div data-id = "1" data-url = "css/pic/photoalbum/18.jpg" style = "background-image: url('proj/templates/site/css/pic/photoalbum/18.jpg');" onclick = "new Gallery(this);"></div>
                    </div>
                </div>
                <div>Другие</div>
            </div>
		<?php }

	}