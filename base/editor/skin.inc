<?php

	namespace Base\Editor\Skins;

	abstract class Skin {
		protected string $name;

		public function __construct(string $name) {
			$this->name = $name;
		}

		abstract public function ToVar(string $value): string;

		public function GetName(): string { return $this->name; }

	}

    require DIR_BASE . 'editor/skins/browse/image.inc';
    require DIR_BASE . 'editor/skins/browse/int2IP.inc';
    require DIR_BASE . 'editor/skins/browse/text.inc';
    require DIR_BASE . 'editor/skins/browse/valueFromArray.inc';