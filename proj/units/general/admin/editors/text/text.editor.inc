<?php

	namespace Proj\Admin\Editor;

	require DIR_UNITS . 'general/admin/editors/text/text.editor.model.inc';

	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins;
	use Proj\Admin\Editor\Model;

	class Text extends Editor {

		public function __construct(int $id, string $name, Table $table, string $title = '') {
			parent::__construct($id, $name, $table, $title);

			$this->titleSelect = 'Список текстов';
			$this->titleBrowse = 'Просмотр текта';
			$this->titleCreate = 'Добавить текст';
			$this->titleUpdate = 'Редактирование текста';
			$this->titleDelete = 'Удалить текст?';

			$this->titleDoCreate = 'Текст добавлен';
			$this->titleDoUpdate = 'Текст изменён';
			$this->titleDoDelete = 'Текст удалён';

            $this->model = new Model\Text($table, $this->params);
        }

		protected function FieldsSelect(): array {
			return [
				'id' 			    => new Skins\Browse\Text('#'),
				'alias' 		    => new Skins\Browse\Text('Псевдоним'),
				'description' 	    => new Skins\Browse\Text('Описание')
			];
		}

		protected function FieldsBrowse(): array {
			return [
				'alias'    			=> new Skins\Browse\Text('Псевдоним'),
				'description'    	=> new Skins\Browse\Text('Описание'),
				'text'    			=> new Skins\Browse\Text('Текст')
			];
		}

		protected function FieldsCreate(): array {
			return [
				'alias' 			    => new Skins\Edit\Text('Имя', 'form[alias]'),
				'description' 		    => new Skins\Edit\TextArea('Описание', 'form[description]'),
				'text' 				    => new Skins\Edit\TextArea('Текст', 'form[text]')
			];
		}

		protected function FieldsUpdate(): array {
			return [
				'alias' 	        => new Skins\Browse\Text('Имя'),
				'description' 	    => new Skins\Edit\TextArea('Описание', 'form[description]'),
				'text' 	    	    => new Skins\Edit\TextArea('Текст', 'form[text]')
			];
		}

    }