<?php

	namespace Proj\Site\Templates;

	use Base\Templates;
	use Base\Instance;
	use Base\Templates\Versions as BaseVersions;
	use Proj\Templates\Site\Versions as SiteVersions;

	class Template extends Templates\Template {
		use Instance;

		private function __construct() {
			parent::__construct();

			$this->AddScript('jq', 'https://code.jquery.com/jquery-3.6.1.min.js');
			$this->AddVersionScript('base_common', '/base/template/js/common', BaseVersions\COMMON_JS);
			$this->AddVersionScript('base_function', '/base/template/js/function', BaseVersions\FUNCTION_JS);
			$this->AddVersionScript('site_common', '/proj/templates/site/js/common', SiteVersions\COMMON_JS);

			$this->AddVersionStylesheet('main', DIR_REL_TPL . 'site/css/main', SiteVersions\MAIN_CSS);
		}

		public static function ToVar(): string {
			Templates\Template::Start();
			self::Render();
			return Templates\Template::Read();
		}

		public static function Render(): void { ?><!doctype html>
			<html lang  = "ru"<?php Template::instance()->BrowseData(); ?>>
				<head>
					<meta charset = "UTF-8">
					<meta name = "viewport" content = "width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
					<meta http-equiv = "X-UA-Compatible" content = "ie=edge">
					<?php
						Template::instance()->BrowseHead();
					?>
				</head>
				<body>
					<?php self::RenderSections(); ?>
					<script>
						$(function() {
							Base.Common.GlobalParams.Set('request', '<?= \REQUEST; ?>');
							// Site.Common.Layout.Initialization();
						});
					</script>
				</body>
			</html>
		<?php }

		private static function RenderSections(): void { ?>
			<header><?php Layout::instance()->header->Browse(); ?></header>
			<main><?php Layout::instance()->main->Browse(); ?></main>
			<footer><?php Layout::instance()->footer->Browse(); ?></footer>
		<?php }

	}

	Template::init();