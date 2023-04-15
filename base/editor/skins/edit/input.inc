<?php

    namespace Base\Editor\Skins\Edit;

    use Base\Editor\Skins\SkinEdit;
    use Base\Templates\Template;

    class Input extends SkinEdit {

        public function __construct(string $name, string $title, string $type, string $default = '') {
			parent::__construct($type, $name, $title, $default);
        }

        public function ToVar(?string $value = null): string {
            Template::Start();
            $this->Render($value ?? $this->default);
            return Template::Read();
        }

        public function Render(string $value): void { ?>
            <input type = "<?= $this->type; ?>" name = "<?= $this->name; ?>" value = "<?= $value; ?>">
        <?php }

    }