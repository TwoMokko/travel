<?php

    namespace Base\Editor\Skins\Edit;

    use Base\Editor\Skins\SkinEditHTMLElement;
    use Base\Templates\Template;

    class Input extends SkinEditHTMLElement {
        protected string $type;

        public function __construct(string $title, string $name, string $type, string $default = '') {
			parent::__construct($title, $name, $default);

            $this->type = $type;
        }

        public function ToVar(mixed $value = null): string {
            Template::Start();
            $this->Render($value ?? $this->default);
            return Template::Read();
        }

        public function Render(string $value): void { ?>
            <input type = "<?= $this->type; ?>" name = "<?= $this->name; ?>" value = "<?= $value; ?>">
        <?php }

    }