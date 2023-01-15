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
			<div class = "photo_line1">
				<div data-id = "1" data-url = "css/pic/photoalbum/2.jpg" style = "background-image: url('css/pic/photoalbum/2.jpg');" onclick = "ShowGallery();"></div>
				<div data-id = "1" data-url = "css/pic/photoalbum/8.jpg" style = "background-image: url('css/pic/photoalbum/8.jpg');" onclick = "ShowGallery();"></div>
				<div data-id = "1" data-url = "css/pic/photoalbum/4.jpg" style = "background-image: url('css/pic/photoalbum/4.jpg');" onclick = "ShowGallery();"></div>
			</div>
			<div class = "photo_line2">
				<div data-id = "1" data-url = "css/pic/photoalbum/5.jpg" style = "background-image: url('css/pic/photoalbum/5.jpg');" onclick = "ShowGallery();"></div>
				<div data-id = "1" data-url = "css/pic/photoalbum/6.jpg" style = "background-image: url('css/pic/photoalbum/6.jpg');" onclick = "ShowGallery();"></div>
				<div data-id = "1" data-url = "css/pic/photoalbum/3.jpg" style = "background-image: url('css/pic/photoalbum/3.jpg');" onclick = "ShowGallery();"></div>
			</div>
			<div class = "photo_line3">
				<div></div>
				<div></div>
				<div></div>
			</div>
			<div class = "photo_line1">
				<div></div>
				<div></div>
				<div></div>
			</div>
			<div class = "photo_line2">
				<div></div>
				<div></div>
				<div></div>
			</div>
			<div class = "photo_line3">
				<div></div>
				<div></div>
				<div></div>
			</div>
		</div>
	</div>
    <script>
        $(() => ScrollTop('main'));
    </script>
    <?php
}