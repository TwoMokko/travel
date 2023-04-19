<?php

	namespace Base\Editor\Skins\Edit;

	class Uploader extends Input {
		private string  $value;
		private string  $accept;
		private string  $path_load;
		private string  $path_del;
		private string  $path_view;
		private array   $photos;

		public function __construct(string $name, string $title, string $path_load, string $path_del, string $path_view, string $value = 'Выберите', string $accept = '', array $photos = []) {
			parent::__construct($name, $title, 'file');

			$this->value = $value;
			$this->accept = $accept;
			$this->path_load = $path_load;
			$this->path_del = $path_del;
			$this->path_view = $path_view;
			$this->photos = $photos;
		}

		public function Render(string $value): void {
			$accept = $this->accept ? ' accept = "' . $this->accept . '"' : '';
            $uid = uniqid('uploader_');
		?>
            <input id = "<?= $uid; ?>" type = "<?= $this->type; ?>" name = "<?= $this->name; ?>" <?= $accept; ?> multiple>
            <script>
                new Functions.UploaderPhoto('#<?= $uid; ?>', 'Нажмите для загрузки или перетащите сюда', '<?= $this->path_load; ?>', '<?= $this->path_del; ?>', '<?= $this->path_view; ?>', <?= json_encode($this->photos); ?>);
            </script>
		<?php }

	}