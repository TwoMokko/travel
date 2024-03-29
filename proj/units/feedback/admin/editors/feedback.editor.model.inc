<?php

	namespace Proj\Admin\Editor\Model;

	use Base\DB\MySQLi\Table;
	use Base\DB\MySQLi\Select;
	use Base\Editor\MySQLi\Model;
	use Proj\Units\Consts;

	class Feedback extends Model {
		public function __construct(Table $table, array $params = []) {
			parent::__construct($table, $params);
		}

		protected function Init(): void {
			$this->querySelect = new Select();
			$this->querySelect
				->calc("*")
				->table($this->table->GetName())
				->where('`state` != ' . Consts\Feedback::STATES['error'])
				->order('date_create', 'DESC')
				->order('id');

			$this->states = [
				Consts\Feedback::STATE_UNVERIFIED => [Consts\Feedback::STATE_VERIFIED]
			];
		}

	}