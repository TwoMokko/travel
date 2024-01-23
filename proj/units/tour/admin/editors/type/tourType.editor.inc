<?php

	namespace Proj\Admin\Editor\Tour;

	require DIR_UNITS . 'tour/admin/editors/type/tourType.editor.model.inc';

	use Base\Controller;
	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins;
	use Proj\Admin\Editor\Model;
	use Proj\Units\Consts;

	class TourType extends Editor {

		public function __construct(string $name, Table $table) {
			parent::__construct($name);

			$this->titleSelect = 'Список видов тура';
			$this->titleCreate = 'Добавить вид тура';
			$this->titleUpdate = 'Редактирование вида тура';
			$this->titleDelete = 'Удалить вид тура?';

			$this->titleDoCreate = 'Вид тура добавлена';
			$this->titleDoUpdate = 'Вид тура изменена';
			$this->titleDoDelete = 'Вид тура удалена';

			$this->model = new Model\TourType($table, $this->params);
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
				'id' 			=> new Skins\Browse\Text('#'),
				'state' 		=> new Skins\Browse\ValueFromArray('Состояние', Consts\Tour::STATES_RU),
				'name' 			=> new Skins\Browse\Text('Название')
			];
		}

		protected function FieldsBrowse() : array {
			return [
				'state'    	 	=> new Skins\Browse\ValueFromArray('Состояние', Consts\Tour::STATES_RU),
				'name'    		=> new Skins\Browse\Text('Заголовок'),
				'description' 	=> new Skins\Browse\Text('Текст'),
				'cover'     	=> new Skins\Browse\Image('Картинка', Consts\Tour::PATH_TYPE_PREVIEW_RELATIVE)
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
				Consts\People::STATE_DRAFT => Consts\People::STATES_RU[Consts\People::STATE_DRAFT],
				Consts\People::STATE_ACTIVE => Consts\People::STATES_RU[Consts\People::STATE_ACTIVE],
				Consts\People::STATE_INACTIVE => Consts\People::STATES_RU[Consts\People::STATE_INACTIVE],
			];

			return [
				'state' 			=> new Skins\Edit\Select('Состояние', 'form[state]',  $states),
				'name' 				=> new Skins\Edit\Text('Заголовок', 'form[name]'),
				'description' 		=> new Skins\Edit\TextArea('Текст', 'form[description]'),
				'cover' 			=> new Skins\Edit\File('Фотография','form[cover]',  'Выберите фотографию', '.jpg, .jpeg, .png')
			];
		}

		protected function FieldsCreate(): array {
			return $this->FieldsCreateAndUpdate();
		}

		protected function FieldsUpdate(): array {
			return $this->FieldsCreateAndUpdate();
		}
	}