<?php

	namespace Proj\Admin\Editor;

	require DIR_UNITS . 'general/admin/editors/image/image.editor.model.inc';

	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins;
	use Proj\Units\Consts;
	use Proj\Admin\Editor\Model;

	class Image extends Editor {

		public function __construct(int $id, string $name, Table $table, string $title = '') {
			parent::__construct($id, $name, $table, $title);

			$this->titleSelect = 'Список изображений';
			$this->titleBrowse = 'Просмотр изображения';
			$this->titleCreate = 'Добавить изображение';
			$this->titleUpdate = 'Редактирование изображения';
			$this->titleDelete = 'Удалить изображение?';

			$this->titleDoCreate = 'Изображение добавлено';
			$this->titleDoUpdate = 'Изображение изменено';
			$this->titleDoDelete = 'Изображение удалено';

            $this->model = new Model\Image($table, $this->params);
        }

		protected function FieldsSelect(): array {
				return [
				'id' 		    => new Skins\Browse\Text('#'),
				'alias' 		=> new Skins\Browse\Text('Псевдоним'),
				'description' 	=> new Skins\Browse\Text('Описание')
			];
		}

		protected function FieldsBrowse(): array {
			return [
				'alias'    	    => new Skins\Browse\Text('Псевдоним'),
				'description'   => new Skins\Browse\Text('Описание'),
				'cover'         => new Skins\Browse\Image('Картинка', Consts\General::PATH_IMAGE_RELATIVE)
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