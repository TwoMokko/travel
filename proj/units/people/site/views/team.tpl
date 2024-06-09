<?php

    namespace Proj\Site\Templates\People;

    use Base\Templates\Template;
	use Proj\Units\Consts;

    abstract class Team {

        public static function ToVar(array $items): string {
            Template::Start();
            self::Team($items);
            return Template::Read();
        }

        public static function Team($items): void { ?>
            <div class = "block team">
                <?php foreach ($items as $item) self::Item($item); ?>
            </div>
        <?php }

        private static function Item($data): void { ?>
            <div>
                <div class = "about_pic" style = "background-image: url(<?= Consts\People::PATH_AVATAR_RELATIVE, $data['image']; ?>);"></div>
                <div class = "about_text">
                    <div><?= $data['name']; ?></div>
                    <div><?= $data['text']; ?></div>
                    <div class = "contact_person">
                        <div>
                            <div>Тел:</div>
                            <div><?= $data['number']; ?></div>
                        </div>
                        <div>
                            <a href = "<?= $data['link_vk']; ?>"></a>
                            <a href = "<?= $data['link_wa']; ?>"></a>
                        </div>
                    </div>
                </div>
            </div>
        <?php }

    }