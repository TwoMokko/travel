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
            <div class = "adventure_text">
                <div>Наше новогоднее приключение на Ольхоне было бы не полным без перехода через остров на другой берег, к так называемому "большому морю" озера Байкал.
                    <p>Прошлый год был довольно снежным. Поэтому выйдя утром на маршрут мы поняли, что придется самим прокладывать путь в рыхлом, сыпучем снегу. Дорога предстояла трудная, в один конец 15 км с преодолением перевала высотой 800 м. День выдался морозным, поэтому наши волосы и одежда покрылись инеем от расходившегося от нас тепла. К обеду мы достигли заветного места, цели нашего путешествия, берега большого моря Байкала!
                    <p>И каково было наше удивление, когда мы увидели плескающуюся водную поверхность, особенно после того как мы почти неделю гуляли и катались на коньках по льду малого моря Байкала, близ деревни Хужир. Но самое волшебство произошло чуть позже. За несколько часов, пока мы находились у берега, именно тогда Байкал решил впать в спячку, и мы стали свидетелями, как одно из самых величественных озёр в мире засыпает на наших глазах.
                    <p>Это было потрясающее приключение, и уникальное явление природы, свидетелями которого мы явились!
                </div>
                <div>
                    <div data-id = "1" data-url = "css/pic/photoalbum/22.jpg" style = "background-image: url('proj/templates/site/css/pic/photoalbum/22.jpg');" onclick = "new Gallery(this);"></div>
                    <div data-id = "1" data-url = "css/pic/photoalbum/18.jpg" style = "background-image: url('proj/templates/site/css/pic/photoalbum/18.jpg');" onclick = "new Gallery(this);"></div>
                </div>
            </div>
            <div class = "other_publication other_adventure">
                <div>
                    <span class = "header" onclick = " window.location.href = '/adventures';">Другие приключения</span>
                </div>
               <div>
				   <div class = "arrow_left"></div>
				   <div>
					   <a href = "/adventure">Название</a>
					   <a href = "/adventure">Другое более длинное название и ещё длиннее</a>
					   <a href = "/adventure">Ещё одно</a>
					   <a href = "/adventure">Четвёртое</a>
				   </div>
				   <div class = "arrow_right"></div>
			   </div>
            </div>
        </div>
        <script>
            $(() => ScrollTop('main'));
        </script>
        <?php
	}
