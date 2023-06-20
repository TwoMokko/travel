<?php

	namespace Proj\Admin\Editor;

	use JetBrains\PhpStorm\NoReturn;

	use Base\Action;
	use Base\Controller;
	use Base\DB\TableMySQLi;
	use Base\Editor\EditorMySQLi;
	use Base\Editor\Skins;
    use Proj\Admin\Units\Tours;
    use Proj\Units\Consts;

	class Feedback extends EditorMySQLi {
		public Action $do_verified;

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);

			$this->do_verified = new Action($this->name, 'do_verified', "/{$this->name}/do_verified?id=%id%", /* @lang JavaScript */"Base.Common.Query.SendData('/{$this->name}/do_verified', {id: %id%}, Admin.General.Render.ToMain); return false;");

			Controller::instance()->view->Push($this->do_verified, [$this, 'DoVerified']);
		}

		protected function Where(array $params): array {
			return [
				'`state` != ' . Consts\Feedback::STATES['error']
			];
		}

		protected function Order(): array {
			return [
				'`date_create` DESC',
				'`id` ASC'
			];
		}

//		protected function Calc(): array {
//			return [
//				"*, CONCAT(`hash`, '.', `id`, '.', `ext`) AS `cover`"
//			];
//		}

		protected function Manage(): array {
			return [
				function (array $params, array $item) { return $this->do_verified->GetLink('Проверено', ['id' => $item['id']]); },
				function (array $params, array $item) { return $this->browse->GetLink('Просмотреть', ['id' => $item['id']]); }
			];
		}

		protected function RegTitles(): void {
			$this->titleSelect = 'Список';
	//		$this->titleCreate = 'Добавить человека';
	//		$this->titleUpdate = 'Редактирование человека';
			$this->titleDelete = 'Удалить?';

	//		$this->titleDoCreate = 'Человек добавлена';
	//		$this->titleDoUpdate = 'Человек изменена';
			$this->titleDoDelete = 'Удалено';
		}

        protected function PrepareOnBrowse(int $id, array &$item, array &$data): void {
            if (!$item['tour_id']) {$item['tour_id'] = 'С футера'; return; }
            $tour = Tours::instance()->GetTour($item['tour_id']);
            $name = Tours::instance()->GetNameGroupTour($tour['gid']);
            $item['tour_id'] = "{$name} {$tour['date']}";

        }

        protected function FieldsSelect(array $params): array {
			return [
				'id' 		=> new Skins\Browse\Text('#'),
				'state' 	=> new Skins\Browse\ValueFromArray('Состояние', Consts\Feedback::STATES_RU),
				'name' 		=> new Skins\Browse\Text('Имя')
			];
		}

		protected function FieldsBrowse(array $data) : array {
			return [
				'state'     => new Skins\Browse\ValueFromArray('Состояние', Consts\Feedback::STATES_RU),
				'tour_id' 	=> new Skins\Browse\Text('С какого тура'),
				'name'    	=> new Skins\Browse\Text('Имя'),
				'text'      => new Skins\Browse\Text('Текст'),
				'contact'   => new Skins\Browse\Text('Контакт')
			];
		}

		#[NoReturn] public function DoVerified(): void {
			$id = GetInt('id');
			$old_state = Consts\Feedback::STATE_UNVERIFIED;
			$this->table->Update(['state' => Consts\Feedback::STATE_VERIFIED], "(`state` = {$old_state}) AND (`id` = {$id})");

			$this->fieldsSelect = $this->FieldsSelect([]);
			SendJSONSuccess(['message' => $this->titleDoUpdate, 'html' => $this->Select()]);
		}

	}