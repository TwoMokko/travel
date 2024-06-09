<?php

	namespace Proj\Admin\Editor\Model;

	use Base\DB\MySQLi\Table;
	use Base\DB\MySQLi\Select;
	use Base\Editor\MySQLi\Model;
	use Proj\Units\Consts;

	class Text extends Model {
		public function __construct(Table $table, array $params = []) {
			parent::__construct($table, $params);
		}

		protected function Init(): void {
			$this->querySelect = new Select();
			$this->querySelect
				->calc('*')
				->table($this->table->GetName())
				->where('`state` = ' . Consts\General::STATE_ACTIVE)
				->order('alias')
				->order('id', 'DESC');
		}

		protected function PrepareCreate(array & $data, array & $params = []): void {
			$data['state'] = Consts\General::STATE_ACTIVE;
		}

	}