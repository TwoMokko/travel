<?php

	namespace Base\Helper\Data;

	abstract class Prepare {

		static function Trim(string $value): string {
			return trim($value);
		}

	}