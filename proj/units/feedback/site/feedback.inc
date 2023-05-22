<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . '/feedback/consts.inc';
	require DIR_UNITS . '/feedback/site/views/forTour.tpl';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Units;
    use Proj\Site\Templates\Layout;
    use Proj\Site\Templates\Feedback\ForTour;
    use Proj\Units\Consts;
	use Proj\DBQuery;

	class Feedback extends Units implements Consts\Feedback {
		use Instance;

        private DBQuery $db;

		private Action $feedback;
		private Action $for_tour;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
            $this->db = DBQuery::instance();

			$this->feedback = new Action('feedback', 'null');
			$this->for_tour = new Action('tours', 'show');

			Controller::instance()->view->Push($this->feedback, [$this, 'Feedback']);
			Controller::instance()->view->Push($this->for_tour, [$this, 'ForTour']);
		}

		#[NoReturn] public function Feedback() {
			$name = trim(GetParam('name', ''));
			$contact = trim(GetParam('contact', ''));
			$text = trim(GetParam('text', ''));

            if (mb_strlen($name) < 3) SendJSONError('Имя не менее 3 символов');

            $data = [
                'name' => mysqli_real_escape_string($name),
                'contact' => mysqli_real_escape_string($contact),
                'text' => mysqli_real_escape_string($text),
				'state' => Consts\Feedback::STATE_UNVERIFIED
            ];

            $this->db->Insert(self::TABLES['feedback'], $data);

			SendJSONSuccess(null);
		}

        public function ForTour(): void {
            Layout::instance()->main->Push(ForTour::ToVar());
        }
	}

	Feedback::init();