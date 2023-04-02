<?php

	namespace Proj\Units\Consts;

	interface Story {
		const ID						= ID_STORY;
		const NAME						= 'story';

		const TABLES = [
			'story'						=> self::NAME
		];

		const STATE_ERROR				= 0;
		const STATE_DRAFT				= 1;
		const STATE_ACTIVE				= 3;
		const STATE_INACTIVE			= 4;
		const STATE_DELETE				= 100;

		const STATES = [
			'error'						=> self::STATE_ERROR,
			'draft'						=> self::STATE_DRAFT,
			'active'					=> self::STATE_ACTIVE,
			'inactive'					=> self::STATE_INACTIVE,
			'delete'					=> self::STATE_DELETE
		];

		const STATES_RU = [
			self::STATE_ERROR			=> 'Ошибка',
			self::STATE_DRAFT			=> 'Черновик',
			self::STATE_ACTIVE			=> 'Активная',
			self::STATE_INACTIVE		=> 'Не активная',
			self::STATE_DELETE			=> 'Удалена'
		];

		const PATH_COVER				= DIR_RESOURCE_IMAGE . 'story/';
		const PATH_COVER_RELATIVE		= '/proj/resource/image/story/';
	}