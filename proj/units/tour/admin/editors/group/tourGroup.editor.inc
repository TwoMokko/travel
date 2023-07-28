<?php

	namespace Proj\Admin\Editor\Tour;

	require DIR_UNITS . 'tour/admin/editors/group/tourGroup.editor.model.inc';

	use Base\Controller;
	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins;
	use Proj\Admin\Editor\Model;
	use Proj\Admin\Units;
	use Proj\Units\Consts;

	class TourGroup extends Editor {

		public function __construct(string $name, array $tables) {
			parent::__construct($name);

			$this->titleSelect = 'Список направлений туров';
			$this->titleCreate = 'Добавить направление тура';
			$this->titleUpdate = 'Редактирование направления тура';
			$this->titleDelete = 'Удалить направление тура?';

			$this->titleDoCreate = 'Направление тура добавлено';
			$this->titleDoUpdate = 'Направление тура изменено';
			$this->titleDoDelete = 'Направление тура удалено';

			$this->model = new Model\TourGroup($tables, $this->params);
		}

		protected function SetHandlers(): void {
			Controller::instance()->view->Push($this->select, [$this, 'OnSelect']);
			Controller::instance()->view->Push($this->browse, [$this, 'OnBrowse']);
			Controller::instance()->view->Push($this->create, [$this, 'OnCreate']);
			Controller::instance()->view->Push($this->update, [$this, 'OnUpdate']);

			Controller::instance()->view->Push($this->do_create, [$this, 'DoCreate']);
			Controller::instance()->view->Push($this->do_update, [$this, 'DoUpdate']);
			Controller::instance()->view->Push($this->do_delete, [$this, 'DoDelete']);
		}

		protected function FieldsSelect(): array {
			return [
				'id' 				=> new Skins\Browse\Text('#'),
				'state' 		    => new Skins\Browse\ValueFromArray('Состояние', Consts\Tour::STATES_RU),
				'name' 				=> new Skins\Browse\Text('Название')
			];
		}

		protected function FieldsBrowse() : array {
			return [
				'state'    	 	    => new Skins\Browse\ValueFromArray('Состояние', Consts\Tour::STATES_RU),
				'name'    		    => new Skins\Browse\Text('Заголовок'),
			];
		}

		protected function ManageSelect(): array {
			return [
				function (array $item) { return $this->update->GetLink('Изменить', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->browse->GetLink('Просмотреть', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->delete->GetLink('Удалить', array_merge(['id' => $item['id']], $this->params)); },
			];
		}

		public function PrepareOnUpdate(int $id, array & $item): void {
			$item['expense'] = $this->model->GetExpenseByGroupId($id);
			$item['additional_expense'] = $this->model->GetAdditionalExpenseByGroupId($id);
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

		protected function FieldsCreate(): array {
			return $this->FieldsCreateAndUpdate();
		}

		protected function FieldsUpdate(): array {
			return $this->FieldsCreateAndUpdate();
		}
	}