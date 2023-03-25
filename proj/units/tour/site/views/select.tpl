<?php

    namespace Proj\Site\Templates\Tour;

    use Base\Templates\Template;

   abstract class Select {

        public static function ToVar(array $data): string {
			Template::Start();
            self::Render($data);
            return Template::Read();
        }

        public static function Render(array $data): void { ?>
            <div class = "block check_tour">
                <div>
                    <form>
                        <div>
                            <div>
                                <div>Выберите категорию</div>
                                <select id = "categories"></select>
                            </div>
                            <div>
                                <div>Выберите путешествие</div>
                                <select id = "tours"></select>
                            </div>
                        </div>
                        <div>
                            <a id = "see_tour" class = "button">Подробнее о путешествии</a>
                        </div>
                    </form>
                </div>
            </div>
            <script>
                $(() => {
                    new SelectTour(<?= json_encode($data); ?>);
                });
            </script>
        <?php }

    }