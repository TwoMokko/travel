<?php

namespace Base\Editor\Skins\Edit;

use Base\Editor\Skins\SkinEdit;
use Base\Templates\Template;

class TextArea extends SkinEdit {

    public function __construct(string $name, string $title, string $default = '') {
        parent::__construct('textarea', $name, $title, $default);
    }

    public function ToVar(?string $value = null): string {
        Template::Start();
        $this->Render($value ?? $this->default);
        return Template::Read();
    }

    public function Render(string $value): void { ?>
        <textarea name = "<?= $this->name; ?>"><?= $value; ?></textarea>
    <?php }

}