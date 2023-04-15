<?php

	namespace Base\Editor\Skins\Edit;

	class Uploader extends Input {
		private string $value;
		private string $accept;

		public function __construct(string $name, string $title, string $value = 'Выберите', string $accept = '') {
			parent::__construct($name, $title, 'file');

			$this->value = $value;
			$this->accept = $accept;
		}

		public function Render(string $value): void {
			$accept = $this->accept ? ' accept = "' . $this->accept . '"' : '';
		?>
            <div>
                <div class = "upload">
                    <input type = "<?= $this->type; ?>" name = "<?= $this->name; ?>" value = "<?= $this->value; ?>"<?= $accept; ?>>
                </div>
                <div class = "img_container">
                    <div class = "img">
                        <div class = "delete"></div>
                    </div>
                </div>
            </div>
		<?php }

	}