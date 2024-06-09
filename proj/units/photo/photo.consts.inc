<?php

namespace Proj\Units\Consts;

interface Photo {
	const ID							= ID_PHOTO;
	const NAME							= 'photo';
	const TITLE                         = 'Фотоальбомы';

	const TABLES = [
		'photo_all'						=> self::NAME. '_all',
		'photo_show'					=> self::NAME . '_show'
	];

	const STATE_ERROR					= 0;
	const STATE_DRAFT					= 1;
	const STATE_ACTIVE					= 3;
	const STATE_INACTIVE				= 4;
	const STATE_DELETE					= 100;

	const STATES = [
		'error'							=> self::STATE_ERROR,
		'draft'							=> self::STATE_DRAFT,
		'active'						=> self::STATE_ACTIVE,
		'inactive'						=> self::STATE_INACTIVE,
		'delete'						=> self::STATE_DELETE
	];

	const STATES_RU = [
		self::STATE_ERROR				=> 'Ошибка',
		self::STATE_DRAFT				=> 'Черновик',
		self::STATE_ACTIVE				=> 'Активная',
		self::STATE_INACTIVE			=> 'Не активная',
		self::STATE_DELETE				=> 'Удалена'
	];

	const PATH_COVER					= DIR_RESOURCE_IMAGE . 'photo/all/';
	const PATH_ALL_ORIGINAL				= DIR_RESOURCE_IMAGE . 'photo/all/original/';
	const PATH_ALL_ORIGINAL_RELATIVE	= '/proj/resource/image/photo/all/original/';
	const PATH_ALL_PREVIEW				= DIR_RESOURCE_IMAGE . 'photo/all/preview/';
	const PATH_ALL_PREVIEW_RELATIVE		= '/proj/resource/image/photo/all/preview/';
	const PATH_SHOW_ORIGINAL			= DIR_RESOURCE_IMAGE . 'photo/show/original/';
	const PATH_SHOW_PREVIEW				= DIR_RESOURCE_IMAGE . 'photo/show/preview/';
	const PATH_SHOW_RELATIVE_ORIGINAL	= '/proj/resource/image/photo/show/original/';
	const PATH_SHOW_RELATIVE_PREVIEW	= '/proj/resource/image/photo/show/preview/';
}