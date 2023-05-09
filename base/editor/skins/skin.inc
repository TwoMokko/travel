<?php

	namespace Base\Editor\Skins;

	abstract class Skin {
        protected string $title;

		public function __construct($title) {
            $this->title = $title;
        }

		abstract public function ToVar(mixed $value): string;

        public function GetTitle(): string { return $this->title; }

	}

    require DIR_BASE . 'editor/skins/browse/skinBrowse.inc';
    require DIR_BASE . 'editor/skins/edit/skinEdit.inc';