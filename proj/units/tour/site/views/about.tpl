<?php

    namespace Proj\Site\Templates\Tour;

    use Base\Templates\Template;

    abstract class About {

        public static function ToVar(array $data): string {
			Template::Start();
        	self::Render($data);
            return Template::Read();
        }

        public static function Render(array $data): void { ?>
            <div class = "about_tour block p">
                <div><?= $data['description']; ?></div>
                <div class = "about_mini">
                    <div>
                        <div><?= $data['price']; ?> ₽</div>
                        <div>Стоимость</div>
                    </div>
                    <div>
                        <div><?= $data['duration']; ?> дней</div>
                        <div>Длительность</div>
                    </div>
                </div>
            </div>
         <?php }

    }