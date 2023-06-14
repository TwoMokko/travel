<?php

    namespace Proj\Units\Consts;

    interface Tour {
        const ID						= ID_TOURS;
        const NAME						= 'tour';

        const TABLES = [
            'tour'                      => self::NAME,
            'group'                     => self::NAME . '_group',
            'type'                      => self::NAME . '_type',
            'program'                   => self::NAME . '_program',
            'expense'                   => self::NAME . '_expense',
            'additional_expense'        => self::NAME . '_additional_expense'
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

        const PATH_TOUR				    = DIR_RESOURCE_IMAGE . 'tour/item/';
        const PATH_TOUR_RELATIVE		= '/proj/resource/image/tour/item/';
        const PATH_TYPE				    = DIR_RESOURCE_IMAGE . 'tour/type/';
        const PATH_TYPE_RELATIVE		= '/proj/resource/image/tour/type/';
    }