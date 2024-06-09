<?php

	namespace Base\Helper\Data;

	abstract class Validation {

		static function Required(string $value): bool {
			return ($value !== '');
		}

	}