<?php

	namespace Base\Editor;

	use Base\DB\MySQLi\Table;

	abstract class EditorMySQLi extends Editor {

		public function __construct(string $name, Table $table, array $params = []) {
			parent::__construct($name, $table, $params);
		}

	}