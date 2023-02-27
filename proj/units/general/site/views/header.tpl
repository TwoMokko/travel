<?php

	namespace Proj\Site\Templates\General;

	use Base\Templates\View;

	class Header extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render() { ?>
			<div class = "block top">
				<div><a href = "/"></a></div>
				<?php $this->Menu(); ?>
				<div class = "open_menu" onclick = "new Menu();"></div>

			</div>
		<?php }

		private function Menu(): void { ?>
			<div class = "block menu">
				<div><a href = "/">Главная</a></div>
				<div><a href = "/tours">Путешествия</a></div>
				<div><a href = "/about">О нас</a></div>
				<div><a href = "/stories">Наши приключения</a></div>
				<div><a href = "/photo">Фотографии</a></div>
			</div>
		<?php }

	}