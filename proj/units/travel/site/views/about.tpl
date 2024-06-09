<?php

    namespace Proj\Site\Templates\Travel;

    use Base\Templates\Buffering;

    abstract class About {

        public static function ToVar(array $data): string {
			Buffering::Start();
        	self::Render($data);
            return Buffering::Read();
        }

        public static function Render(array $data): void { ?>
            <div class = "about_tour block p">
                <div><?= nl2br($data['description']); ?></div>
                <div class = "about_mini">
                    <div>
                        <div><?= MoneyFormat($data['price']); ?> ₽</div>
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