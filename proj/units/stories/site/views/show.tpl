<?php

	namespace Proj\Site\Templates\Stories;

	use Base\Templates\View;
    use Proj\Site\Units\Stories;

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
            </div>
		<?php }

        public function ToVarCarousel(array $items): string {
            $this->Start();
            $this->Carousel($items);
            return $this->Read();
        }

        public function Carousel($items) { ?>
            <div class = "other_publication block p">
                <div>
                    <span class = "header" onclick = " window.location.href = '/stories';">Другие приключения</span>
                </div>
                <div id = "carousel">
                    <?php foreach ($items as $item) echo Stories::instance()->show->GetLink($item['header'], ['id' => $item['id']], ['class' => 'other_public other_story']); ?>
                </div>
            </div>
            <script>
                $(() => new Carousel('#carousel', 4));
            </script>
        <?php }

	}