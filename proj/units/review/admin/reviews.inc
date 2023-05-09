<?php

    namespace Proj\Admin\Units;

    require DIR_UNITS . 'review/admin/reviews.structure.inc';
    require DIR_UNITS . 'review/admin/reviews.editor.inc';

    use Base\Instance;
    use Base\Controller;
    use Base\Action;
    use Base\Editor\EditorMySQLi;
    use Proj\Admin\Structure;
    use Proj\Admin\Templates\Layout;
    use Proj\Admin\Templates\General\Group;

    class Reviews extends Structure\Reviews {
        use Instance;

        private EditorMySQLi $editor_review;

        private Action $out_menu;

        private function __construct() {
            parent::__construct();

            $this->editor_review = new \Proj\Admin\Editor\Reviews(self::NAME, $this->table_reviews);
            $this->out_menu = new Action();

            Controller::instance()->view->Push($this->out_menu, [$this, 'OutMenu']);
        }

        public function OutMenu() {
            Layout::instance()->menu->Push(
                Group::ToVar('Отзывы', [
                    $this->editor_review->select->GetLink('Список', ['page' => 1])
                ])
            );
        }

    }

    Reviews::init();