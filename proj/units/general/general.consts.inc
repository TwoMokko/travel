<?php

	namespace Proj\Units\Consts;

	interface General {
		const ID						= ID_GENERAL;
		const NAME						= 'general';
		const TITLE						= 'Основное';

		const ACCESS_SETTING			= 1;
		const ACCESS_DB_CHECK			= 8;
		const ACCESS_DB_MAKE			= 9;
		const ACCESS_DB_STRUCTURE		= 10;

		const TEXT_ERROR_ACCESS			= 'Ошибка доступа. Недостаточно прав.';

		const TABLES = [
			'text'				        => self::NAME . '_text',
			'image'				        => self::NAME . '_image'
		];

		const STATE_ERROR				= 0;
		const STATE_ACTIVE				= 3;
		const STATE_DELETE				= 100;

		const STATES = [
			'error'						=> self::STATE_ERROR,
			'active'					=> self::STATE_ACTIVE,
			'delete'					=> self::STATE_DELETE
		];

		const STATES_RU = [
			self::STATE_ERROR			=> 'Ошибка',
			self::STATE_ACTIVE			=> 'Активная',
			self::STATE_DELETE			=> 'Удалена'
		];

		const PATH_IMAGE				= DIR_RESOURCE_IMAGE . 'general/';
		const PATH_IMAGE_RELATIVE		= DIR_REL_RESOURCE_IMAGE . 'general/';
	}