<?php

    namespace Base\Editor\Skins\Edit;

    use Base\Editor\Skins\SkinEdit;
    use Base\Templates\Template;

    class Table extends SkinEdit {
        private string $name;
        private array $column;

        public function __construct(string $title, string $name, array $column = []) {
            parent::__construct($title);

            $this->name = $name;
            $this->column = $column;
        }

        public function ToVar(mixed $value = []): string {
            Template::Start();
            $uid = uniqid('skin_table_');
        ?>
            <div id = "<?= $uid; ?>"></div>
            <script> new Base.Skins.Table('#<?= $uid; ?>', '<?= $this->name; ?>', <?= json_encode($this->column); ?>, <?= json_encode($value); ?>); </script>
        <?php
            return Template::Read();
        }

    }