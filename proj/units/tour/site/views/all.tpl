<?php

    namespace Proj\Site\Templates\Tour;

    use Base\Templates\View;
    use Proj\Site\Units\General;
    use Proj\Site\Units\Tour;
    use Proj\Units\Consts;

    class All extends View {

        public function ToVar(array $items): string {
            $this->Start();
            $this->All($items);
            return $this->Read();
        }

        public function All($data) { ?>
            <div class = "relative_tours">
                <?php $this->Navigation($data); ?>
                <div>
                    <?php foreach ($data as $type) $this->Type($type); ?>
                </div>
            </div>
            <script>
                NavigationTour('.navigation_tour', 120, 50);
            </script>
        <?php }

        private function Navigation($data) { ?>
            <div class = "navigation_tour">
                <?php foreach ($data as $type) { ?>
                    <div><a href = "#<?= $type['alias']; ?>"><?= $type['name']; ?></a></div>
                <?php } ?>
            </div>
        <?php }

        private function Type($type) { ?>
            <div class = "block page_tours p">
                <div class = "header" id = "<?= $type['alias']; ?>"><?= $type['name']; ?></div>
                <div class = "cards_tours">
                    <?php foreach ($type['tours'] as $tour) $this->Item($tour); ?>
                </div>
            </div>
        <?php }

        private function Item($tour) { ?>
            <div>
                <div style = "background-image: url(<?= Consts\Tour::PATH_TOUR_RELATIVE, $tour['image']; ?>);">
                    <span><?= $tour['price']; ?></span>
                </div>
                <div>
                    <div><?= $tour['date']; ?></div>
                    <div><?= $tour['name']; ?></div>
                    <div><?= $tour['description']; ?></div>
                    <!--                                <div>Цена</div>-->
                    <div>
                        <?= Tour::instance()->item->GetLink('Подробнее', ['id' => $tour['id']], ['class' => 'button border']); ?>
                        <a class = "button" onclick = "ToDrive(); event.preventDefault();">Поехать</a>
                        <!--                                    <input type = "button" value = "Поехать" onclick = "ToDrive(); event.preventDefault();">-->
                    </div>
                </div>
            </div>
        <?php }

    }