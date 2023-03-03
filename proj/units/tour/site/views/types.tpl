<?php

	namespace Proj\Site\Templates\Tour;

	use Base\Templates\View;
	use Proj\Units\Consts;

	class Types extends View {

		public function ToVar(array $items): string {
			$this->Start();
			$this->Render($items);
			return $this->Read();
		}

		public function Render($items) { ?>
			<div class = "block tours p">
				<div>
					<div class = "header">Типы путешествий</div>
					<div class = "switch_menu">
						<?php foreach ($items as $item) { ?>
							<div><?= $item['name']; ?></div>
						<?php } ?>
					</div>
					<div class = "switch_list">
						<?php foreach ($items as $item) $this->Item($item); ?>
					</div>
				</div>
			</div>
			<script>
				$(() => Switcher('.switch_menu', '.switch_list'));
			</script>
		<?php }

		private function Item($data) { ?>
			<div>
				<div style = "background-image: url(<?= Consts\Tour::PATH_TYPE_RELATIVE, $data['image']; ?>);"></div>
				<div>
					<div><?= $data['name']; ?></div>
					<div><?= $data['description']; ?></div>
					<div>
						<a class = "button" href = "/tours#major_travel">Выбрать путешествие</a>
						<!--							<input type = "button" value = "Выбрать путешествие" onclick = " window.location.href = '/tours';">-->
					</div>
				</div>
			</div>
		<?php }

	}