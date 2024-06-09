<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'general/admin/general.structure.inc';
	require DIR_UNITS . 'general/admin/general.model.inc';

	require DIR_UNITS . 'general/admin/editors/text/text.editor.inc';
	require DIR_UNITS . 'general/admin/editors/image/image.editor.inc';

	require DIR_UNITS . 'general/admin/views/group.tpl';
	require DIR_UNITS . 'general/admin/views/structure.tpl';
	require DIR_UNITS . 'general/admin/views/check.tpl';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Helper\Response;
	use Closure;
	use Base\Instance;
	use Proj\Admin\Structure;
    use Proj\Admin\Actions;
	use Proj\Admin\Model;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General AS TPL;
	use Proj\Admin\Editor;
	use Proj\Editor\Consts as EditorConsts;
	use Proj\Params;

	class General extends Structure\General {
		use Instance;

		private Model\General $model;

		private Editor\Text $editor_text;
		private Editor\Image $editor_image;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->model = Model\General::instance();

			$this->editor_text = new Editor\Text(EditorConsts\ID_GENERAL_TEXT, self::NAME . '_text', $this->table_text, 'Контент, текста (редактор)');
			$this->editor_image = new Editor\Image(EditorConsts\ID_GENERAL_IMAGE, self::NAME . '_image', $this->table_image, 'Контент, изображения (редактор)');

			self::$view->Push([self::ENTRY_HTML], self::$out_head, Closure::fromCallable([$this, 'OutHead']));
			self::$view->Push([self::ENTRY_HTML], self::$out_menu, Closure::fromCallable([$this, 'OutMenu']));
			self::$view->Push([self::ENTRY_HTML], self::$out_footer, Closure::fromCallable([$this, 'OutFooter']));

			self::$view->Push([self::ENTRY_XHR], self::$home, Closure::fromCallable([$this, 'Home']));
			self::$view->Push([self::ENTRY_XHR], self::$db_structure, Closure::fromCallable([$this, 'Structure']));
			self::$view->Push([self::ENTRY_XHR], self::$db_check, Closure::fromCallable([$this, 'Check']));
			self::$view->Push([self::ENTRY_XHR], self::$db_make, Closure::fromCallable([$this, 'Make']));
		}

		#region HTML

		private function OutHead(): void {
			Layout::instance()->header->Push("<div>Привет, " . Model\Users::instance()->GetAlias() . "</div>");
			Layout::instance()->header->Push(Actions\Users::$exit->GetLinkHref('', [], ['class' => 'logout']));
		}

		public function OutMenu() {
			Layout::instance()->menu->Push(TPL\Item::ToVar('<a href = "' . self::$site->GetAddress() . '" target = "_blank">Открыть сайт</a>'));

			Layout::instance()->menu->Push($this->OutMenuSeparator());
			Layout::instance()->menu->Push(TPL\Item::ToVar(self::$home->GetLinkHref('Главная')));

			$menuBD = [];
			if ($this->Allow(self::ACCESS_DB_STRUCTURE)) $menuBD[] = self::$db_structure->GetLinkHref('Структура');
			if ($this->Allow(self::ACCESS_DB_CHECK)) $menuBD[] = self::$db_check->GetLinkHref('Проверить');
			$menuComposition = Composition::instance()->GetMenu();
			$menuStatistics = Statistics::instance()->GetMenu();
			if ($menuBD || $menuComposition || $menuStatistics) {
				Layout::instance()->menu->Push($this->OutMenuSeparator());
				Layout::instance()->menu->Push($this->OutMenuHead('Разработка'));
				if ($menuBD) Layout::instance()->menu->Push(TPL\Group::ToVar('База данных', $menuBD));
				if ($menuComposition) Layout::instance()->menu->Push(TPL\Group::ToVar('Композиция', $menuComposition));
				if ($menuStatistics) Layout::instance()->menu->Push(TPL\Group::ToVar('Статистика', $menuStatistics));
			}

			$menuGroup = Users::instance()->GetMenuGroup();
			$menuUser = Users::instance()->GetMenuUser();
			if ($menuGroup || $menuUser) {
				Layout::instance()->menu->Push($this->OutMenuSeparator());
				Layout::instance()->menu->Push($this->OutMenuHead('Безопасность'));
				if ($menuGroup) Layout::instance()->menu->Push(TPL\Group::ToVar('Группы', $menuGroup));
				if ($menuUser) Layout::instance()->menu->Push(TPL\Group::ToVar('Пользователи', $menuUser));
			}

			$menuTravelType = [];
			if (Travel::instance()->editor_type->AllowSelect()) $menuTravelType[] = Travel::instance()->editor_type->select->GetLinkHref('Список', ['page' => 1]);
			if (Travel::instance()->editor_type->AllowCreate()) $menuTravelType[] = Travel::instance()->editor_type->create->GetLinkHref('Добавить');

			$menuTravelDirection = [];
			if (Travel::instance()->editor_direction->AllowSelect()) $menuTravelDirection[] = Travel::instance()->editor_direction->select->GetLinkHref('Список', ['page' => 1]);
			if (Travel::instance()->editor_direction->AllowCreate()) $menuTravelDirection[] = Travel::instance()->editor_direction->create->GetLinkHref('Добавить');

			$menuTravelTour = [];
			if (Travel::instance()->editor_tour->AllowSelect()) $menuTravelTour[] = Travel::instance()->editor_tour->select->GetLinkHref('Список', ['page' => 1]);
			if (Travel::instance()->editor_tour->AllowCreate()) $menuTravelTour[] = Travel::instance()->editor_tour->create->GetLinkHref('Добавить');

			if ($menuTravelType || $menuTravelDirection || $menuTravelTour) {
				Layout::instance()->menu->Push(
					$this->OutMenuSeparator(),
					$this->OutMenuHead('Путешешествия')
				);
				if ($menuTravelType) Layout::instance()->menu->Push(TPL\Group::ToVar('Виды', $menuTravelType));
				if ($menuTravelDirection) Layout::instance()->menu->Push(TPL\Group::ToVar('Направления', $menuTravelDirection));
				if ($menuTravelTour) Layout::instance()->menu->Push(TPL\Group::ToVar('Туры', $menuTravelTour));
			}

			$menuGeneralText = [];
			if ($this->editor_text->AllowSelect()) $menuGeneralText[] = $this->editor_text->select->GetLinkHref('Список', ['page' => 1]);
			if ($this->editor_text->AllowCreate()) $menuGeneralText[] = $this->editor_text->create->GetLinkHref('Добавить');

			$menuGeneralImage = [];
			if ($this->editor_image->AllowSelect()) $menuGeneralImage[] = $this->editor_image->select->GetLinkHref('Список', ['page' => 1]);
			if ($this->editor_image->AllowCreate()) $menuGeneralImage[] = $this->editor_image->create->GetLinkHref('Добавить');

			$menuGeneralPeople = [];
			if (People::instance()->editor_people->AllowSelect()) $menuGeneralPeople[] = People::instance()->editor_people->select->GetLinkHref('Список', ['page' => 1]);
			if (People::instance()->editor_people->AllowCreate()) $menuGeneralPeople[] = People::instance()->editor_people->create->GetLinkHref('Добавить');

			$menuPhoto = [];
			if (Photo::instance()->editor_photo->AllowSelect()) $menuPhoto[] = Photo::instance()->editor_photo->select->GetLinkHref('Список', ['page' => 1]);
			if (Photo::instance()->editor_photo->AllowCreate()) $menuPhoto[] = Photo::instance()->editor_photo->create->GetLinkHref('Добавить');

			$menuStory = [];
			if (Story::instance()->editor_story->AllowSelect()) $menuStory[] = Story::instance()->editor_story->select->GetLinkHref('Список', ['page' => 1]);
			if (Story::instance()->editor_story->AllowCreate()) $menuStory[] = Story::instance()->editor_story->create->GetLinkHref('Добавить');

			if ($menuGeneralText || $menuGeneralImage || $menuGeneralPeople || $menuPhoto || $menuStory) {
				Layout::instance()->menu->Push(
					$this->OutMenuSeparator(),
					$this->OutMenuHead('Контент')
				);
				if ($menuGeneralText) Layout::instance()->menu->Push(TPL\Group::ToVar('Текста', $menuGeneralText));
				if ($menuGeneralImage) Layout::instance()->menu->Push(TPL\Group::ToVar('Изображения', $menuGeneralImage));
				if ($menuGeneralPeople) Layout::instance()->menu->Push(TPL\Group::ToVar('Люди', $menuGeneralPeople));
				if ($menuPhoto) Layout::instance()->menu->Push(TPL\Group::ToVar('Фотоальбомы', $menuPhoto));
				if ($menuStory) Layout::instance()->menu->Push(TPL\Group::ToVar('Истории', $menuStory));
			}

			$menuFeedback = [];
			if (Feedback::instance()->editor_feedback->AllowSelect()) $menuFeedback[] = Feedback::instance()->editor_feedback->select->GetLinkHref('Список', ['page' => 1]);
			if (Feedback::instance()->editor_feedback->AllowCreate()) $menuFeedback[] = Feedback::instance()->editor_feedback->create->GetLinkHref('Добавить');

			if (Review::instance()->editor_review->AllowSelect() || $menuFeedback) {
				Layout::instance()->menu->Push(
					$this->OutMenuSeparator(),
					$this->OutMenuHead('Прочее')
				);
				if (Review::instance()->editor_review->AllowSelect()) Layout::instance()->menu->Push(TPL\Item::ToVar(Review::instance()->editor_review->select->GetLinkHref('Отзывы', ['page' => 1])));
				if ($menuFeedback) Layout::instance()->menu->Push(TPL\Group::ToVar('Обратная связь', $menuFeedback));
			}

		}

		#endregion HTML

		private function OutMenuSeparator(): string {
			return '<hr>';
		}

		private function OutMenuHead(string $text): string {
			return "<div class = 'head'>{$text}</div>";
		}

		private function OutFooter() {
			Layout::instance()->footer->Push('© ' . Params::$site_name . ', 2023');
		}

		#region XHR

		#[NoReturn] private function Home() {
			Response::PushHistory(self::$home);
			Response::PushSection('main', $this->model->Home());
			Response::SendJSON();
		}

		#[NoReturn] private function Structure() {
			if (!$this->Allow(self::ACCESS_DB_STRUCTURE)) Response::SendNoticeError(self::TEXT_ERROR_ACCESS);

			Response::PushHistory(self::$db_structure);
			Response::PushSection('main', TPL\Structure::ToVar($this->model->Structure()));
			Response::SendJSON();
		}

		#[NoReturn] private function Check() {
			if (!$this->Allow(self::ACCESS_DB_CHECK)) Response::SendNoticeError(self::TEXT_ERROR_ACCESS);

			Response::PushHistory(self::$db_check);
			Response::PushSection('main', TPL\Check::ToVar($this->model->DBCheck()));
			Response::SendJSON();
		}

		#[NoReturn] private function Make() {
			if (!$this->Allow(self::ACCESS_DB_MAKE)) Response::SendNoticeError(self::TEXT_ERROR_ACCESS);

			Response::PushData($this->model->DBMake());
			Response::SendJSON();
		}

		#endregion XHR

	}

	General::init();