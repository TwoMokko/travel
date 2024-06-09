<?php

    namespace Proj\Admin\Units;

    require DIR_UNITS . 'review/admin/review.structure.inc';
    require DIR_UNITS . 'review/admin/editors/review/review.editor.inc';

    use Base\Instance;
    use Proj\Admin\Structure;
	use Proj\Admin\Editor;
    use Proj\Editor\Consts as EditorConsts;

    class Review extends Structure\Review {
        use Instance;

        public Editor\Review $editor_review;

        private function __construct() {
            parent::__construct(__FILE__);

            $this->editor_review = new Editor\Review(EditorConsts\ID_REVIEW, self::NAME, $this->table_reviews, 'Отзывы (редактор)');
        }

    }

    Review::init();