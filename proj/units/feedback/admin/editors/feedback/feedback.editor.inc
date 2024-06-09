<?php

	namespace Proj\Admin\Editor;

	require DIR_UNITS . 'feedback/admin/editors/feedback/feedback.editor.model.inc';

	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins;
	use Proj\Admin\Editor\Model;
	use Proj\Units\Consts as ProjConsts;

	class Feedback extends Editor {

		public function __construct(int $id, string $name, Table $table, string $title = '') {
			parent::__construct($id, $name, $table, $title);

			$this->titleSelect = 'Список';
			$this->titleDelete = 'Удалить?';

			$this->titleDoDelete = 'Удалено';

			$this->model = new Model\Feedback($table, $this->params);
		}

		protected function FieldsSelect(): array {
			return [
				'id' 		=> new Skins\Browse\Text('#'),
				'state' 	=> new Skins\Browse\ValueFromArray('Состояние', ProjConsts\Feedback::STATES_RU),
				'name' 		=> new Skins\Browse\Text('Имя')
			];
		}

		protected function FieldsBrowse() : array {
			return [
				'state'     => new Skins\Browse\ValueFromArray('Состояние', ProjConsts\Feedback::STATES_RU),
				'tour_id' 	=> new Skins\Browse\Text('С какого тура'),
				'name'    	=> new Skins\Browse\Text('Имя'),
				'text'      => new Skins\Browse\Text('Текст'),
				'contact'   => new Skins\Browse\Text('Контакт')
			];
		}

		protected function ManageSelect(): array {
			return [
				function (array $item) { return $this->browse->GetLinkHrefAllow(self::ACCESS_BROWSE, 'Просмотреть', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $item['state'] == ProjConsts\Feedback::STATE_UNVERIFIED ? $this->set_state->GetLinkHrefAllow(self::ACCESS_STATE, 'Изменить', array_merge(['id' => $item['id'], 'state' => ProjConsts\Feedback::STATE_VERIFIED], $this->params)) : ''; },
			];
		}

	}