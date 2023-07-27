<?php

	namespace Proj\Admin\Editor\Story;

	require DIR_UNITS . 'story/admin/editors/story.editor.model.inc';

	use Base\Controller;
	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins;
	use Proj\Admin\Editor\Model;
	use Proj\Units\Consts;

	class Story extends Editor {

		public function __construct(string $name, Table $table) {
			parent::__construct($name);

			$this->titleSelect = 'Список историй';
			$this->titleCreate = 'Добавить историю';
			$this->titleUpdate = 'Редактирование истории';
			$this->titleDelete = 'Удалить история?';

			$this->titleDoCreate = 'История добавлена';
			$this->titleDoUpdate = 'История изменена';
			$this->titleDoDelete = 'История удалена';

			$this->model = new Model\Story($table, $this->params);
		}

		protected function SetHandlers(): void {
			Controller::instance()->view->Push($this->select, [$this, 'OnSelect']);
			Controller::instance()->view->Push($this->browse, [$this, 'OnBrowse']);
			Controller::instance()->view->Push($this->create, [$this, 'OnCreate']);
			Controller::instance()->view->Push($this->update, [$this, 'OnUpdate']);

			Controller::instance()->view->Push($this->do_create, [$this, 'DoCreate']);
			Controller::instance()->view->Push($this->do_update, [$this, 'DoUpdate']);
			Controller::instance()->view->Push($this->do_delete, [$this, 'DoDelete']);
//			Controller::instance()->view->Push($this->set_state, [$this, 'SetState']);
		}

		protected function FieldsSelect(): array {
			return [
				'id' 		=> new Skins\Browse\Text('#'),
				'state' 	=> new Skins\Browse\ValueFromArray('Состояние', Consts\Story::STATES_RU),
				'header' 	=> new Skins\Browse\Text('Заголовок')
			];
		}

		protected function FieldsBrowse() : array {
			return [
				'state'     => new Skins\Browse\ValueFromArray('Состояние', Consts\Story::STATES_RU),
				'header'    => new Skins\Browse\Text('Заголовок'),
				'text'      => new Skins\Browse\Text('Текст'),
				'cover'     => new Skins\Browse\Image('Картинка', Consts\Story::PATH_COVER_RELATIVE)
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
				'state' 	=> new Skins\Edit\Select('Состояние','form[state]',  $states),
				'header' 	=> new Skins\Edit\Text('Заголовок', 'form[header]'),
				'text' 		=> new Skins\Edit\TextArea('Текст', 'form[text]'),
				'cover' 	=> new Skins\Edit\File('Фотография','form[cover]',  'Выберите фотографию', '.jpg, .jpeg, .png')
			];
		}

		protected function FieldsCreate(): array {
			return $this->FieldsCreateAndUpdate();
		}

		protected function FieldsUpdate(): array {
			return $this->FieldsCreateAndUpdate();
		}
	}