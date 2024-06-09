<?php

    namespace Proj\Units\Consts;

    interface Travel {
        const ID								= ID_TRAVEL;
        const NAME								= 'travel';
		const TITLE                             = 'Путешествие';

        const TABLES = [
            'tours'                      		=> self::NAME . '_tours',
            'directions'                     	=> self::NAME . '_directions',
            'types'                      		=> self::NAME . '_types',
            'programs'                   		=> self::NAME . '_tour_programs',
            'expenses'                   		=> self::NAME . '_tour_expenses',
            'additional_expenses'        		=> self::NAME . '_tour_additional_expenses'
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

        const PATH_TOUR_ORIGINAL				= DIR_RESOURCE_IMAGE . 'travel/tour/original/';
        const PATH_TOUR_ORIGINAL_RELATIVE		= '/proj/resource/image/travel/tour/original/';
        const PATH_TOUR_PREVIEW				    = DIR_RESOURCE_IMAGE . 'travel/tour/preview/';
        const PATH_TOUR_PREVIEW_RELATIVE		= '/proj/resource/image/travel/tour/preview/';
        const PATH_TYPE_ORIGINAL				= DIR_RESOURCE_IMAGE . 'travel/type/original/';
        const PATH_TYPE_ORIGINAL_RELATIVE		= '/proj/resource/image/travel/type/original/';
        const PATH_TYPE_PREVIEW					= DIR_RESOURCE_IMAGE . 'travel/type/preview/';
        const PATH_TYPE_PREVIEW_RELATIVE		= '/proj/resource/image/travel/type/preview/';
    }