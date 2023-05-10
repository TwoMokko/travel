<?php

	namespace Proj\Admin\Editor;

	use JetBrains\PhpStorm\NoReturn;

	use Base\DB\TableMySQLi;
	use Base\Editor\EditorMySQLi;
	use Base\Editor\Skins;
	use Proj\Admin\Units;
	use Proj\Units\Consts;

	class Tour extends EditorMySQLi {
        private TableMySQLi $table_program;

		public function __construct(string $name, array $tables) {
            [$table, $this->table_program] = $tables;
			parent::__construct($name, $table);
		}

		protected function Where(array $params): array {
			return [
				'`state` != ' . Consts\Tour::STATES['delete']
			];
		}

		protected function Order(): array {
			return [
				'`date_create` DESC',
				'`id` ASC'
			];
		}

		protected function Calc(): array {
			return [
				"*, CONCAT(`hash`, '.', `id`, '.', `ext`) AS `cover`"
			];
		}

		protected function RegTitles(): void {
			$this->titleSelect = 'Список туров';
			$this->titleCreate = 'Добавить тур';
			$this->titleUpdate = 'Редактирование тура';
			$this->titleDelete = 'Удалить тур?';

			$this->titleDoCreate = 'Тур добавлен';
			$this->titleDoUpdate = 'Тур изменен';
			$this->titleDoDelete = 'Тур удален';
		}

		protected function FieldsSelect(array $params): array {
			return [
				'id' 				=> new Skins\Browse\Text('#'),
				'state' 			=> new Skins\Browse\ValueFromArray('Состояние', Consts\Tour::STATES_RU),
                'date'    			=> new Skins\Browse\Text('Дата'),
                'name' 				=> new Skins\Browse\Text('Название')
			];
		}

		protected function FieldsBrowse(array $params) : array {
			return [
				'state'     		=> new Skins\Browse\ValueFromArray('Состояние', Consts\Tour::STATES_RU),
				'name'    			=> new Skins\Browse\Text('Заголовок'),
				'date'    			=> new Skins\Browse\Text('Дата'),
				'description'      	=> new Skins\Browse\Text('Описание'),
				'cover'     		=> new Skins\Browse\Image('Картинка', Consts\Tour::PATH_TOUR_RELATIVE)
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
				'state' 			=> new Skins\Edit\Select('Состояние', 'form[state]', $states),
				'gid' 			    => new Skins\Edit\Select('Заголовок', 'form[gid]', Units\Tours::instance()->GetGroupTour()),
				'date' 				=> new Skins\Edit\Text('Дата', 'form[date]'),
				'description' 		=> new Skins\Edit\TextArea('Описание', 'form[description]'),
				'tid' 				=> new Skins\Edit\Select('Тип тура', 'form[tid]', Units\Tours::instance()->GetTypes()),
				'price' 			=> new Skins\Edit\Text('Цена', 'form[price]'),
				'duration' 			=> new Skins\Edit\Text('Длительность (цифрой)', 'form[duration]'),
				'cover' 			=> new Skins\Edit\File('Фотография', 'form[cover]', 'Выберите фотографию', '.jpg, .jpeg, .png'),
                'program'           => new Skins\Edit\Table('Маршрут', 'form[program]', [
                    'day' => ['alias' => 'день', 'type' => 'number', 'name' => 'day'],
                    'description' => ['alias' => 'описание', 'type' => 'textarea', 'name' => 'description']
                ])
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

            $result = $this->table_program->Select(['day', 'description'], "`tour_id`={$id}", '`day`');
            $item['program'] = $this->table_program->FetchAll($result);
		}

		#[NoReturn] public function DoCreate(): void {
			$data = GetParam('form', []);

            $program = [];
            if (isset($data['program'])) {
                $program = $data['program'];
                unset($data['program']);
            }

			$id = $this->table->Insert($data);

            $this->SaveProgram($program, $id);

			if ($_FILES['form']['tmp_name']['cover']) {
				[$hash, $ext] = $this->SaveFile($id);
				$this->table->Update(['hash' => $hash, 'ext' => $ext], "`id` = {$id}");
			}

			SendJSONSuccess(['message' => $this->titleDoCreate, 'html' => $this->Select()]);
		}

		#[NoReturn] public function DoUpdate(): void {
			$id = (int)GetParam('id', 0);
			$data = GetParam('form', []);

            $program = [];
            if (isset($data['program'])) {
                $program = $data['program'];
                unset($data['program']);
            }

            $this->table_program->Delete("`tour_id` = {$id}");
            $this->SaveProgram($program, $id);

			if ($_FILES['form']['tmp_name']['cover']) {
				$old_file = $this->table->SelectOneFieldCalc("CONCAT(`hash`, '.', `id`, '.', `ext`) AS `name`", 'name', "`id` = {$id}");
				if ($old_file && file_exists(Consts\Tour::PATH_TOUR . $old_file)) unlink(Consts\Tour::PATH_TOUR . $old_file);

				[$data['hash'], $data['ext']] = $this->SaveFile($id);
			}

			$this->table->Update($data, "`id` = {$id}");

			SendJSONSuccess(['message' => $this->titleDoUpdate, 'html' => $this->Select()]);
		}

        private function SaveProgram(array $program, int $id): void {
            if ($program) {
                $valuesItems = [];
                foreach ($program as $item) $valuesItems[] = "({$id}, {$item['day']}, '{$item['description']}')";
                $values = implode(', ', $valuesItems);
                $this->table_program->Query("INSERT INTO `{$this->table_program->GetName()}` (`tour_id`, `day`, `description`) VALUES {$values}");
            }
        }

		private function SaveFile(int $id): array {
			$temp_path = $_FILES['form']['tmp_name']['cover'];
			$temp_name = $_FILES['form']['name']['cover'];
			$dir = Consts\Tour::PATH_TOUR;
			$hash = hash_file('md5', $temp_path);
			$info = pathinfo($temp_name);
			$ext = $info['extension'];
			$name = "{$hash}.{$id}.{$ext}";

			if (!is_dir($dir)) mkdir($dir, 0777, true);
			move_uploaded_file($temp_path, $dir . $name);

			return [$hash, $ext];
		}

	}