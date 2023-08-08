<?php

	namespace Proj\Templates\Site\Versions {

        use Base\VersionsControl;

        define("Proj\Templates\Site\Versions\COMMON_JS", VersionsControl::instance()->Get('site', 'COMMON_JS'));

        define("Proj\Templates\Site\Versions\MAIN_CSS", VersionsControl::instance()->Get('site', 'MAIN_CSS'));
	}