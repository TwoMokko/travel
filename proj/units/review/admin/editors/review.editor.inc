<?php

	namespace Proj\Admin\Editor\Review;

	require DIR_UNITS . 'review/admin/editors/review.editor.model.inc';

	use Base\Action;
	use Base\Controller;
	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins;
	use JetBrains\PhpStorm\NoReturn;
	use Proj\Admin\Editor\Model;
	use Proj\Admin\Templates;
	use Proj\Admin\Units\Tours;
	use Proj\Units\Consts;

	class Review extends Editor {

		public Action $publish;
		public Action $do_publish;

		public function __construct(string $name, Table $table) {
			$this->publish = new Action($name, 'publish', "/{$name}/publish?id=%id%", /* @lang JavaScript */"Base.Common.Query.SendData('/{$name}/publish', {id: %id%}, Admin.General.Render.ToMain); return false;");
			$this->do_publish = new Action($name, 'do_publish', "/{$name}/do_publish?id=%id%", /* @lang JavaScript */"Base.Common.Query.SendData('/{$name}/do_publish', {id: %id%}, Admin.General.Render.ToMain); return false;");

			parent::__construct($name);

			$this->titleSelect = 'Список';
			$this->titleDelete = 'Удалить?';

			$this->titleDoDelete = 'Удалено';

			$this->model = new Model\Review($table, $this->params);
		}

		protected function SetHandlers(): void {
			Controller::instance()->view->Push($this->select, [$this, 'OnSelect']);
			Controller::instance()->view->Push($this->browse, [$this, 'OnBrowse']);
			Controller::instance()->view->Push($this->create, [$this, 'OnCreate']);
			Controller::instance()->view->Push($this->update, [$this, 'OnUpdate']);
			Controller::instance()->view->Push($this->publish, [$this, 'OnPublish']);

			Controller::instance()->view->Push($this->do_create, [$this, 'DoCreate']);
			Controller::instance()->view->Push($this->do_update, [$this, 'DoUpdate']);
			Controller::instance()->view->Push($this->do_delete, [$this, 'DoDelete']);
			Controller::instance()->view->Push($this->do_publish, [$this, 'DoPublish']);
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
				function (array $item) { return $this->publish->GetLink('Опубликовать', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->browse->GetLink('Просмотреть', array_merge(['id' => $item['id']], $this->params)); },
//				function (array $params, array $item) { return $this->publish->GetLink('Опубликовать', ['id' => $item['id']]); },
//				function (array $params, array $item) { return $this->browse->GetLink('Просмотреть', ['id' => $item['id']]); }
			];
		}

		#[NoReturn] public function OnPublish(): void {
			SendJSONSuccess(['html' => 'asdasdasdsad']);
//			$id = GetInt('id');
			//$item = $this->table->SelectOne(null, "(`id` = {$id})");
//			$item= $this->model->GetItem($id);
//			$fields = [
//				'tour_id'       => new Skins\Edit\Select('К какому направлению относится', 'form[gid]', ['Выберите'] + Tours::instance()->GetGroupTour()),
//				'name'          => new Skins\Edit\Text('Имя', 'form[name]'),
//				'text'          => new Skins\Edit\TextArea('Текст', 'form[text]')
//			];
//
//			SendJSONSuccess(['html' => Templates\Reviews\Publish::ToVar($this, $id, $fields, $item, [], 'Публикация отзыва')]);
		}

		#[NoReturn] public function DoPublish(): void {
			SendJSONSuccess(['message' => $this->titleDoUpdate, 'html' => $this->GetOnSelectHTML()]);
//			$id = GetInt('id');
//			$data = GetParam('form', []);
//			$data['state'] = Consts\Reviews::STATE_VERIFIED;
//
//			$this->table->Update($data, "`id` = {$id}");
//
//			$this->fieldsSelect = $this->FieldsSelect([]);
//			SendJSONSuccess(['message' => $this->titleDoUpdate, 'html' => $this->Select()]);
		}

	}