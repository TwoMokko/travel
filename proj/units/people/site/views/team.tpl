<?php

    namespace Proj\Site\Templates\People;

    use Base\Templates\View;
    use Proj\Units\Consts;

    class Team extends View {

        public function ToVar(array $items): string {
            $this->Start();
            $this->Team($items);
            return $this->Read();
        }

        public function Team($items) { ?>
            <div class = "block p team">
                <?php foreach ($items as $item) $this->Item($item); ?>
            </div>
        <?php }

        private function Item($data) { ?>
            <div>
                <div class = "about_pic" style = "background-image: url(<?= Consts\People::PATH_AVATAR_RELATIVE, $data['image']; ?>);"></div>
                <div class = "about_text">
                    <!--						<div>Организатор</div>-->
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