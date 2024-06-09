<?php

	namespace Proj\Admin\Editor\Travel;

	require DIR_UNITS . 'travel/admin/editors/type/type.editor.model.inc';

	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins;
	use Proj\Units\Consts;
	use Proj\Admin\Editor\Model;

	class Type extends Editor {

		public function __construct(int $id, string $name, Table $table, string $title = '') {
			parent::__construct($id, $name, $table, $title);

			$this->titleSelect = 'Список видов тура';
			$this->titleBrowse = 'Просмотр вида тура';
			$this->titleCreate = 'Добавить вид тура';
			$this->titleUpdate = 'Редактирование вида тура';
			$this->titleDelete = 'Удалить вид тура?';

			$this->titleDoCreate = 'Вид тура добавлена';
			$this->titleDoUpdate = 'Вид тура изменена';
			$this->titleDoDelete = 'Вид тура удалена';

			$this->model = new Model\Travel\Type($table, $this->params);
		}

		protected function FieldsSelect(): array {
			return [
				'id' 			=> new Skins\Browse\Text('#'),
				'state' 		=> new Skins\Browse\ValueFromArray('Состояние', Consts\Travel::STATES_RU),
				'name' 			=> new Skins\Browse\Text('Название')
			];
		}

		protected function FieldsBrowse() : array {
			return [
				'state'    	 	=> new Skins\Browse\ValueFromArray('Состояние', Consts\Travel::STATES_RU),
				'name'    		=> new Skins\Browse\Text('Заголовок'),
				'description' 	=> new Skins\Browse\Text('Текст'),
				'cover'     	=> new Skins\Browse\Image('Картинка', Consts\Travel::PATH_TYPE_PREVIEW_RELATIVE)
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
				Consts\Travel::STATE_DRAFT => Consts\Travel::STATES_RU[Consts\Travel::STATE_DRAFT],
				Consts\Travel::STATE_ACTIVE => Consts\Travel::STATES_RU[Consts\Travel::STATE_ACTIVE],
				Consts\Travel::STATE_INACTIVE => Consts\Travel::STATES_RU[Consts\Travel::STATE_INACTIVE],
			];

			return [
				'state' 			=> new Skins\Edit\Select('Состояние', 'form[state]',  $states),
				'name' 				=> new Skins\Edit\Text('Заголовок', 'form[name]'),
				'description' 		=> new Skins\Edit\TextArea('Текст', 'form[description]'),
				'cover' 			=> new Skins\Edit\File('Фотография','form[cover]',  'Выберите фотографию', '.jpg, .jpeg, .png')
			];
		}

	}