<?php

    namespace Proj\Site\Templates\Travel;

    use Base\Templates\Buffering;
	use Proj\Units\Consts;
	use Proj\Site\Actions;

    abstract class Tours {

        public static function ToVar(array $items): string {
			Buffering::Start();
            self::Render($items);
            return Buffering::Read();
        }

        public static function Render($data): void { ?>
            <div class = "relative_tours">
                <?php self::Navigation($data); ?>
                <div>
                    <?php foreach ($data as $type) if ($type['tours']) self::Type($type); ?>
                </div>
            </div>
            <script>
                NavigationTour('.navigation_tour', 120, 50);
            </script>
        <?php }

        private static function Navigation($data): void { ?>
            <div class = "navigation_tour">
                <?php foreach ($data as $type) { if (!$type['tours']) continue; ?>
                    <div><a href = "#type_<?= $type['id']; ?>"><?= $type['name']; ?></a></div>
                <?php } ?>
            </div>
        <?php }

        private static function Type($type): void { ?>
            <div class = "block page_tours p">
                <div class = "header" id = "type_<?= $type['id']; ?>"><?= $type['name']; ?></div>
                <div class = "cards_tours">
                    <?php foreach ($type['tours'] as $tour) self::Item($tour); ?>
                </div>
            </div>
        <?php }

        private static function Item($tour): void { ?>
            <div>
                <div style = "background-image: url(<?= Consts\Travel::PATH_TOUR_PREVIEW_RELATIVE, $tour['image']; ?>);">
                    <span><?= MoneyFormat($tour['price']); ?></span>
                </div>
                <div>
                    <div><?= $tour['date']; ?></div>
                    <div><?= $tour['name']; ?></div>
                    <div><?= $tour['description']; ?></div>
                    <div>
                        <?= Actions\Pages::$tour->GetLinkHref('Подробнее', ['id' => $tour['id']], ['class' => 'button border']); ?>
                        <a class = "button" onclick = "ToDrive(<?= $tour['id']; ?>); event.preventDefault();">Поехать</a>
                    </div>
                </div>
            </div>
        <?php }

    }