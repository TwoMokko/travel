<?php

	namespace Proj\Admin\Editor\Model\Travel;

	use Base\DB\MySQLi\Table;
	use Base\DB\MySQLi\Select;
	use Base\Editor\MySQLi\Model;
	use Base\Helper\Data\Prepare;
	use Base\Helper\Data\Validation;
	use Proj\Units\Consts;

	class Direction extends Model {
		private Table $table_additional_expenses;
		private Table $table_expenses;

		public function __construct(array /** @var Table $tables */ $tables, array $params = []) {
			[$table, $this->table_expenses, $this->table_additional_expenses] = $tables;
			parent::__construct($table, $params);
		}

		protected function Init(): void {
			$this->querySelect = new Select();
			$this->querySelect
				->calc("*")
				->table($this->table->GetName())
				->where('`state` != ' . Consts\Travel::STATE_DELETE)
				->order('id');
		}

		public function Create(array $data, array $params = []): bool {
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

			$this->PrepareData($data);
			if (!$this->ValidateData($data)) return false;

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

			$this->PrepareData($data);
			if (!$this->ValidateData($data)) return false;

			$this->table_expenses->Delete("`tour_id` = {$id}");
			$this->SaveExpense($expense, $id);
			$this->table_additional_expenses->Delete("`tour_id` = {$id}");
			$this->SaveAdditionalExpense($additional_expense, $id);

			$this->table->Update($data, "`id` = {$id}");

			return true;
		}

		private function PrepareData(array & $data): void {
			$data['name'] = Prepare::Trim($data['name']);
			$data['video'] = Prepare::Trim($data['video']);
		}

		private function ValidateData(array $data): bool {
			return Validation::Required($data['name']);
		}

		private function SaveExpense(array $items, int $id): void {
			if ($items) {
				$valuesItems = [];
				foreach ($items as $item) $valuesItems[] = "({$id}, '{$item['expense']}')";
				$values = implode(', ', $valuesItems);
				$this->table_expenses->Query("INSERT INTO `{$this->table_expenses->GetName()}` (`tour_id`, `expense`) VALUES {$values}");
			}
		}

		private function SaveAdditionalExpense(array $items, int $id): void {
			if ($items) {
				$valuesItems = [];
				foreach ($items as $item) $valuesItems[] = "({$id}, '{$item['additional_expense']}')";
				$values = implode(', ', $valuesItems);
				$this->table_additional_expenses->Query("INSERT INTO `{$this->table_additional_expenses->GetName()}` (`tour_id`, `additional_expense`) VALUES {$values}");
			}
		}

		public function GetExpenseByDirectionId($id): array {
			$result = $this->table_expenses->Select(['expense'], "`tour_id` = {$id}");
			return $this->table_expenses->FetchAll($result);
		}

		public function GetAdditionalExpenseByDirectionId($id): array {
			$result = $this->table_additional_expenses->Select(['additional_expense'], "`tour_id` = {$id}");
			return $this->table_additional_expenses->FetchAll($result);
		}

	}