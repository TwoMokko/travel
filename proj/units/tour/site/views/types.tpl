<?php

	namespace Proj\Site\Templates\Tour;

	use Base\Templates\Template;
	use Proj\Units\Consts;

	abstract class Types {

		public static function ToVar(array $items): string {
			Template::Start();
			self::Render($items);
			return Template::Read();
		}

		public static function Render($items): void { ?>
			<div class = "block tours p">
				<div>
					<div class = "header">Типы путешествий</div>
					<div class = "switch_menu">
						<?php foreach ($items as $item) { ?>
							<div><?= $item['name']; ?></div>
						<?php } ?>
					</div>
					<div class = "switch_list">
						<?php foreach ($items as $item) self::Item($item); ?>
					</div>
				</div>
			</div>
			<script>
				$(() => Switcher('.switch_menu', '.switch_list'));
			</script>
		<?php }

		private static function Item($data): void { ?>
			<div>
				<div style = "background-image: url(<?= Consts\Tour::PATH_TYPE_PREVIEW_RELATIVE, $data['image']; ?>);"></div>
				<div>
					<div><?= $data['name']; ?></div>
					<div><?= $data['description']; ?></div>
					<div>
						<a class = "button" href = "/tours#<?= $data['alias']; ?>">Выбрать путешествие</a>
						<!--							<input type = "button" value = "Выбрать путешествие" onclick = " window.location.href = '/tours';">-->
					</div>
				</div>
			</div>
		<?php }

	}