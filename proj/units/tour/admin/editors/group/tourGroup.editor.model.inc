<?php

	namespace Proj\Admin\Editor\Model;

	use Base\DB\MySQLi\Table;
	use Base\DB\MySQLi\Select;
	use Base\Editor\MySQLi\Model;
	use Proj\Units\Consts;
	use Proj\Others\UploaderImage;

	class TourGroup extends Model {
		private Table $table_additional_expense;
		private Table $table_expense;

		public function __construct(array $tables, array $params = []) {
			[$table, $this->table_expense, $this->table_additional_expense] = $tables;
			parent::__construct($table, $params);
		}

		protected function Init(): void {
			$this->querySelect = new Select();
			$this->querySelect
				->calc("*")
				->table($this->table->GetName())
				->where('`state` != ' . Consts\Tour::STATES['delete'])
				->order('id');
		}

		public function Create(array $data, array $params): bool {
			$expense = [];
			if (isset($data['expense'])) {
				$expense = $data['expense'];
				unset($data['expense']);
			}

			$additional_expense = [];
			if (isset($data['additional_expense'])) {
				$additional_expense = $data['additional_expense'];
				unset($data['additional_expense']);
			}

			$this->PrepareData($data, [
				'name' => [self::TRANSFORM_TRIM],
				'video' => [self::TRANSFORM_TRIM]
			]);

			$valid = $this->ValidationData($data, [
				'name' => [self::VALIDATION_REQUIRED]
			]);
			if (!$valid) return false;

			$id = $this->table->Insert($data);

			$this->SaveExpense($expense, $id);
			$this->SaveAdditionalExpense($additional_expense, $id);

			return true;
		}

		public function Update(array $data, int $id): bool {
			$expense = [];
			if (isset($data['expense'])) {
				$expense = $data['expense'];
				unset($data['expense']);
			}

			$additional_expense = [];
			if (isset($data['additional_expense'])) {
				$additional_expense = $data['additional_expense'];
				unset($data['additional_expense']);
			}

//			$id = $this->table->Insert($data);

			$this->table_expense->Delete("`tour_id` = {$id}");
			$this->SaveExpense($expense, $id);
			$this->table_additional_expense->Delete("`tour_id` = {$id}");
			$this->SaveAdditionalExpense($additional_expense, $id);

			$this->table->Update($data, "`id` = {$id}");

			return true;
		}

		private function SaveExpense(array $items, int $id): void {
			if ($items) {
				$valuesItems = [];
				foreach ($items as $item) $valuesItems[] = "({$id}, '{$item['expense']}')";
				$values = implode(', ', $valuesItems);
				$this->table_expense->Query("INSERT INTO `{$this->table_expense->GetName()}` (`tour_id`, `expense`) VALUES {$values}");
			}
		}

		private function SaveAdditionalExpense(array $items, int $id): void {
			if ($items) {
				$valuesItems = [];
				foreach ($items as $item) $valuesItems[] = "({$id}, '{$item['additional_expense']}')";
				$values = implode(', ', $valuesItems);
				$this->table_additional_expense->Query("INSERT INTO `{$this->table_additional_expense->GetName()}` (`tour_id`, `additional_expense`) VALUES {$values}");
			}
		}

		public function GetExpenseByGroupId($id): array {
			$result = $this->table_expense->Select(['expense'], "`tour_id` = {$id}");
			return $this->table_expense->FetchAll($result);
		}

		public function GetAdditionalExpenseByGroupId($id): array {
			$result = $this->table_additional_expense->Select(['additional_expense'], "`tour_id` = {$id}");
			return $this->table_additional_expense->FetchAll($result);
		}

	}