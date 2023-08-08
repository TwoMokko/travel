<?php

	namespace Base\Templates\Versions {

        use Base\VersionsControl;

        define("Base\Templates\Versions\COMMON_JS", VersionsControl::instance()->Get('base', 'COMMON_JS'));
        define("Base\Templates\Versions\FUNCTION_JS", VersionsControl::instance()->Get('base', 'FUNCTION_JS'));
        define("Base\Templates\Versions\SKINS_JS", VersionsControl::instance()->Get('base', 'SKINS_JS'));
	}