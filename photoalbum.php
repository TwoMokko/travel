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
			<div data-id = "1" data-url = "css/pic/photoalbum/2.jpg" style = "background-image: url('css/pic/photoalbum/2.jpg');" onclick = "new Gallery(this);"></div>
			<div data-id = "1" data-url = "css/pic/photoalbum/8.jpg" style = "background-image: url('css/pic/photoalbum/8.jpg');" onclick = "new Gallery(this);"></div>
			<div data-id = "1" data-url = "css/pic/photoalbum/4.jpg" style = "background-image: url('css/pic/photoalbum/4.jpg');" onclick = "new Gallery(this);"></div>
			<div data-id = "1" data-url = "css/pic/photoalbum/5.jpg" style = "background-image: url('css/pic/photoalbum/5.jpg');" onclick = "new Gallery(this);"></div>
			<div data-id = "1" data-url = "css/pic/photoalbum/6.jpg" style = "background-image: url('css/pic/photoalbum/6.jpg');" onclick = "new Gallery(this);"></div>
			<div data-id = "1" data-url = "css/pic/photoalbum/3.jpg" style = "background-image: url('css/pic/photoalbum/3.jpg');" onclick = "new Gallery(this);"></div>
			<div data-id = "1" data-url = "css/pic/photoalbum/10.jpg" style = "background-image: url('css/pic/photoalbum/10.jpg');" onclick = "new Gallery(this);"></div>
			<div data-id = "1" data-url = "css/pic/photoalbum/11.jpg" style = "background-image: url('css/pic/photoalbum/11.jpg');" onclick = "new Gallery(this);"></div>
			<div data-id = "1" data-url = "css/pic/photoalbum/12.jpg" style = "background-image: url('css/pic/photoalbum/12.jpg');" onclick = "new Gallery(this);"></div>
			<div data-id = "1" data-url = "css/pic/photoalbum/13.jpg" style = "background-image: url('css/pic/photoalbum/13.jpg');" onclick = "new Gallery(this);"></div>
			<div data-id = "1" data-url = "css/pic/photoalbum/14.jpg" style = "background-image: url('css/pic/photoalbum/14.jpg');" onclick = "new Gallery(this);"></div>
			<div data-id = "1" data-url = "css/pic/photoalbum/15.jpg" style = "background-image: url('css/pic/photoalbum/15.jpg');" onclick = "new Gallery(this);"></div>
			<div data-id = "1" data-url = "css/pic/photoalbum/16.jpg" style = "background-image: url('css/pic/photoalbum/16.jpg');" onclick = "new Gallery(this);"></div>
			<div data-id = "1" data-url = "css/pic/photoalbum/17.jpg" style = "background-image: url('css/pic/photoalbum/17.jpg');" onclick = "new Gallery(this);"></div>
			<div data-id = "1" data-url = "css/pic/photoalbum/18.jpg" style = "background-image: url('css/pic/photoalbum/18.jpg');" onclick = "new Gallery(this);"></div>
			<div data-id = "1" data-url = "css/pic/photoalbum/22.jpg" style = "background-image: url('css/pic/photoalbum/22.jpg');" onclick = "new Gallery(this);"></div>
			<div data-id = "1" data-url = "css/pic/photoalbum/20.jpg" style = "background-image: url('css/pic/photoalbum/20.jpg');" onclick = "new Gallery(this);"></div>
			<div data-id = "1" data-url = "css/pic/photoalbum/21.jpg" style = "background-image: url('css/pic/photoalbum/21.jpg');" onclick = "new Gallery(this);"></div>
<!--			<div class = "photo_line1">-->
<!--				<div data-id = "1" data-url = "css/pic/photoalbum/2.jpg" style = "background-image: url('css/pic/photoalbum/2.jpg');" onclick = "new Gallery(this);"></div>-->
<!--				<div data-id = "1" data-url = "css/pic/photoalbum/8.jpg" style = "background-image: url('css/pic/photoalbum/8.jpg');" onclick = "new Gallery(this);"></div>-->
<!--				<div data-id = "1" data-url = "css/pic/photoalbum/4.jpg" style = "background-image: url('css/pic/photoalbum/4.jpg');" onclick = "new Gallery(this);"></div>-->
<!--			</div>-->
<!--			<div class = "photo_line2">-->
<!--				<div data-id = "2" data-url = "css/pic/photoalbum/5.jpg" style = "background-image: url('css/pic/photoalbum/5.jpg');" onclick = "new Gallery(this);"></div>-->
<!--				<div data-id = "2" data-url = "css/pic/photoalbum/6.jpg" style = "background-image: url('css/pic/photoalbum/6.jpg');" onclick = "new Gallery(this);"></div>-->
<!--				<div data-id = "2" data-url = "css/pic/photoalbum/3.jpg" style = "background-image: url('css/pic/photoalbum/3.jpg');" onclick = "new Gallery(this);"></div>-->
<!--			</div>-->
<!--			<div class = "photo_line3">-->
<!--				<div></div>-->
<!--				<div></div>-->
<!--				<div></div>-->
<!--			</div>-->
<!--			<div class = "photo_line1">-->
<!--				<div></div>-->
<!--				<div></div>-->
<!--				<div></div>-->
<!--			</div>-->
<!--			<div class = "photo_line2">-->
<!--				<div></div>-->
<!--				<div></div>-->
<!--				<div></div>-->
<!--			</div>-->
<!--			<div class = "photo_line3">-->
<!--				<div></div>-->
<!--				<div></div>-->
<!--				<div></div>-->
<!--			</div>-->
		</div>
	</div>
    <script>
        $(() => ScrollTop('main'));
    </script>
    <?php
}