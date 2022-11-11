<?php

	require 'templates/top.tpl';
	require 'templates/footer.tpl';
	require 'templates/main.tpl';

	function Title(): string {
		return 'Одна история';
	}

	function Head(): void {
		?><div class = "block hat other">
		<div class = "one_adventure_hat"></div>
		<?php Top(); ?>
		<div>
			<div>Одна история</div>
	<!--		<div>Возможно, текст</div>-->
		</div>
		</div><?php
	}

	function Main(): void {
		?><div class = "block p page_one_adventure">
			<div></div>
		</div><?php
	}
