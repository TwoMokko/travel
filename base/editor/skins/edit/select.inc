<?php

	namespace Base\Editor\Skins\Edit;

	use Base\Editor\Skins\SkinEdit;
	use Base\Templates\Template;

	class Select extends SkinEdit {
		private array $data;

		public function __construct(string $name, string $title, array $data = []) {
			parent::__construct('select', $name, $title);

			$this->data = $data;
		}

		public function ToVar(string $value = ''): string {
			Template::Start();
			$this->Render($value);
			return Template::Read();
		}

		public function Render(string $value): void { ?>
			<select name = "<?= $this->name; ?>">
				<?php foreach ($this->data as $value => $text) { ?>
					<option value = "<?= $value; ?>"><?= $text; ?></option>
				<?php } ?>
			</select>
		<?php }

	}