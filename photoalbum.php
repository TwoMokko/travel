<?php

require 'templates/top.tpl';
require 'templates/footer.tpl';
require 'templates/main.tpl';

function Title(): string {
	return 'Ак-туру';
}

function Head(): void {
	?><div class = "block hat other">
	<div class = "photoalbum_hat"></div>
	<?php Top(); ?>
	<div>
		<div>Ак-туру</div>
		<div>Возможно, текст</div>
	</div>
	</div><?php
}


function Main(): void {
	?><div class = "block page_photo_album p">
		<div></div>
		<div class = "photo_album">
			<div></div>
			<div></div>
			<div></div>
			<div></div>
			<div></div>
			<div></div>
			<div></div>
			<div></div>
			<div></div>
			<div></div>
			<div></div>
			<div></div>
			<div></div>
			<div></div>
			<div></div>
			<div></div>
			<div></div>
			<div></div>
		</div>
	</div>
    <script>
        $(() => ScrollTop('main'));
    </script>
    <?php
}