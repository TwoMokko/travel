<?php

    namespace Proj\Site\Templates\Travel;

    use Base\Templates\Buffering;

    abstract class Program {

        public static function ToVar(array $program): string {
			Buffering::Start();
        	self::Render($program);
            return Buffering::Read();
        }

        public static function Render(array $program): void { if (!$program) return; ?>
			<div class = "tour_program block p">
				<div class = "header">Маршрут</div>
				<div>
					<div class = "map"></div>
					<div class = "days"><?php foreach ($program as $item) self::Item($item); ?></div>
				</div>
			</div>
        <?php }

		public static function Item($item): void { ?>
			<div>
				<div>
					<div><?= $item['day']; ?></div>
					<div>день</div>
				</div>
				<div><?= $item['description']; ?></div>
			</div>
		<?php }

    }