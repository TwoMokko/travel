<?php

	namespace Proj\Admin\Editor\Feedback;

	require DIR_UNITS . 'feedback/admin/editors/feedback.editor.model.inc';

	use Base\Controller;
	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins;
	use Proj\Admin\Editor\Model;
	use Proj\Admin\Units\Tours;
	use Proj\Units\Consts;

	class Feedback extends Editor {

		public function __construct(string $name, Table $table) {
			parent::__construct($name);

			$this->titleSelect = 'Список';
			$this->titleDelete = 'Удалить?';

			$this->titleDoDelete = 'Удалено';

			$this->model = new Model\Feedback($table, $this->params);
		}

		protected function SetHandlers(): void {
			Controller::instance()->view->Push($this->select, [$this, 'OnSelect']);
			Controller::instance()->view->Push($this->browse, [$this, 'OnBrowse']);
//			Controller::instance()->view->Push($this->create, [$this, 'OnCreate']);
//			Controller::instance()->view->Push($this->update, [$this, 'OnUpdate']);

//			Controller::instance()->view->Push($this->do_create, [$this, 'DoCreate']);
//			Controller::instance()->view->Push($this->do_update, [$this, 'DoUpdate']);
//			Controller::instance()->view->Push($this->do_delete, [$this, 'DoDelete']);
			Controller::instance()->view->Push($this->set_state, [$this, 'SetState']);
		}

//		protected function PrepareOnBrowse(int $id, array &$item, array &$data): void {
//			if (!$item['tour_id']) {$item['tour_id'] = 'С футера'; return; }
//			$tour = Tours::instance()->GetTour($item['tour_id']);
//			$name = Tours::instance()->GetNameGroupTour($tour['gid']);
//			$item['tour_id'] = "{$name} {$tour['date']}";
//
//		}

		protected function FieldsSelect(): array {
			return [
				'id' 		=> new Skins\Browse\Text('#'),
				'state' 	=> new Skins\Browse\ValueFromArray('Состояние', Consts\Feedback::STATES_RU),
				'name' 		=> new Skins\Browse\Text('Имя')
			];
		}

		protected function FieldsBrowse() : array {
			return [
				'state'     => new Skins\Browse\ValueFromArray('Состояние', Consts\Feedback::STATES_RU),
				'tour_id' 	=> new Skins\Browse\Text('С какого тура'),
				'name'    	=> new Skins\Browse\Text('Имя'),
				'text'      => new Skins\Browse\Text('Текст'),
				'contact'   => new Skins\Browse\Text('Контакт')
			];
		}

		protected function ManageSelect(): array {
			return [
				function (array $item) { return $this->browse->GetLink('Просмотреть', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return ($item['state'] == Consts\Feedback::STATE_UNVERIFIED) ? $this->set_state->GetLink('Проверить', array_merge(['id' => $item['id'], 'state' => Consts\Feedback::STATE_VERIFIED], $this->params)) : ''; }
			];
		}

	}