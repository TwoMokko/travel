<?php

	namespace Proj\Admin\Editor\General;

	require DIR_UNITS . 'general/admin/editors/image/image.editor.model.inc';

	use Base\Controller;
	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins;
	use Proj\Admin\Editor\Model;
	use Proj\Units\Consts;

	class Image extends Editor {

		public function __construct(string $name, Table $table) {
			parent::__construct($name);

			$this->titleSelect = 'Список изображений';
			$this->titleCreate = 'Добавить изображение';
			$this->titleUpdate = 'Редактирование изображения';
//			$this->titleDelete = 'Удалить изображение?';

			$this->titleDoCreate = 'Изображение добавлено';
			$this->titleDoUpdate = 'Изображение изменено';
//			$this->titleDoDelete = 'Изображение удалено';

			$this->model = new Model\Image($table, $this->params);
		}

		protected function SetHandlers(): void {
			Controller::instance()->view->Push($this->select, [$this, 'OnSelect']);
			Controller::instance()->view->Push($this->browse, [$this, 'OnBrowse']);
			Controller::instance()->view->Push($this->create, [$this, 'OnCreate']);
			Controller::instance()->view->Push($this->update, [$this, 'OnUpdate']);

			Controller::instance()->view->Push($this->do_create, [$this, 'DoCreate']);
			Controller::instance()->view->Push($this->do_update, [$this, 'DoUpdate']);
//			Controller::instance()->view->Push($this->set_state, [$this, 'SetState']);
		}

		protected function NavigateSelect(): array {
            return [
                function () { return $this->create->GetLink('Добавить изображение', ['page' => 1]); }
            ];
        }

		protected function FieldsSelect(): array {
			return [
				'id' 		    => new Skins\Browse\Text('#'),
				'alias' 		=> new Skins\Browse\Text('Псевдоним'),
				'description' 	=> new Skins\Browse\Text('Описание')
			];
		}

		protected function FieldsBrowse() : array {
			return [
				'alias'    	    => new Skins\Browse\Text('Псевдоним'),
				'description'   => new Skins\Browse\Text('Описание'),
				'cover'         => new Skins\Browse\Image('Картинка', Consts\General::PATH_IMAGE_RELATIVE)
			];
		}

		protected function ManageSelect(): array {
			return [
				function (array $item) { return $this->update->GetLink('Изменить', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->browse->GetLink('Просмотреть', array_merge(['id' => $item['id']], $this->params)); },
//				function (array $item) { return $this->set_state->GetLink('Проверена', array_merge(['id' => $item['id'], 'state' => Consts\General::STATE_DELETE], $this->params)); }
			];
		}

		protected function FieldsCreate(): array {
            return [
                'alias' 		    => new Skins\Edit\Text('Псевдоним (неизменяемое)', 'form[alias]'),
                'description' 		=> new Skins\Edit\Text('Описание', 'form[description]'),
                'cover' 	        => new Skins\Edit\File('Фотография', 'form[cover]', 'Выберите фотографию', '.jpg, .jpeg, .png')
            ];
		}

		protected function FieldsUpdate(): array {
            return [
                'alias' 		    => new Skins\Browse\Text('Псевдоним'),
                'description' 		=> new Skins\Edit\Text('Описание', 'form[description]'),
                'cover' 	        => new Skins\Edit\File('Фотография', 'form[cover]', 'Выберите фотографию', '.jpg, .jpeg, .png')
            ];
		}

	}