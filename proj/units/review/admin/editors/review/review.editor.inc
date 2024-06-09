<?php

	namespace Proj\Admin\Editor;

	require DIR_UNITS . 'review/admin/editors/review/review.editor.model.inc';

	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins;
	use Proj\Units\Consts;
	use Proj\Admin\Model as ProjModel;
	use Proj\Admin\Editor\Model;

	class Review extends Editor {

		public function __construct(int $id, string $name, Table $table, string $title = '') {
			parent::__construct($id, $name, $table, $title);

			$this->titleSelect = 'Отзывы';
			$this->titleBrowse = 'Просмотр отзыва';
			$this->titleUpdate = 'Публикация отзыва';
			$this->titleDelete = 'Удалить отзыв?';

			$this->titleDoDelete = 'Отзыв удален';
			$this->titleDoUpdate = 'Опубликовано';

			$this->btnUpdate = 'Опубликовать';

			$this->model = new Model\Review($table, $this->params);
        }

		protected function FieldsSelect(): array {
			return [
				'id' 		=> new Skins\Browse\Text('#'),
				'gid' 		=> new Skins\Browse\ValueFromArray('К какому направлению относится', ProjModel\Travel::instance()->GetDirections()),
				'state' 	=> new Skins\Browse\ValueFromArray('Состояние', Consts\Review::STATES_RU),
				'name' 		=> new Skins\Browse\Text('Имя')
			];
		}

		protected function FieldsBrowse(): array {
			return  [
				'state'     => new Skins\Browse\ValueFromArray('Состояние', Consts\Review::STATES_RU),
				'name'    	=> new Skins\Browse\Text('Имя'),
				'text'      => new Skins\Browse\Text('Текст'),
			];
		}

		protected function FieldsUpdate(): array {
			return [
				'gid'           => new Skins\Edit\Select('К какому направлению относится', 'form[gid]', ['Выберите'] + ProjModel\Travel::instance()->GetDirections()),
				'name'          => new Skins\Edit\Text('Имя', 'form[name]'),
				'text'          => new Skins\Edit\TextArea('Текст', 'form[text]')
			];
		}

		protected function ManageSelect(): array {
			return [
				function (array $item) { return $this->update->GetLinkHrefAllow(self::ACCESS_UPDATE, $item['state'] == Consts\Review::STATE_UNVERIFIED ? 'Опубликовать' : 'Редактировать', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->browse->GetLinkHrefAllow(self::ACCESS_BROWSE, 'Просмотреть', array_merge(['id' => $item['id']], $this->params)); },
			];
		}

    }