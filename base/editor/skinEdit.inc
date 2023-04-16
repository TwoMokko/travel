<?php

	namespace Base\Editor\Skins;

	abstract class SkinEdit {
		protected string $type;
		protected string $name;
		protected string $title;
		protected ?string $default;

		public function __construct(string $type, string $name, string $title, string $default = '') {
			$this->type = $type;
			$this->name = $name;
			$this->title = $title;
			$this->default = $default;
		}

		abstract public function ToVar(string $value): string;

		public function GetTitle(): string { return $this->title; }
		public function GetType(): string { return $this->type; }

	}

	require DIR_BASE . 'editor/skins/edit/input.inc';
	require DIR_BASE . 'editor/skins/edit/text.inc';
	require DIR_BASE . 'editor/skins/edit/hidden.inc';
	require DIR_BASE . 'editor/skins/edit/file.inc';
	require DIR_BASE . 'editor/skins/edit/select.inc';
	require DIR_BASE . 'editor/skins/edit/uploader.inc';