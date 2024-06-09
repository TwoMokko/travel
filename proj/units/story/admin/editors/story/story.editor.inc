<?php

	namespace Proj\Admin\Editor;

	require DIR_UNITS . 'story/admin/editors/story/story.editor.model.inc';

	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins;
	use Proj\Units\Consts;
	use Proj\Admin\Editor\Model;

	class Story extends Editor {

		public function __construct(int $id, string $name, Table $table, string $title = '') {
			parent::__construct($id, $name, $table, $title);

			$this->titleSelect = 'Список историй';
			$this->titleCreate = 'Добавить историю';
			$this->titleUpdate = 'Редактирование истории';
			$this->titleDelete = 'Удалить история?';

			$this->titleDoCreate = 'История добавлена';
			$this->titleDoUpdate = 'История изменена';
			$this->titleDoDelete = 'История удалена';

			$this->model = new Model\Story($table, $this->params);
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
				'cover'     => new Skins\Browse\Image('Картинка', Consts\Story::PATH_COVER_PREVIEW_RELATIVE)
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
				Consts\Story::STATE_DRAFT => Consts\Story::STATES_RU[Consts\Story::STATE_DRAFT],
				Consts\Story::STATE_ACTIVE => Consts\Story::STATES_RU[Consts\Story::STATE_ACTIVE],
				Consts\Story::STATE_INACTIVE => Consts\Story::STATES_RU[Consts\Story::STATE_INACTIVE],
			];

			return [
				'state' 	=> new Skins\Edit\Select('Состояние','form[state]',  $states),
				'header' 	=> new Skins\Edit\Text('Заголовок', 'form[header]'),
				'text' 		=> new Skins\Edit\TextArea('Текст', 'form[text]'),
				'cover' 	=> new Skins\Edit\File('Фотография','form[cover]',  'Выберите фотографию', '.jpg, .jpeg, .png')
			];
		}

	}