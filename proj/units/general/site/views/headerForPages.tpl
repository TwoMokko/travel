<?php

    namespace Proj\Site\Templates\General;

    use Base\Templates\View;

    class HeaderForPages extends View {

        public function ToVar(string $image, string $title, string $text = ''): string {
            $this->Start();
            $this->Render($image, $title, $text);
            return $this->Read();
        }

        public function Render(string $image, string $title, string $text = '') { ?>
            <div class = "block hat other">
                <div style = "background-image: url('<?= $image; ?>');"></div>
                <?php Header::object()->Render(); ?>
                <div>
                    <div><?= $title; ?></div>
                    <div><?= $text; ?></div>
                </div>
            </div>
        <?php }

    }