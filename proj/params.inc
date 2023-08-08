<?php

    namespace Proj;

    class Params {

        static string $site_name = 'айдатревал.рф';
        static string $site_address;
    }

    Params::$site_address = $_SERVER['SERVER_NAME'];