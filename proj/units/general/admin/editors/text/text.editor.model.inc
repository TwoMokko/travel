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
				->order('id');
		}

//		public function Create(array $data): bool {
//			$data = GetParam('form', []);
//			$id = $this->table->Insert($data);
//
////			if ($_FILES['form']['tmp_name']['cover']) {
////				$data_file = [$hash, $ext] = $this->SaveFile($id);
////				if (!$data_file) return false;
////				$this->table->Update(['hash' => $hash, 'ext' => $ext], "`id` = {$id}");
////			}
//
//			return true;
//		}

		public function Update(array $data, int $id): bool {
			$id = (int)GetParam('id', 0);
			$data = GetParam('form', []);

			$this->table->Update($data, "`id` = {$id}");

			return true;
		}

	}