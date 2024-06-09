<?php

    namespace Base\Editor\Skins\Browse;

    use Base\Editor\Skins\SkinBrowse;
    use Base\Templates\Buffering;

    class Image extends SkinBrowse {
        private string $path;
        private string $width;
        private string $height;
        private string $bg_size;

        public function __construct(string $title, string $path, int $width = 200, int $height = 200, string $bg_size = 'contain') {
            parent::__construct($title);
            $this->path = $path;
            $this->width = $width;
            $this->height = $height;
            $this->bg_size = $bg_size;
        }

        public function ToVar(mixed $value) : string {
			Buffering::Start();
        ?>
            <div style = "background-image: url('<?= $this->path, $value; ?>'); width: <?= $this->width; ?>px; height: <?= $this->height; ?>px; background-size: <?= $this->bg_size; ?>; background-repeat: no-repeat; background-position: center; border: 1px solid #007fAD;"></div>
        <?php
            return Buffering::Read();
        }

    }