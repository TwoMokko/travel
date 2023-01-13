<?php

    require 'templates/top.tpl';
    require 'templates/footer.tpl';
    require 'templates/main.tpl';

    function Title(): string {
        return 'Путешествия';
    }

    function Head(): void {
        ?><div class = "block hat other">
        <div class = "tours_hat"></div>
        <?php Top(); ?>
        <div>
            <div>Путешествия</div>
            <div>Возможно, текст</div>
        </div>
        </div><?php
    }

    function Main(): void {
        ?>
        <div class = "relative_tours">
            <div class = "navigation_tour">
                <div><a href = "#major_travel">Основные путешествия</a></div>
                <div><a href = "#individual_support">Индивидуальное сопровождение</a></div>
                <div><a href = "#VIP">ВИП</a></div>
                <div><a href = "#weekend_tour">Выходного дня</a></div>
            </div>
            <div>
                <div class = "block page_tours p">
                    <div class = "header" id = "major_travel">Основные путешествия</div>
                    <div class = "cards_tours">
                        <div>
                            <div>
								<span>33 000 </span>
							</div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Ольхон - самый большой остров на озере Байкал. Протяженность около 80 км и ширина 15 км...</div>
<!--                                <div>Цена</div>-->
                                <div>
                                    <!--							<span class = "more">Подробнее ⟶</span>-->
                                    <a class = "button border" href = "/tour">Подробнее</a>
                                    <input type = "button" value = "Поехать" onclick = "ToDrive(); event.preventDefault();">
                                </div>
                            </div>
                        </div>
                        <a href = "/tour">
                            <div>
								<span>12 000 </span>
							</div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
<!--                                <div>Цена</div>-->
                                <div>
<!--                                    <a class = "button border" href = "/tour">Подробнее</a>-->
                                    <input type = "button" value = "Поехать" onclick = "ToDrive(); event.preventDefault();">
                                </div>
                            </div>
                        </a>
                        <a href = "/tour">
                            <div>
								<span>35 000 </span>
							</div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
<!--                                <div>Цена</div>-->
                                <div>
<!--                                    <a class = "button border" href = "/tour">Подробнее</a>-->
                                    <input type = "button" value = "Поехать" onclick = "ToDrive(); event.preventDefault();">
                                </div>
                            </div>
                        </a>
                        <a href = "/tour">
                            <div>
								<span>45 000 </span>
							</div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
<!--                                <div>Цена</div>-->
                                <div>
<!--                                    <a class = "button border" href = "/tour">Подробнее</a>-->
                                    <input type = "button" value = "Поехать" onclick = "ToDrive(); event.preventDefault();">
                                </div>
                            </div>
                        </a>
                        <a href = "/tour">
                            <div>
								<span>30 000 </span>
							</div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
<!--                                <div>Цена</div>-->
                                <div>
<!--                                    <a class = "button border" href = "/tour">Подробнее</a>-->
                                    <input type = "button" value = "Поехать" onclick = "ToDrive(); event.preventDefault();">
                                </div>
                            </div>
                        </a>
                        <a href = "/tour">
                            <div>
								<span>40 000 </span>
							</div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
<!--                                <div>Цена</div>-->
                                <div>
<!--                                    <a class = "button border" href = "/tour">Подробнее</a>-->
                                    <input type = "button" value = "Поехать" onclick = "ToDrive(); event.preventDefault();">
                                </div>
                            </div>
                        </a>
                        <a href = "/tour">
                            <div>
								<span>35 000 </span>
							</div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
<!--                                <div>Цена</div>-->
                                <div>
<!--                                    <a class = "button border" href = "/tour">Подробнее</a>-->
                                    <input type = "button" value = "Поехать" onclick = "ToDrive(); event.preventDefault();">
                                </div>
                            </div>
                        </a>
                        <a href = "/tour">
                            <div>
								<span>18 000 </span>
							</div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
<!--                                <div>Цена</div>-->
                                <div>
<!--                                    <a class = "button border" href = "/tour">Подробнее</a>-->
                                    <input type = "button" value = "Поехать" onclick = "ToDrive(); event.preventDefault();">
                                </div>
                            </div>
                        </a>
                        <a href = "/tour">
                            <div>
								<span>8 000 </span>
							</div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
<!--                                <div>Цена</div>-->
                                <div>
<!--                                    <a class = "button border" href = "/tour">Подробнее</a>-->
                                    <input type = "button" value = "Поехать" onclick = "ToDrive(); event.preventDefault();">
                                </div>
                            </div>
                        </a>
                    </div>
                </div>
                <div class = "block page_tours p">
                    <div class = "header" id = "individual_support">Индивидуальное сопровождение</div>
                    <div class = "cards_tours">
                        <a href = "/tour">
                            <div>
								<span>45 000 </span>
							</div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
<!--                                <div>Цена</div>-->
                                <div>
<!--                                    <a class = "button border" href = "/tour">Подробнее</a>-->
                                    <input type = "button" value = "Поехать" onclick = "ToDrive(); event.preventDefault();">
                                </div>
                            </div>
                        </a>
                        <a href = "/tour">
                            <div>
								<span>40 000 </span>
							</div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
<!--                                <div>Цена</div>-->
                                <div>
<!--                                    <a class = "button border" href = "/tour">Подробнее</a>-->
                                    <input type = "button" value = "Поехать" onclick = "ToDrive(); event.preventDefault();">
                                </div>
                            </div>
                        </a>
                        <a href = "/tour">
                            <div>
								<span>55 000 </span>
							</div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
<!--                                <div>Цена</div>-->
                                <div>
<!--                                    <a class = "button border" href = "/tour">Подробнее</a>-->
                                    <input type = "button" value = "Поехать" onclick = "ToDrive(); event.preventDefault();">
                                </div>
                            </div>
                        </a>
                    </div>
                </div>
                <div class = "block page_tours p">
                    <div class = "header" id = "VIP">ВИП</div>
                    <div class = "cards_tours">
                        <a href = "/tour">
                            <div>
								<span>75 000 </span>
							</div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
<!--                                <div>Цена</div>-->
                                <div>
<!--                                    <a class = "button border" href = "/tour">Подробнее</a>-->
                                    <input type = "button" value = "Поехать" onclick = "ToDrive(); event.preventDefault();">
                                </div>
                            </div>
                        </a>
                        <a href = "/tour">
                            <div>
								<span>68 000 </span>
							</div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
<!--                                <div>Цена</div>-->
                                <div>
<!--                                    <a class = "button border" href = "/tour">Подробнее</a>-->
                                    <input type = "button" value = "Поехать" onclick = "ToDrive(); event.preventDefault();">
                                </div>
                            </div>
                        </a>
                    </div>
                </div>
                <div class = "block page_tours p">
                    <div class = "header" id = "weekend_tour">Выходного дня</div>
                    <div class = "cards_tours">
                        <a href = "/tour">
                            <div>
								<span>5 000 </span>
							</div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
<!--                                <div>Цена</div>-->
                                <div>
<!--                                    <a class = "button border" href = "/tour">Подробнее</a>-->
                                    <input type = "button" value = "Поехать" onclick = "ToDrive(); event.preventDefault();">
                                </div>
                            </div>
                        </a>
                        <a href = "/tour">
                            <div>
								<span>8 000 </span>
							</div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
<!--                                <div>Цена</div>-->
                                <div>
<!--                                    <a class = "button border" href = "/tour">Подробнее</a>-->
                                    <input type = "button" value = "Поехать" onclick = "ToDrive(); event.preventDefault();">
                                </div>
                            </div>
                        </a>
                    </div>
                </div>
            </div>
        </div>
        <script>
            NavigationTour('.navigation_tour', 120, 50);
            $(() => ScrollTop('main'));
        </script>
        <?php
    }