<?php

	namespace Proj\Units\Consts;

	interface Feedback {
		const ID				= ID_FEEDBACK;
		const NAME				= 'feedback';

        const TABLES = [
            'feedback'						=> self::NAME
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
			self::STATE_VERIFIED		=> 'Проверено',
			self::STATE_UNVERIFIED		=> 'Не проверено'
		];
    }