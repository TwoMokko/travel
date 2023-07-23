<?php

	namespace Base\Editor\MySQLi;

	require DIR_BASE . 'editor/editor.inc';
	require DIR_BASE . 'editor/MySQLi/editor.model.inc';

	abstract class Editor extends \Base\Editor\Editor {

		public function __construct(string $name) {
			parent::__construct($name);
		}

	}