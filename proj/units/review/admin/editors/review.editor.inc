<?php

	namespace Proj\Admin\Editor\Review;

	require DIR_UNITS . 'review/admin/editors/review.editor.model.inc';

	use Base\Controller;
	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins;
	use Proj\Admin\Editor\Model;
	use Proj\Admin\Units\Tours;
	use Proj\Units\Consts;

	class Review extends Editor {

		public function __construct(string $name, Table $table) {

			parent::__construct($name);

			$this->titleSelect = 'Отзывы';
			$this->titleDelete = 'Удалить отзыв?';

			$this->titleDoDelete = 'Отзыв удален';
			$this->btnUpdate = 'Опубликовать';
			$this->titleDoUpdate = 'Опубликовано';

			$this->model = new Model\Review($table, $this->params);
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
				'id' 		=> new Skins\Browse\Text('#'),
				'gid' 		=> new Skins\Browse\ValueFromArray('К какому направлению относится', Tours::instance()->GetGroupTour()),
				'state' 	=> new Skins\Browse\ValueFromArray('Состояние', Consts\Reviews::STATES_RU),
				'name' 		=> new Skins\Browse\Text('Имя')
			];
		}

		protected function FieldsBrowse() : array {
			return [
				'state'     => new Skins\Browse\ValueFromArray('Состояние', Consts\Reviews::STATES_RU),
				'name'    	=> new Skins\Browse\Text('Имя'),
				'text'      => new Skins\Browse\Text('Текст'),
			];
		}

		protected function ManageSelect(): array {
			return [
				function (array $item) { return $this->update->GetLink('Опубликовать', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->browse->GetLink('Просмотреть', array_merge(['id' => $item['id']], $this->params)); },
			];
		}

        protected function FieldsUpdate(): array {
            return [
                'gid'           => new Skins\Edit\Select('К какому направлению относится', 'form[gid]', ['Выберите'] + Tours::instance()->GetGroupTour()),
				'name'          => new Skins\Edit\Text('Имя', 'form[name]'),
				'text'          => new Skins\Edit\TextArea('Текст', 'form[text]')
            ];
        }

	}