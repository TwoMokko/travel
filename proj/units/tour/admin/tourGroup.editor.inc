<?php

	namespace Proj\Admin\Editor;

	use JetBrains\PhpStorm\NoReturn;

	use Base\DB\TableMySQLi;
	use Base\Editor\EditorMySQLi;
	use Base\Editor\Skins;
	use Proj\Admin\Units;
	use Proj\Units\Consts;

	class TourGroup extends EditorMySQLi {

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);
		}

		protected function Where(array $params): array {
			return [
				'`state` != ' . Consts\Tour::STATES['delete']
			];
		}

		protected function Order(): array {
			return [
				'`id` ASC'
			];
		}

		protected function RegTitles(): void {
			$this->titleSelect = 'Список направлений туров';
			$this->titleCreate = 'Добавить направление тура';
			$this->titleUpdate = 'Редактирование направления тура';
			$this->titleDelete = 'Удалить направление тура?';

			$this->titleDoCreate = 'Направление тура добавлено';
			$this->titleDoUpdate = 'Направление тура изменено';
			$this->titleDoDelete = 'Направление тура удалено';
		}

		protected function FieldsSelect(array $params): array {
			return [
				'id' 				=> new Skins\Browse\Text('#'),
                'state' 		    => new Skins\Browse\ValueFromArray('Состояние', Consts\Tour::STATES_RU),
                'name' 				=> new Skins\Browse\Text('Название')
			];
		}

		protected function FieldsBrowse(array $params) : array {
			return [
                'state'    	 	    => new Skins\Browse\ValueFromArray('Состояние', Consts\Tour::STATES_RU),
                'name'    		    => new Skins\Browse\Text('Заголовок'),
			];
		}

		protected function FieldsCreate(array $params): array {
			return $this->FieldsCreateAndUpdate($params);
		}

		protected function FieldsUpdate(array $params): array {
			return $this->FieldsCreateAndUpdate($params);
		}

		private function FieldsCreateAndUpdate(array $params): array {
            $states = [
                Consts\People::STATE_DRAFT => Consts\People::STATES_RU[Consts\People::STATE_DRAFT],
                Consts\People::STATE_ACTIVE => Consts\People::STATES_RU[Consts\People::STATE_ACTIVE],
                Consts\People::STATE_INACTIVE => Consts\People::STATES_RU[Consts\People::STATE_INACTIVE],
            ];

			return [
                'state' 			=> new Skins\Edit\Select('Состояние', 'form[state]',  $states),
                'name' 				=> new Skins\Edit\Text('Заголовок', 'form[name]'),
				'video' 			=> new Skins\Edit\Text('Ссылка видео', 'form[video]'),
				'photo_id' 			=> new Skins\Edit\Select('Фотоальбом', 'form[photo_id]', Units\Photo::instance()->GetAlbums()),
			];
		}

		public function PrepareOnCreate(array & $data): void {
			$data['state'] = [
				Consts\Tour::STATE_DRAFT	=> 'Черновик',
				Consts\Tour::STATE_ACTIVE	=> 'Активная',
				Consts\Tour::STATE_INACTIVE	=> 'Не активная',
			];
		}

		public function PrepareOnUpdate(int $id, array & $item, array & $data): void {
			$data['state'] = [
				Consts\Tour::STATE_DRAFT	=> 'Черновик',
				Consts\Tour::STATE_ACTIVE	=> 'Активная',
				Consts\Tour::STATE_INACTIVE	=> 'Не активная',
			];
		}
	}