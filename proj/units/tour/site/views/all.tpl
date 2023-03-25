<?php

    namespace Proj\Site\Templates\Tour;

    use Base\Templates\Template;
    use Proj\Site\Units\Tour;
    use Proj\Units\Consts;

    abstract class All {

        public static function ToVar(array $items): string {
			Template::Start();
            self::All($items);
            return Template::Read();
        }

        public static function All($data): void { ?>
            <div class = "relative_tours">
                <?php self::Navigation($data); ?>
                <div>
                    <?php foreach ($data as $type) self::Type($type); ?>
                </div>
            </div>
            <script>
                NavigationTour('.navigation_tour', 120, 50);
            </script>
        <?php }

        private static function Navigation($data): void { ?>
            <div class = "navigation_tour">
                <?php foreach ($data as $type) { ?>
                    <div><a href = "#<?= $type['alias']; ?>"><?= $type['name']; ?></a></div>
                <?php } ?>
            </div>
        <?php }

        private static function Type($type): void { ?>
            <div class = "block page_tours p">
                <div class = "header" id = "<?= $type['alias']; ?>"><?= $type['name']; ?></div>
                <div class = "cards_tours">
                    <?php foreach ($type['tours'] as $tour) self::Item($tour); ?>
                </div>
            </div>
        <?php }

        private static function Item($tour): void { ?>
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