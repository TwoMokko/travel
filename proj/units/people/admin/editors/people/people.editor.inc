<?php

	namespace Proj\Admin\Editor;

	require DIR_UNITS . 'people/admin/editors/people/people.editor.model.inc';

	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins;
	use Proj\Units\Consts;
	use Proj\Admin\Editor\Model;

	class People extends Editor {

		public function __construct(int $id, string $name, Table $table, string $title = '') {
			parent::__construct($id, $name, $table, $title);

			$this->titleSelect = 'Список людей';
			$this->titleCreate = 'Добавить человека';
			$this->titleUpdate = 'Редактирование человека';
			$this->titleDelete = 'Удалить человека?';

			$this->titleDoCreate = 'Человек добавлен';
			$this->titleDoUpdate = 'Человек изменен';
			$this->titleDoDelete = 'Человек удален';

            $this->model = new Model\People($table, $this->params);
        }

		protected function FieldsSelect(): array {
			return [
				'id' 		=> new Skins\Browse\Text('#'),
				'state' 	=> new Skins\Browse\ValueFromArray('Состояние', Consts\People::STATES_RU),
				'name' 		=> new Skins\Browse\Text('Имя')
			];
		}

		protected function FieldsBrowse(): array {
			return [
				'state'     => new Skins\Browse\ValueFromArray('Состояние', Consts\People::STATES_RU),
				'name'    	=> new Skins\Browse\Text('Имя'),
				'text'      => new Skins\Browse\Text('Текст'),
				'number'    => new Skins\Browse\Text('Номер'),
				'link_vk'   => new Skins\Browse\Text('Вконтакте'),
				'link_wa'   => new Skins\Browse\Text('ВотсАпп'),
				'cover'     => new Skins\Browse\Image('Картинка', Consts\People::PATH_AVATAR_RELATIVE)
			];
		}

		protected function FieldsCreate(): array {
			return $this->FieldsCreateAndUpdate();
		}

		protected function FieldsUpdate(): array {
			return $this->FieldsCreateAndUpdate();
		}

		private function FieldsCreateAndUpdate(): array {
			$states = [
				Consts\People::STATE_DRAFT => Consts\People::STATES_RU[Consts\People::STATE_DRAFT],
				Consts\People::STATE_ACTIVE => Consts\People::STATES_RU[Consts\People::STATE_ACTIVE],
				Consts\People::STATE_INACTIVE => Consts\People::STATES_RU[Consts\People::STATE_INACTIVE],
			];

			return [
				'state' 	=> new Skins\Edit\Select('Состояние', 'form[state]', $states),
				'name' 		=> new Skins\Edit\Text('Имя', 'form[name]'),
				'text' 		=> new Skins\Edit\TextArea('Текст', 'form[text]'),
				'number' 	=> new Skins\Edit\Text('Номер', 'form[number]'),
				'link_vk' 	=> new Skins\Edit\Text('Вконтакте', 'form[link_vk]'),
				'link_wa' 	=> new Skins\Edit\Text('ВотсАпп', 'form[link_wa]'),
				'cover' 	=> new Skins\Edit\File('Фотография', 'form[cover]', 'Выберите фотографию', '.jpg, .jpeg, .png')
			];
		}

    }