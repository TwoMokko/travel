<?php

	namespace Proj\Site\Templates;

	use Base\Templates\View;

	class Template extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render() { ?><!doctype html>
			<html lang  = "ru">
				<head>
					<meta charset = "UTF-8">
					<meta name = "viewport" content = "width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
					<meta http-equiv = "X-UA-Compatible" content = "ie=edge">
					<title>I Da Travel</title>
					<?php
						Layout::BrowseScripts();
						Layout::BrowseStylesheets();
					?>
				</head>
				<body>
					<?php $this->RenderSections(); ?>
					<script>
						$(function() {
							Base.Common.GlobalParams.Set('request', '<?= \REQUEST; ?>');
							// Site.Common.Layout.Initialization();
						});
					</script>
				</body>
			</html>
		<?php }

		public function RenderSections() { ?>
			<header><?php Layout::instance()->header->Browse(); ?></header>
			<main><?php Layout::instance()->main->Browse(); ?></main>
			<footer><?php Layout::instance()->footer->Browse(); ?></footer>
		<?php }

	}