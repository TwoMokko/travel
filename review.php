<?php

require 'templates/top.tpl';
require 'templates/footer.tpl';
require 'templates/main.tpl';

function Title(): string {
	return 'Отзывы';
}

function Head(): void {
	?><div class = "block hat other">
	<div class = "reviews_hat"></div>
	<?php Top(); ?>
	<div>
		<div>Отзывы</div>
		<div>Возможно, текст</div>
	</div>
	</div><?php
}


function Main(): void {
	?><div class = "block p">
		<div class = "review_cards">
			<div class = "review_card">
				<div class = "review_person">
					<div></div>
					<div>Карина Турова</div>
				</div>
				<div class = "review_text">Сам отзыв. Тур понравился, природа там замечательная. Было предоставлено свободное время, чтобы погулять и посмотреть что-то самим. Гид давала хорошие рекомендации. Очень понравился о. Ольхон и д. Тальцы.</div>
			</div>
			<div class = "review_card">
				<div class = "review_person">
					<div></div>
					<div>Наташа Иванова</div>
				</div>
				<div class = "review_text">Сам отзыв. Всё прошло увлекательно много посмотрели, гид всё показал расказал ,помог с выбором. Еда в столовой по домашнему.</div>
			</div>
			<div class = "review_card">
				<div class = "review_person">
					<div></div>
					<div>Карина Турова</div>
				</div>
				<div class = "review_text">Сам отзыв. Тур понравился, природа там замечательная. Было предоставлено свободное время, чтобы погулять и посмотреть что-то самим. Гид давала хорошие рекомендации. Очень понравился о. Ольхон и д. Тальцы.</div>
			</div>
			<div class = "review_card">
				<div class = "review_person">
					<div></div>
					<div>Наташа Иванова</div>
				</div>
				<div class = "review_text">Сам отзыв. Всё прошло увлекательно много посмотрели, гид всё показал расказал ,помог с выбором. Еда в столовой по домашнему.</div>
			</div>
			<div class = "review_card">
				<div class = "review_person">
					<div></div>
					<div>Карина Турова</div>
				</div>
				<div class = "review_text">Сам отзыв. Тур понравился, природа там замечательная. Было предоставлено свободное время, чтобы погулять и посмотреть что-то самим. Гид давала хорошие рекомендации. Очень понравился о. Ольхон и д. Тальцы.</div>
			</div>
			<div class = "review_card">
				<div class = "review_person">
					<div></div>
					<div>Наташа Иванова</div>
				</div>
				<div class = "review_text">Сам отзыв. Всё прошло увлекательно много посмотрели, гид всё показал расказал ,помог с выбором. Еда в столовой по домашнему.</div>
			</div>
			<div class = "review_card">
				<div class = "review_person">
					<div></div>
					<div>Карина Турова</div>
				</div>
				<div class = "review_text">Сам отзыв. Тур понравился, природа там замечательная. Было предоставлено свободное время, чтобы погулять и посмотреть что-то самим. Гид давала хорошие рекомендации. Очень понравился о. Ольхон и д. Тальцы.</div>
			</div>
			<div class = "review_card">
				<div class = "review_person">
					<div></div>
					<div>Наташа Иванова</div>
				</div>
				<div class = "review_text">Сам отзыв. Всё прошло увлекательно много посмотрели, гид всё показал расказал ,помог с выбором. Еда в столовой по домашнему.</div>
			</div>
		</div>
	</div>
	<script>
		$(() => ScrollTop('main'));
	</script>
	<?php
}