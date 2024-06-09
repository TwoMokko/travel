<?php

    namespace Proj\Site\Templates\Travel;

    use Base\Templates\Buffering;

   abstract class Select {

        public static function ToVar(array $data): string {
			Buffering::Start();
            self::Render($data);
            return Buffering::Read();
        }

        public static function Render(array $data): void { ?>
            <div class = "block check_tour">
                <div>
                    <form>
                        <div>
                            <div>
                                <div>Выберите вид путешествий</div>
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