<?php

    namespace Proj\Site\Units;

    require DIR_UNITS . 'statistics/site/statistics.actions.inc';
    require DIR_UNITS . 'statistics/site/statistics.model.inc';

    use Base\Instance;
    use Base\Controller;
    use Proj\Site\Actions;
    use Proj\Site\Model;

    class Statistics extends Actions\Statistics {
        use Instance;

        private Model\Statistics $model;

        private function __construct() {
            parent::__construct();

            $this->model = Model\Statistics::instance();

            Controller::instance()->view->Push(self::$collect, [$this, 'Collect']);
        }

        public function Collect(): void {
            if (Controller::$area == 'statistics') return;

            $this->model->Collect();
        }

    }

    Statistics::init();