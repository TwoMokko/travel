<?php

	namespace Proj\Units\Consts;

	interface Stories {
		const ID						= ID_STORIES;
		const NAME						= 'stories';

		const TABLES = [
			'stories'					=> self::NAME
		];

		const STATE_ERROR				= 0;
		const STATE_NEW 				= 1;
		const STATE_DONE				= 2;
		const STATE_ACTIVE				= 3;
		const STATE_INACTIVE			= 4;
		const STATE_DELETE				= 100;

		const STATES = [
			'error'						=> self::STATE_ERROR,
			'new'						=> self::STATE_NEW,
			'done'					    => self::STATE_DONE,
			'active'					=> self::STATE_ACTIVE,
			'inactive'					=> self::STATE_INACTIVE,
			'delete'					=> self::STATE_DELETE
		];

		const PATH_AVATAR				= DIR_RESOURCE_IMAGE . 'stories/';
		const PATH_AVATAR_RELATIVE		= '/proj/resource/image/stories/';
	}