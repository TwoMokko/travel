<?php

	namespace Proj\Admin\Editor\Tour;

	require DIR_UNITS . 'tour/admin/editors/tour/tour.editor.model.inc';

	use Base\Controller;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins;
	use Proj\Admin\Editor\Model;
	use Proj\Admin\Units;
	use Proj\Units\Consts;

	class Tour extends Editor {

		public function __construct(string $name, array $tables) {
			parent::__construct($name);

			$this->titleSelect = 'Список туров';
			$this->titleCreate = 'Добавить тур';
			$this->titleUpdate = 'Редактирование тура';
			$this->titleDelete = 'Удалить тур?';

			$this->titleDoCreate = 'Тур добавлен';
			$this->titleDoUpdate = 'Тур изменен';
			$this->titleDoDelete = 'Тур удален';

			$this->model = new Model\Tour($tables, $this->params);
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
				'state' 			=> new Skins\Browse\ValueFromArray('Состояние', Consts\Tour::STATES_RU),
				'date'    			=> new Skins\Browse\Text('Дата'),
				'name' 				=> new Skins\Browse\Text('Название')
			];
		}

		protected function FieldsBrowse() : array {
			return [
				'state'     		=> new Skins\Browse\ValueFromArray('Состояние', Consts\Tour::STATES_RU),
				'name'    			=> new Skins\Browse\Text('Заголовок'),
				'date'    			=> new Skins\Browse\Text('Дата'),
				'description'      	=> new Skins\Browse\Text('Описание'),
				'cover'     		=> new Skins\Browse\Image('Картинка', Consts\Tour::PATH_TOUR_RELATIVE)
			];
		}

		protected function ManageSelect(): array {
			return [
				function (array $item) { return $this->update->GetLink('Изменить', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->browse->GetLink('Просмотреть', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->delete->GetLink('Удалить', array_merge(['id' => $item['id']], $this->params)); },
			];
		}

		private function FieldsCreateAndUpdate(): array {
			$states = [
				Consts\Tour::STATE_DRAFT => Consts\Tour::STATES_RU[Consts\Tour::STATE_DRAFT],
				Consts\Tour::STATE_ACTIVE => Consts\Tour::STATES_RU[Consts\Tour::STATE_ACTIVE],
				Consts\Tour::STATE_INACTIVE => Consts\Tour::STATES_RU[Consts\Tour::STATE_INACTIVE],
			];

			return [
				'state' 			=> new Skins\Edit\Select('Состояние', 'form[state]', $states),
				'gid' 			    => new Skins\Edit\Select('Заголовок', 'form[gid]', Units\Tours::instance()->GetGroupTour()),
				'date' 				=> new Skins\Edit\Text('Дата', 'form[date]'),
				'description' 		=> new Skins\Edit\TextArea('Описание', 'form[description]'),
				'tid' 				=> new Skins\Edit\Select('Тип тура', 'form[tid]', Units\Tours::instance()->GetTypes()),
				'price' 			=> new Skins\Edit\Text('Цена', 'form[price]'),
				'duration' 			=> new Skins\Edit\Text('Длительность (цифрой)', 'form[duration]'),
				'cover' 			=> new Skins\Edit\File('Фотография', 'form[cover]', 'Выберите фотографию', '.jpg, .jpeg, .png'),
				'program'           => new Skins\Edit\Table('Маршрут', 'form[program]', [
					'day' => ['alias' => 'день', 'type' => 'number', 'name' => 'day'],
					'description' => ['alias' => 'описание', 'type' => 'textarea', 'name' => 'description']
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