<?php

    namespace Proj\Units\Consts;

    interface Reviews {
        const ID						= ID_REVIEWS;
        const NAME						= 'review';

		const TABLES = [
			'review'					=> self::NAME
		];


        const STATE_ERROR				= 0;
        const STATE_VERIFIED			= 1;
        const STATE_UNVERIFIED			= 2;

        const STATES = [
            'error'						=> self::STATE_ERROR,
            'verified'					=> self::STATE_VERIFIED,
            'unverified'				=> self::STATE_UNVERIFIED,
        ];

        const STATES_RU = [
            self::STATE_ERROR			=> 'Ошибка',
            self::STATE_VERIFIED		=> 'Опубликовано',
            self::STATE_UNVERIFIED		=> 'Не опубликовано'
        ];

		const PATH_AVATAR				= DIR_RESOURCE_IMAGE . 'review/';
		const PATH_AVATAR_RELATIVE		= '/proj/resource/image/review/';
    }