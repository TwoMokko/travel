<?php

	namespace Base\Editor\Skins\Edit;

	class Text extends Input {

		public function __construct(string $name, string $title) {
			parent::__construct($name, $title, 'text');
		}

	}