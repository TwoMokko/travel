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

		const AVATARS = [
			1 => '/proj/resource/image/review/1.png',
			2 => '/proj/resource/image/review/2.png',
			3 => '/proj/resource/image/review/3.png',
			4 => '/proj/resource/image/review/4.png',
			5 => '/proj/resource/image/review/5.png'
		];

		const PATH_AVATAR				= DIR_RESOURCE_IMAGE . 'review/';
		const PATH_AVATAR_RELATIVE		= '/proj/resource/image/review/';
    }