<?php

	function MoneyFormat(float $number): string {
		return number_format($number, 0, '.', ' ');
	}