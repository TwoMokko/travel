<?php

	namespace Proj\Units\Consts;

	interface Story {
		const ID								= ID_STORY;
		const NAME								= 'story';
		const TITLE                             = 'Истории';

		const TABLES = [
			'story'								=> self::NAME
		];

		const STATE_ERROR						= 0;
		const STATE_DRAFT						= 1;
		const STATE_ACTIVE						= 3;
		const STATE_INACTIVE					= 4;
		const STATE_DELETE						= 100;

		const STATES = [
			'error'								=> self::STATE_ERROR,
			'draft'								=> self::STATE_DRAFT,
			'active'							=> self::STATE_ACTIVE,
			'inactive'							=> self::STATE_INACTIVE,
			'delete'							=> self::STATE_DELETE
		];

		const STATES_RU = [
			self::STATE_ERROR					=> 'Ошибка',
			self::STATE_DRAFT					=> 'Черновик',
			self::STATE_ACTIVE					=> 'Активная',
			self::STATE_INACTIVE				=> 'Не активная',
			self::STATE_DELETE					=> 'Удалена'
		];

		const PATH_COVER_ORIGINAL				= DIR_RESOURCE_IMAGE . 'story/original';
		const PATH_COVER_ORIGINAL_RELATIVE		= '/proj/resource/image/story/original/';
		const PATH_COVER_PREVIEW				= DIR_RESOURCE_IMAGE . 'story/preview';
		const PATH_COVER_PREVIEW_RELATIVE		= '/proj/resource/image/story/preview/';
	}