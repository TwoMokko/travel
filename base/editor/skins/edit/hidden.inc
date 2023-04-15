<?php

	namespace Base\Editor\Skins\Edit;

	class Hidden extends Input {

		public function __construct(string $name, string $title, string $default = '') {
			parent::__construct($name, $title, 'hidden', $default);
		}

	}