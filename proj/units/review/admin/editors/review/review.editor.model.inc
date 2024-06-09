<?php

	namespace Proj\Admin\Editor\Model;

	use Base\DB\MySQLi\Table;
	use Base\DB\MySQLi\Select;
	use Base\Editor\MySQLi\Model;
	use Proj\Units\Consts;

	class Review extends Model {
		public function __construct(Table $table, array $params = []) {
			parent::__construct($table, $params);
		}

		protected function Init(): void {
			$this->querySelect = new Select();
			$this->querySelect
				->calc('*')
				->table($this->table->GetName())
				->where('`state` != ' . Consts\Review::STATES['error'])
				->order('date_create', 'DESC')
				->order('id');
		}

		public function PrepareUpdate(array &$data, int $id): void {
			$data['state'] = Consts\Review::STATE_VERIFIED;
		}

	}