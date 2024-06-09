<?php

	namespace Proj\Admin\Editor\Travel;

	require DIR_UNITS . 'travel/admin/editors/tour/tour.editor.model.inc';

	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins;
	use Proj\Units\Consts;
	use Proj\Admin\Editor\Model;
	use Proj\Admin\Model as ProjModel;

	class Tour extends Editor {

		public function __construct(int $id, string $name, /** @var Table[] $tables */ $tables, string $title = '') {
			parent::__construct($id, $name, $tables[0], $title);

			$this->titleSelect = 'Список туров';
			$this->titleBrowse = 'Просмотр тура';
			$this->titleCreate = 'Добавить тур';
			$this->titleUpdate = 'Редактирование тура';
			$this->titleDelete = 'Удалить тур?';

			$this->titleDoCreate = 'Тур добавлен';
			$this->titleDoUpdate = 'Тур изменен';
			$this->titleDoDelete = 'Тур удален';

			$this->model = new Model\Travel\Tour($tables, $this->params);
		}

		protected function FieldsSelect(): array {
			return [
				'id' 				=> new Skins\Browse\Text('#'),
				'state' 			=> new Skins\Browse\ValueFromArray('Состояние', Consts\Travel::STATES_RU),
				'date'    			=> new Skins\Browse\Text('Дата'),
				'name' 				=> new Skins\Browse\Text('Название')
			];
		}

		protected function FieldsBrowse() : array {
			return [
				'state'     		=> new Skins\Browse\ValueFromArray('Состояние', Consts\Travel::STATES_RU),
				'name'    			=> new Skins\Browse\Text('Заголовок'),
				'date'    			=> new Skins\Browse\Text('Дата'),
				'description'      	=> new Skins\Browse\Text('Описание'),
				'cover'     		=> new Skins\Browse\Image('Картинка', Consts\Travel::PATH_TOUR_ORIGINAL_RELATIVE)
			];
		}

		protected function FieldsCreate(): array {
			return $this->FieldsCreateAndUpdate();
		}

		protected function FieldsUpdate(): array {
			return $this->FieldsCreateAndUpdate();
		}

		public function PrepareOnUpdate(int $id, array & $item): void {
			$item['program'] = $this->model->GetDescriptionByTourId($id);
		}

		private function FieldsCreateAndUpdate(): array {
			$states = [
				Consts\Travel::STATE_DRAFT => Consts\Travel::STATES_RU[Consts\Travel::STATE_DRAFT],
				Consts\Travel::STATE_ACTIVE => Consts\Travel::STATES_RU[Consts\Travel::STATE_ACTIVE],
				Consts\Travel::STATE_INACTIVE => Consts\Travel::STATES_RU[Consts\Travel::STATE_INACTIVE],
			];

			return [
				'state' 			=> new Skins\Edit\Select('Состояние', 'form[state]', $states),
				'gid' 			    => new Skins\Edit\Select('Направление', 'form[gid]', ProjModel\Travel::instance()->GetDirections()),
				'date' 				=> new Skins\Edit\Text('Дата', 'form[date]'),
				'description' 		=> new Skins\Edit\TextArea('Описание', 'form[description]'),
				'tid' 				=> new Skins\Edit\Select('Вид тура', 'form[tid]', ProjModel\Travel::instance()->GetTypes()),
				'price' 			=> new Skins\Edit\Text('Цена', 'form[price]'),
				'duration' 			=> new Skins\Edit\Text('Длительность (цифрой)', 'form[duration]'),
				'cover' 			=> new Skins\Edit\File('Фотография', 'form[cover]', 'Выберите фотографию', '.jpg, .jpeg, .png'),
				'program'           => new Skins\Edit\Table('Маршрут', 'form[program]', [
					'day' => ['alias' => 'день', 'type' => 'number', 'name' => 'day'],
					'description' => ['alias' => 'описание', 'type' => 'textarea', 'name' => 'description']
				])
			];
		}

	}