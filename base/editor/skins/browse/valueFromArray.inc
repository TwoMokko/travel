<?php

	namespace Base\Editor\Skins\Browse;

    use Base\Editor\Skins\Skin;

	class ValueFromArray extends Skin {
		private array $array;

		public function __construct(string $name, array $array) {
			parent::__construct($name);

			$this->array = $array;
		}

		public function ToVar(string $value) : string {
			return $this->array[$value] ?? '';
		}

	}