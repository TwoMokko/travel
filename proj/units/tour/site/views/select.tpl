<?php

    namespace Proj\Site\Templates\Tour;

    use Base\Templates\View;

    class Select extends View {

        public function ToVar(array $data): string {
            $this->Start();
            $this->Render($data);
            return $this->Read();
        }

        public function Render(array $data) { ?>
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