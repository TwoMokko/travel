<?php

    namespace Proj\Site\Templates\Tour;

    use Base\Templates\Template;

    abstract class Program {

        public static function ToVar(array $program): string {
			Template::Start();
        	self::Render($program);
            return Template::Read();
        }

        public static function Render(array $program): void { ?>
            <?php if ($program) self::Program($program); ?>
        <?php }

		public static function ProgramItem($item): void { ?>
			<div>
				<div>
					<div><?= $item['day']; ?></div>
					<div>день</div>
				</div>
				<div><?= $item['description']; ?></div>
			</div>
		<?php }

        private static function Program(array $program): void { ?>
            <div class = "tour_program block p">
                <div class = "header">Маршрут</div>
                <div>
                    <div class = "map"></div>
                    <div class = "days"><?php foreach ($program as $item) self::ProgramItem($item); ?></div>
                </div>

            </div>
        <?php }
    }