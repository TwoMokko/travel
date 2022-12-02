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
                <div>1</div>
                <div>2</div>
                <div>3</div>
                <div>4</div>
            </div>
            <div>
                <div class = "block page_tours p">
                    <div class = "header">Основные путешествия</div>
                    <div class = "cards_tours">
                        <div>
                            <div></div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
                                <div>Цена</div>
                                <div>
                                    <!--							<span class = "more">Подробнее ⟶</span>-->
                                    <a class = "button border" href = "/tour">Подробнее</a>
                                    <input type = "button" value = "Поехать">
                                </div>
                            </div>
                        </div>
                        <div>
                            <div></div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
                                <div>Цена</div>
                                <div>
                                    <a class = "button border" href = "/tour">Подробнее</a>
                                    <input type = "button" value = "Поехать">
                                </div>
                            </div>
                        </div>
                        <div>
                            <div></div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
                                <div>Цена</div>
                                <div>
                                    <a class = "button border" href = "/tour">Подробнее</a>
                                    <input type = "button" value = "Поехать">
                                </div>
                            </div>
                        </div>
                        <div>
                            <div></div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
                                <div>Цена</div>
                                <div>
                                    <a class = "button border" href = "/tour">Подробнее</a>
                                    <input type = "button" value = "Поехать">
                                </div>
                            </div>
                        </div>
                        <div>
                            <div></div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
                                <div>Цена</div>
                                <div>
                                    <a class = "button border" href = "/tour">Подробнее</a>
                                    <input type = "button" value = "Поехать">
                                </div>
                            </div>
                        </div>
                        <div>
                            <div></div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
                                <div>Цена</div>
                                <div>
                                    <a class = "button border" href = "/tour">Подробнее</a>
                                    <input type = "button" value = "Поехать">
                                </div>
                            </div>
                        </div>
                        <div>
                            <div></div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
                                <div>Цена</div>
                                <div>
                                    <a class = "button border" href = "/tour">Подробнее</a>
                                    <input type = "button" value = "Поехать">
                                </div>
                            </div>
                        </div>
                        <div>
                            <div></div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
                                <div>Цена</div>
                                <div>
                                    <a class = "button border" href = "/tour">Подробнее</a>
                                    <input type = "button" value = "Поехать">
                                </div>
                            </div>
                        </div>
                        <div>
                            <div></div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
                                <div>Цена</div>
                                <div>
                                    <a class = "button border" href = "/tour">Подробнее</a>
                                    <input type = "button" value = "Поехать">
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
                <div class = "block page_tours p">
                    <div class = "header">Индивидуальное сопровождение</div>
                    <div class = "cards_tours">
                        <div>
                            <div></div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
                                <div>Цена</div>
                                <div>
                                    <a class = "button border" href = "/tour">Подробнее</a>
                                    <input type = "button" value = "Поехать">
                                </div>
                            </div>
                        </div>
                        <div>
                            <div></div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
                                <div>Цена</div>
                                <div>
                                    <a class = "button border" href = "/tour">Подробнее</a>
                                    <input type = "button" value = "Поехать">
                                </div>
                            </div>
                        </div>
                        <div>
                            <div></div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
                                <div>Цена</div>
                                <div>
                                    <a class = "button border" href = "/tour">Подробнее</a>
                                    <input type = "button" value = "Поехать">
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
                <div class = "block page_tours p">
                    <div class = "header">ВИП</div>
                    <div class = "cards_tours">
                        <div>
                            <div></div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
                                <div>Цена</div>
                                <div>
                                    <a class = "button border" href = "/tour">Подробнее</a>
                                    <input type = "button" value = "Поехать">
                                </div>
                            </div>
                        </div>
                        <div>
                            <div></div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
                                <div>Цена</div>
                                <div>
                                    <a class = "button border" href = "/tour">Подробнее</a>
                                    <input type = "button" value = "Поехать">
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
                <div class = "block page_tours p">
                    <div class = "header">Выходного дня</div>
                    <div class = "cards_tours">
                        <div>
                            <div></div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
                                <div>Цена</div>
                                <div>
                                    <a class = "button border" href = "/tour">Подробнее</a>
                                    <input type = "button" value = "Поехать">
                                </div>
                            </div>
                        </div>
                        <div>
                            <div></div>
                            <div>
                                <div>Дата</div>
                                <div>Название</div>
                                <div>Описание</div>
                                <div>Цена</div>
                                <div>
                                    <a class = "button border" href = "/tour">Подробнее</a>
                                    <input type = "button" value = "Поехать">
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        <script>
            NavigationTour('.navigation_tour', 200, 20);
        </script>
        <?php
    }