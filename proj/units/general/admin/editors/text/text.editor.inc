<?php

	namespace Proj\Admin\Editor\General;

	require DIR_UNITS . 'general/admin/editors/text/text.editor.model.inc';

	use Base\Controller;
	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins;
	use Proj\Admin\Editor\Model;
	use Proj\Units\Consts;

	class Text extends Editor {

		public function __construct(string $name, Table $table) {
			parent::__construct($name);

			$this->titleSelect = 'Список текстов';
			$this->titleCreate = 'Добавить текст';
			$this->titleUpdate = 'Редактирование текста';
			$this->titleDelete = 'Удалить текст?';

			$this->titleDoCreate = 'Текст добавлено';
			$this->titleDoUpdate = 'Текст изменено';
			$this->titleDoDelete = 'Текст удален';

			$this->model = new Model\Text($table, $this->params);
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

		protected function NavigateSelect(): array {
            return [
				function () { return $this->create->GetLink('Добавить текст', ['page' => 1]); }
            ];
        }

		protected function FieldsSelect(): array {
			return [
				'id' 			=> new Skins\Browse\Text('#'),
				'alias' 		=> new Skins\Browse\Text('Псевдоним'),
				'description' 	=> new Skins\Browse\Text('Описание')
			];
		}

		protected function FieldsBrowse() : array {
			return [
				'alias'    			=> new Skins\Browse\Text('Псевдоним'),
				'description'    	=> new Skins\Browse\Text('Описание'),
				'text'    			=> new Skins\Browse\Text('Текст')
			];
		}

		protected function ManageSelect(): array {
			return [
				function (array $item) { return $this->update->GetLink('Изменить', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->browse->GetLink('Просмотреть', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->delete->GetLink('Удалить', array_merge(['id' => $item['id']], $this->params)); },
			];
		}

		protected function FieldsCreate(): array {
            return [
				'alias' 			=> new Skins\Edit\Text('Имя', 'form[alias]'),
				'description' 		=> new Skins\Edit\TextArea('Описание', 'form[description]'),
				'text' 				=> new Skins\Edit\TextArea('Текст', 'form[text]')
            ];
		}

		protected function FieldsUpdate(): array {
            return [
				'alias' 	=> new Skins\Browse\Text('Имя'),
				'description' 		=> new Skins\Edit\TextArea('Описание', 'form[description]'),
				'text' 		=> new Skins\Edit\TextArea('Текст', 'form[text]')
            ];
		}

		protected function PrepareDoCreate(& $data): void {
			$data['state'] = Consts\General::STATE_ACTIVE;
		}

	}