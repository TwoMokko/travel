<?php

	namespace Proj\Site\Templates\Travel;

	use Base\Templates\Buffering;
	use Proj\Units\Consts;

	abstract class Types {

		public static function ToVar(array $items): string {
			Buffering::Start();
			self::Render($items);
			return Buffering::Read();
		}

		public static function Render($items): void { ?>
			<div class = "block tours p">
				<div>
					<div class = "header">Виды путешествий</div>
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
				<div style = "background-image: url(<?= Consts\Travel::PATH_TYPE_PREVIEW_RELATIVE, $data['image']; ?>);"></div>
				<div>
					<div><?= $data['name']; ?></div>
					<div><?= $data['description']; ?></div>
					<div>
						<a class = "button" href = "/tours#type_<?= $data['id']; ?>">Выбрать путешествие</a>
					</div>
				</div>
			</div>
		<?php }

	}