<?php

	namespace Base\DB\MySQLi;

	class FieldInt16 extends Field {
		protected int $size = 6;

		public function __construct(string $name, Table $table) {
			parent::__construct('int16', $name, $table);

			$this->_type = ['smallint', "smallint({$this->size})"];
			$this->_null = 'NO';
			$this->_key = '';
			$this->_default = '0';
			$this->_extra = [''];
		}

		private function GetFormat(): string { return "`{$this->name}` smallint NOT NULL DEFAULT '0'"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}