<?php

    namespace Proj\Admin\Editor;

    require DIR_UNITS . 'review/admin/views/publish.tpl';

    use JetBrains\PhpStorm\NoReturn;

    use Base\Action;
    use Base\Controller;
    use Base\DB\MySQLi\Table;
    use Base\Editor\EditorMySQLi;
    use Base\Editor\Skins;
    use Proj\Admin\Units\Tours;
    use Proj\Units\Consts;
    use Proj\Admin\Templates;

    class Reviews extends EditorMySQLi {
        public Action $publish;
        public Action $do_publish;

        public function __construct(string $name, Table $table) {
            parent::__construct($name, $table);

            $this->publish = new Action($this->name, 'publish', "/{$this->name}/publish?id=%id%", /* @lang JavaScript */"Base.Common.Query.SendData('/{$this->name}/publish', {id: %id%}, Admin.General.Render.ToMain); return false;");
            $this->do_publish = new Action($this->name, 'do_publish', "/{$this->name}/do_publish?id=%id%", /* @lang JavaScript */"Base.Common.Query.SendData('/{$this->name}/do_publish', {id: %id%}, Admin.General.Render.ToMain); return false;");

            Controller::instance()->view->Push($this->publish, [$this, 'Publish']);
            Controller::instance()->view->Push($this->do_publish, [$this, 'DoPublish']);
        }

        protected function Where(array $params): array {
            return [
                '`state` != ' . Consts\Reviews::STATES['error']
            ];
        }

        protected function Order(): array {
            return [
                '`date_create` DESC',
                '`id` ASC'
            ];
        }

        protected function Manage(): array {
            return [
                function (array $params, array $item) { return $this->publish->GetLink('Опубликовать', ['id' => $item['id']]); },
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

        protected function FieldsSelect(array $params): array {
            return [
                'id' 		=> new Skins\Browse\Text('#'),
                'gid' 		=> new Skins\Browse\ValueFromArray('К какому направлению относится', Tours::instance()->GetGroupTour()),
                'state' 	=> new Skins\Browse\ValueFromArray('Состояние', Consts\Reviews::STATES_RU),
                'name' 		=> new Skins\Browse\Text('Имя')
            ];
        }

        protected function FieldsBrowse(array $data) : array {
            return [
                'state'     => new Skins\Browse\ValueFromArray('Состояние', Consts\Reviews::STATES_RU),
                'name'    	=> new Skins\Browse\Text('Имя'),
                'text'      => new Skins\Browse\Text('Текст'),
            ];
        }

        public function Publish(): void {
            $id = GetInt('id');
            $item = $this->table->SelectOne(null, "(`id` = {$id})");
            $fields = [
                'tour_id'       => new Skins\Edit\Select('К какому направлению относится', 'gid', array_merge(['Выберите'], Tours::instance()->GetGroupTour())),
                'name'          => new Skins\Edit\Text('Имя', 'name'),
                'text'          => new Skins\Edit\TextArea('Текст', 'text')
            ];

//            $this->PrepareOnUpdate($id, $item, $data);
//            $this->fieldsUpdate = $this->FieldsUpdate([]);
            SendJSONSuccess(['html' => Templates\Reviews\Publish::ToVar($this, $id, $fields, $item, [], 'Публикация отзыва')]);
        }

        #[NoReturn] public function DoPublish(): void {
            $id = GetInt('id');
            $old_state = Consts\Reviews::STATE_UNVERIFIED;
            $this->table->Update(['state' => Consts\Reviews::STATE_VERIFIED], "(`state` = {$old_state}) AND (`id` = {$id})");

            $this->fieldsSelect = $this->FieldsSelect([]);
            SendJSONSuccess(['message' => $this->titleDoUpdate, 'html' => $this->Select()]);
        }

    }