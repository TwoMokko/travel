<?php

	namespace Proj\Admin\Editor;

	use JetBrains\PhpStorm\NoReturn;

	use Base\DB\TableMySQLi;
	use Base\Editor\EditorMySQLi;
	use Base\Editor\Skins;
	use Proj\Units\Consts;

	class People extends EditorMySQLi {

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);
		}

		protected function Where(array $params): array {
			return [
				'`state` != ' . Consts\People::STATES['delete']
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
			$this->titleSelect = 'Список людей';
			$this->titleCreate = 'Добавить человека';
			$this->titleUpdate = 'Редактирование человека';
			$this->titleDelete = 'Удалить человека?';

			$this->titleDoCreate = 'Человек добавлена';
			$this->titleDoUpdate = 'Человек изменена';
			$this->titleDoDelete = 'Человек удалена';
		}

		protected function FieldsSelect(array $params): array {
			return [
				'id' 		=> new Skins\Browse\Text('#'),
				'state' 	=> new Skins\Browse\ValueFromArray('Состояние', Consts\People::STATES_RU),
				'name' 		=> new Skins\Browse\Text('Имя')
			];
		}

		protected function FieldsBrowse(array $params) : array {
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
                'state' 	=> new Skins\Edit\Select('Состояние', 'form[state]', $states),
                'name' 		=> new Skins\Edit\Text('Имя', 'form[name]'),
                'text' 		=> new Skins\Edit\TextArea('Текст', 'form[text]'),
                'number' 	=> new Skins\Edit\Text('Номер', 'form[number]'),
                'link_vk' 	=> new Skins\Edit\Text('Вконтакте', 'form[link_vk]'),
                'link_wa' 	=> new Skins\Edit\Text('ВотсАпп', 'form[link_wa]'),
                'cover' 	=> new Skins\Edit\File('Фотография', 'form[cover]', 'Выберите фотографию', '.jpg, .jpeg, .png')
            ];
        }

		public function PrepareOnUpdate(int $id, array & $item, array & $data): void {
			$data['state'] = [
				Consts\People::STATE_DRAFT	=> 'Черновик',
				Consts\People::STATE_ACTIVE	=> 'Активная',
				Consts\People::STATE_INACTIVE	=> 'Не активная',
			];
		}

		#[NoReturn] public function DoCreate(): void {
			$data = GetParam('form', []);

			$id = $this->table->Insert($data);

			if ($_FILES['form']['tmp_name']['cover']) {
				[$hash, $ext] = $this->SaveFile($id);
				$this->table->Update(['hash' => $hash, 'ext' => $ext], "`id` = {$id}");
			}

			SendJSONSuccess(['message' => $this->titleDoCreate, 'html' => $this->Select()]);
		}

		#[NoReturn] public function DoUpdate(): void {
			$id = (int)GetParam('id', 0);
			$data = GetParam('form', []);

			if ($_FILES['form']['tmp_name']['cover']) {
				$old_file = $this->table->SelectOneFieldCalc("CONCAT(`hash`, '.', `id`, '.', `ext`) AS `name`", 'name', "`id` = {$id}");
				if ($old_file) unlink(Consts\People::PATH_AVATAR . $old_file);

				[$data['hash'], $data['ext']] = $this->SaveFile($id);
			}

			$this->table->Update($data, "`id` = {$id}");

			SendJSONSuccess(['message' => $this->titleDoUpdate, 'html' => $this->Select()]);
		}

		private function SaveFile(int $id): array {
			$temp_path = $_FILES['form']['tmp_name']['cover'];
			$temp_name = $_FILES['form']['name']['cover'];
			$dir = Consts\People::PATH_AVATAR;
			$hash = hash_file('md5', $temp_path);
			$info = pathinfo($temp_name);
			$ext = $info['extension'];
			$name = "{$hash}.{$id}.{$ext}";

			if (!is_dir($dir)) mkdir($dir, 0777, true);
			move_uploaded_file($temp_path, $dir . $name);

			return [$hash, $ext];
		}

	}