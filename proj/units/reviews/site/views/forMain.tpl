<?php

namespace Proj\Site\Templates\Reviews;

use Base\Templates\View;

class ForMain extends View {

	public function ToVar(): string {
		$this->Start();
		$this->Render();
		return $this->Read();
	}

	public function Render() { ?>
<!--		<div class = "review_cards">-->
<!--			<div class = "review_card" onclick = "SeeReview(this);">-->
<!--				<div class = "review_person">-->
<!--					<div></div>-->
<!--					<div>Карина Турова</div>-->
<!--				</div>-->
<!--				<div class = "review_text">Сам отзыв. Тур понравился, природа там замечательная. Было предоставлено свободное время, чтобы погулять и посмотреть что-то самим. Гид давала хорошие рекомендации. Очень понравился о. Ольхон и д. Тальцы.Гид давала хорошие рекомендации. Очень понравился о. Ольхон и д. Тальцы.</div>-->
<!--			</div>-->
<!--			<div class = "review_card" onclick = "SeeReview(this);">-->
<!--				<div class = "review_person">-->
<!--					<div></div>-->
<!--					<div>Наташа Иванова</div>-->
<!--				</div>-->
<!--				<div class = "review_text">Сам отзыв. Всё прошло увлекательно много посмотрели, гид всё показал расказал ,помог с выбором. Еда в столовой по домашнему.</div>-->
<!--			</div>-->
<!--		</div>-->
		<div class = "block p reviews">
			<div>
				<div class = "header" onclick = " window.location.href = '/review';">Отзывы</div>
				<span title = "оставить отзыв"></span>
			</div>
			<div>
				<div class = "arrow_left"></div>
				<div class = "review_cards">
					<div class = "review_card" onclick = "SeeReview(this);">
						<div class = "review_person">
							<div></div>
							<div>Карина Турова</div>
						</div>
						<div class = "review_text">Сам отзыв. Тур понравился, природа там замечательная. Было предоставлено свободное время, чтобы погулять и посмотреть что-то самим. Гид давала хорошие рекомендации. Очень понравился о. Ольхон и д. Тальцы.Гид давала хорошие рекомендации. Очень понравился о. Ольхон и д. Тальцы.</div>
					</div>
					<div class = "review_card" onclick = "SeeReview(this);">
						<div class = "review_person">
							<div></div>
							<div>Наташа Иванова</div>
						</div>
						<div class = "review_text">Сам отзыв. Всё прошло увлекательно много посмотрели, гид всё показал расказал ,помог с выбором. Еда в столовой по домашнему.</div>
					</div>
				</div>
				<div class = "arrow_right"></div>
			</div>
		</div>
	<?php }

}