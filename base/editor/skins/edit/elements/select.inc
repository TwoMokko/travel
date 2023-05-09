<?php

	namespace Base\Editor\Skins\Edit;

    use Base\Editor\Skins\SkinEditHTMLElement;
    use Base\Templates\Template;

	class Select extends SkinEditHTMLElement {
		private array $data;

		public function __construct(string $title, string $name, array $data = []) {
			parent::__construct($title, $name);

			$this->data = $data;
		}

		public function ToVar(mixed $value = ''): string {
			Template::Start();
			$this->Render($value);
			return Template::Read();
		}

		public function Render(string $value): void { ?>
			<select name = "<?= $this->name; ?>">
				<?php foreach ($this->data as $key => $text) {
                    $selected = ($value == $key) ? ' selected' : '';
                ?>
					<option value = "<?= $key; ?>"<?= $selected; ?>><?= $text; ?></option>
				<?php } ?>
			</select>
		<?php }

	}