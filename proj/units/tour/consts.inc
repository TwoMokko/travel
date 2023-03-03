<?php

    namespace Proj\Units\Consts;

    interface Tour {
        const ID						= ID_TOURS;
        const NAME						= 'tour';

        const TABLES = [
            'tour'                      => self::NAME,
            'type'                      => self::NAME . '_type'
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

        const PATH_TOUR				    = DIR_RESOURCE_IMAGE . 'tour/item/';
        const PATH_TOUR_RELATIVE		= '/proj/resource/image/tour/item/';
        const PATH_TYPE				    = DIR_RESOURCE_IMAGE . 'tour/type/';
        const PATH_TYPE_RELATIVE		= '/proj/resource/image/tour/type/';
    }