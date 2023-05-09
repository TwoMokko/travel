<?php

    namespace Base\Editor\Skins\Edit;

    use Base\Editor\Skins\SkinEditHTMLElement;
    use Base\Templates\Template;

    class TextArea extends SkinEditHTMLElement {

        public function __construct(string $title, string $name, string $default = '') {
            parent::__construct($title, $name, $default);
        }

        public function ToVar(mixed $value = null): string {
            Template::Start();
            $this->Render($value ?? $this->default);
            return Template::Read();
        }

        public function Render(string $value): void { ?>
            <textarea name = "<?= $this->name; ?>"><?= $value; ?></textarea>
        <?php }

    }