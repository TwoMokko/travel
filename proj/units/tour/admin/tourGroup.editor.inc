<?php

	namespace Proj\Admin\Editor;

	use JetBrains\PhpStorm\NoReturn;

	use Base\DB\TableMySQLi;
	use Base\Editor\EditorMySQLi;
	use Base\Editor\Skins;
	use Proj\Admin\Units;
	use Proj\Units\Consts;

	class TourGroup extends EditorMySQLi {
		private TableMySQLi $table_expense;
		private TableMySQLi $table_additional_expense;

		public function __construct(string $name, array $tables) {
			[$table, $this->table_expense, $this->table_additional_expense] = $tables;
			parent::__construct($name, $table);
		}

		protected function Where(array $params): array {
			return [
				'`state` != ' . Consts\Tour::STATES['delete']
			];
		}

		protected function Order(): array {
			return [
				'`id` ASC'
			];
		}

		protected function RegTitles(): void {
			$this->titleSelect = 'Список направлений туров';
			$this->titleCreate = 'Добавить направление тура';
			$this->titleUpdate = 'Редактирование направления тура';
			$this->titleDelete = 'Удалить направление тура?';

			$this->titleDoCreate = 'Направление тура добавлено';
			$this->titleDoUpdate = 'Направление тура изменено';
			$this->titleDoDelete = 'Направление тура удалено';
		}

		protected function FieldsSelect(array $params): array {
			return [
				'id' 				=> new Skins\Browse\Text('#'),
                'state' 		    => new Skins\Browse\ValueFromArray('Состояние', Consts\Tour::STATES_RU),
                'name' 				=> new Skins\Browse\Text('Название')
			];
		}

		protected function FieldsBrowse(array $params) : array {
			return [
                'state'    	 	    => new Skins\Browse\ValueFromArray('Состояние', Consts\Tour::STATES_RU),
                'name'    		    => new Skins\Browse\Text('Заголовок'),
			];
		}

		protected function FieldsCreate(array $params): array {
			return $this->FieldsCreateAndUpdate();
		}

		protected function FieldsUpdate(array $params): array {
			return $this->FieldsCreateAndUpdate();
		}

		private function FieldsCreateAndUpdate(): array {
            $states = [
                Consts\People::STATE_DRAFT => Consts\People::STATES_RU[Consts\People::STATE_DRAFT],
                Consts\People::STATE_ACTIVE => Consts\People::STATES_RU[Consts\People::STATE_ACTIVE],
                Consts\People::STATE_INACTIVE => Consts\People::STATES_RU[Consts\People::STATE_INACTIVE],
            ];

			return [
                'state' 				=> new Skins\Edit\Select('Состояние', 'form[state]',  $states),
                'name' 					=> new Skins\Edit\Text('Заголовок', 'form[name]'),
				'video' 				=> new Skins\Edit\Text('Ссылка видео', 'form[video]'),
				'photo_id' 				=> new Skins\Edit\Select('Фотоальбом', 'form[photo_id]', Units\Photo::instance()->GetAlbums()),
				'expense'           	=> new Skins\Edit\Table('Входит в стоимость', 'form[expense]', [
					'expense' => ['alias' => 'входит в стоимость', 'type' => 'text', 'name' => 'expense']
				]),
				'additional_expense'	=> new Skins\Edit\Table('Дополнительные расходы', 'form[additional_expense]', [
					'additional_expense' => ['alias' => 'дополнительные расходы', 'type' => 'text', 'name' => 'additional_expense']
				])
			];
		}

		public function PrepareOnCreate(array & $data): void {
			$data['state'] = [
				Consts\Tour::STATE_DRAFT	=> 'Черновик',
				Consts\Tour::STATE_ACTIVE	=> 'Активная',
				Consts\Tour::STATE_INACTIVE	=> 'Не активная',
			];
		}

		public function PrepareOnUpdate(int $id, array & $item, array & $data): void {
			$data['state'] = [
				Consts\Tour::STATE_DRAFT	=> 'Черновик',
				Consts\Tour::STATE_ACTIVE	=> 'Активная',
				Consts\Tour::STATE_INACTIVE	=> 'Не активная',
			];

			$result = $this->table_expense->Select(['expense'], "`tour_id`={$id}");
			$item['expense'] = $this->table_expense->FetchAll($result);

			$result = $this->table_additional_expense->Select(['additional_expense'], "`tour_id`={$id}");
			$item['additional_expense'] = $this->table_additional_expense->FetchAll($result);
		}

		#[NoReturn] public function DoCreate(): void {
			$data = GetParam('form', []);

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

			$id = $this->table->Insert($data);

			$this->SaveExpense($expense, $id);
			$this->SaveAdditionalExpense($additional_expense, $id);

			SendJSONSuccess(['message' => $this->titleDoCreate, 'html' => $this->Select()]);
		}

		#[NoReturn] public function DoUpdate(): void {
			$id = (int)GetParam('id', 0);
			$data = GetParam('form', []);

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

			SendJSONSuccess(['message' => $this->titleDoCreate, 'html' => $this->Select()]);
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

	}