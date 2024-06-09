<?php

	namespace Proj\Admin\Editor\Travel;

	require DIR_UNITS . 'travel/admin/editors/direction/direction.editor.model.inc';

	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins;
	use Proj\Admin\Model as ProjModel;
	use Proj\Units\Consts;
	use Proj\Admin\Editor\Model;

	class Direction extends Editor {

		public function __construct(int $id, string $name, /** @var Table[] $tables */ array $tables, string $title = '') {
			parent::__construct($id, $name, $tables[0], $title);

			$this->titleSelect = 'Список направлений туров';
			$this->titleBrowse = 'Просмотр направления тура';
			$this->titleCreate = 'Добавить направление тура';
			$this->titleUpdate = 'Редактирование направления тура';
			$this->titleDelete = 'Удалить направление тура?';

			$this->titleDoCreate = 'Направление тура добавлено';
			$this->titleDoUpdate = 'Направление тура изменено';
			$this->titleDoDelete = 'Направление тура удалено';

			$this->model = new Model\Travel\Direction($tables, $this->params);
		}

		protected function FieldsSelect(): array {
			return [
				'id' 				=> new Skins\Browse\Text('#'),
				'state' 		    => new Skins\Browse\ValueFromArray('Состояние', Consts\Travel::STATES_RU),
				'name' 				=> new Skins\Browse\Text('Название')
			];
		}

		protected function FieldsBrowse() : array {
			return [
				'state'    	 	    => new Skins\Browse\ValueFromArray('Состояние', Consts\Travel::STATES_RU),
				'name'    		    => new Skins\Browse\Text('Заголовок'),
			];
		}

		protected function FieldsCreate(): array {
			return $this->FieldsCreateAndUpdate();
		}

		protected function FieldsUpdate(): array {
			return $this->FieldsCreateAndUpdate();
		}

		public function PrepareOnUpdate(int $id, array & $item): void {
			$item['expense'] = $this->model->GetExpenseByDirectionId($id);
			$item['additional_expense'] = $this->model->GetAdditionalExpenseByDirectionId($id);
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
				'photo_id' 				=> new Skins\Edit\Select('Фотоальбом', 'form[photo_id]', ProjModel\Photo::instance()->GetAlbums()),
				'expense'           	=> new Skins\Edit\Table('Входит в стоимость', 'form[expense]', [
					'expense' => ['alias' => 'входит в стоимость', 'type' => 'text', 'name' => 'expense']
				]),
				'additional_expense'	=> new Skins\Edit\Table('Дополнительные расходы', 'form[additional_expense]', [
					'additional_expense' => ['alias' => 'дополнительные расходы', 'type' => 'text', 'name' => 'additional_expense']
				])
			];
		}

	}