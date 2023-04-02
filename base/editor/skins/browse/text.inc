<?php

    namespace Base\Editor\Skins\Browse;

    use Base\Editor\Skins\Skin;

    class Text extends Skin {

        public function __construct(string $name) {
            parent::__construct($name);
        }

        public function ToVar(string $value) : string {
            return nl2br(htmlspecialchars($value));
        }

    }