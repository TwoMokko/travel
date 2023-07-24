<?php

	namespace Base\Editor;

	require DIR_BASE . 'editor/editor.actions.inc';
	require DIR_BASE . 'editor/editor.model.inc';

	require DIR_BASE . 'editor/skins/skin.inc';

	require DIR_BASE . 'editor/views/select.tpl';
	require DIR_BASE . 'editor/views/browse.tpl';
	require DIR_BASE . 'editor/views/create.tpl';
	require DIR_BASE . 'editor/views/update.tpl';

	use JetBrains\PhpStorm\NoReturn;

	use Base;
	use Base\Controller;
	use Base\Pages;
	use Base\Templates\Editor\Select;
	use Base\Templates\Editor\Create;
	use Base\Templates\Editor\Update;
	use Base\Templates\Editor\Browse;

	abstract class Editor extends Actions {
		protected Model $model;

		protected string $titleSelect = 'Выборка';
		protected string $titleBrowse = 'Просмотр';
		protected string $titleCreate = 'Создание';
		protected string $titleUpdate = 'Редактирование';
		protected string $titleDelete = 'Удалить?';
		protected string $titleState = 'Изменить состояние?';

		protected string $titleDoCreate = 'Создано';
		protected string $titleDoUpdate = 'Изменено';
		protected string $titleDoDelete = 'Удалено';
		protected string $titleSetState = 'Состояние изменено';

		protected string $errorAccess = 'Доступ запрещён';
		protected string $errorSave = 'Ошибка сохранения';

		protected array $params = [];

		protected int $page_entries = 50;

		protected function __construct(string $name) {
			parent::__construct($name);

			$this->SetHandlers();
		}

		protected function SetHandlers(): void {
			Controller::instance()->view->Push($this->select, [$this, 'OnSelect']);
			Controller::instance()->view->Push($this->browse, [$this, 'OnBrowse']);
			Controller::instance()->view->Push($this->create, [$this, 'OnCreate']);
			Controller::instance()->view->Push($this->update, [$this, 'OnUpdate']);

			Controller::instance()->view->Push($this->do_create, [$this, 'DoCreate']);
			Controller::instance()->view->Push($this->do_update, [$this, 'DoUpdate']);
			Controller::instance()->view->Push($this->do_delete, [$this, 'DoDelete']);
			Controller::instance()->view->Push($this->set_state, [$this, 'SetState']);
		}

		protected function FieldsSelect(): array { return []; }
		protected function FieldsBrowse(): array { return []; }
		protected function FieldsCreate(): array { return []; }
		protected function FieldsUpdate(): array { return []; }

		protected function NavigateSelect(): array { return []; }
		protected function NavigateBrowse(): array { return [ function () { return $this->select->GetLink("<< {$this->titleSelect}", array_merge(['page' => 1], $this->params)); } ]; }
		protected function NavigateCreate(): array { return [ function () { return $this->select->GetLink("<< {$this->titleSelect}", array_merge(['page' => 1], $this->params)); } ]; }
		protected function NavigateUpdate(): array { return [ function () { return $this->select->GetLink("<< {$this->titleSelect}", array_merge(['page' => 1], $this->params)); } ]; }

		protected function ManageSelect(): array {
			return [
				function (array $item) { return $this->update->GetLink('Изменить', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->do_delete->GetLink('Удалить', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->browse->GetLink('Просмотреть', array_merge(['id' => $item['id']], $this->params)); }
			];
		}

		protected function GetOnSelectHTML(): string {
			$page = GetInt('page', 1);

			$fields				= $this->FieldsSelect();
			[$items, $ext]		= $this->model->SelectData($page, $this->page_entries);
			$navigate			= $this->NavigateSelect();
			$manage				= $this->ManageSelect();

			return Select::ToVar($this, $fields, $items, $ext, $this->titleSelect, $navigate, $manage);
		}

		#[NoReturn] public function OnSelect(): void {
			SendJSONSuccess(['html' => $this->GetOnSelectHTML()]);
		}

		#[NoReturn] public function OnBrowse(): void {
			$id = GetInt('id');
			$item = $this->model->GetItemForBrowse($id);

			$fields				= $this->FieldsBrowse();
			$navigate			= $this->NavigateBrowse();

			SendJSONSuccess(['html' => Browse::ToVar($this, $fields, $id, $item, "{$this->titleBrowse} #{$id}", $navigate)]);
		}

		#[NoReturn] public function OnCreate(): void {
			$fields				= $this->FieldsCreate();
			$navigate			= $this->NavigateCreate();

			SendJSONSuccess(['html' => Create::ToVar($this, $fields, $this->titleCreate, $navigate, $this->params)]);
		}

		#[NoReturn] public function OnUpdate(): void {
			$id = GetInt('id');
			$item = $this->model->GetItem($id);

			$fields				= $this->FieldsUpdate();
			$navigate			= $this->NavigateUpdate();

			SendJSONSuccess(['html' => Update::ToVar($this, $fields, $id, $item, "{$this->titleUpdate} #{$id}", $navigate, $this->params)]);
		}

		protected function PrepareDoCreate(& $data): void {  }

		#[NoReturn] public function DoCreate(): void {
			$data = GetParam('form', []);
			$this->PrepareDoCreate($data);

			if (!$this->model->Create($data)) SendJSONSuccess(['message' => $this->titleDoUpdate]);

			SendJSONSuccess(['message' => $this->titleDoCreate, 'html' => $this->GetOnSelectHTML()]);
		}

		#[NoReturn] public function DoUpdate(): void {
			$id = GetInt('id');
			$data = GetParam('form', []);

			if (!$this->model->Update($data, $id)) SendJSONSuccess(['message' => $this->titleDoUpdate]);

			SendJSONSuccess(['message' => $this->titleDoUpdate, 'html' => $this->GetOnSelectHTML()]);
		}

		#[NoReturn] public function DoDelete(): void {
			$id = GetInt('id');

			$this->model->Delete($id);

			SendJSONSuccess(['message' => $this->titleDoDelete, 'html' => $this->GetOnSelectHTML()]);
		}

		#[NoReturn] public function SetState(): void {
			$id = GetInt('id');
			$state = GetInt('state');

			$oldState = $this->model->GetState($id);
			if ($this->model->AccessState($oldState, $state)) SendJSONSuccess(['message' => $this->errorAccess, 'html' => $this->GetOnSelectHTML()]);

			$this->model->SetState($state, $id);

			SendJSONSuccess(['message' => $this->titleSetState, 'html' => $this->GetOnSelectHTML()]);
		}

		public function Pages($pages): string {
			if (!$this->page_entries) return '';

			return (new Pages($this->select, $pages['current'], $pages['count']))->ToString();
		}

}