<?php

    namespace Proj\Site\Templates\Tour;

    use Base\Templates\Template;

    abstract class Expense {

        public static function ToVar(array $data, array $expense, array $additional_expense): string {
			Template::Start();
        	self::Render($data, $expense, $additional_expense);
            return Template::Read();
        }

        public static function Render(array $data, array $expense, array $additional_expense): void { ?>
			<?php if ($expense && $additional_expense) self::Expenses($data, $expense, $additional_expense); ?>
        <?php }

        public static function Expense(string $expense): void { ?>
			<div>
				<div>-</div>
				<div><?= $expense; ?></div>
			</div>
        <?php }

        public static function AdditionalExpense(string $expense): void { ?>
			<div>
				<div>-</div>
				<div><?= $expense; ?></div>
			</div>
        <?php }

        public static function Expenses($data, $expenses, $additional_expenses): void { ?>
			<div class = "tour_price block p">
				<div>Что входит в стоимость</div>
				<div>
					<div>
						<div>Цена <?= $data['price']; ?> ₽ включает:</div>
						<div class = "list"><?php foreach ($expenses as $item) self::Expense($item); ?></div>
					</div>
					<div>
						<div>Дополнительные расходы:</div>
						<div class = "list"><?php foreach ($additional_expenses as $item) self::AdditionalExpense($item); ?></div>
					</div>
				</div>
			</div>
        <?php }

    }