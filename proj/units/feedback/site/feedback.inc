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

		public Action $feedback;
//        public Action $for_tour;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
            $this->db = DBQuery::instance();

			$this->feedback = new Action('feedback', 'null');
//			$this->for_tour = new Action('tours', 'show');

			Controller::instance()->view->Push($this->feedback, [$this, 'Feedback']);
//			Controller::instance()->view->Push($this->for_tour, [$this, 'ForTour']);
		}

		#[NoReturn] public function Feedback() {
            $tour_id = GetInt('tour_id');
			$name = trim(GetParam('name', ''));
			$contact = trim(GetParam('contact', ''));
			$text = trim(GetParam('text', ''));

            if (mb_strlen($name) < 3) SendJSONError('Имя не менее 3 символов');
            if (mb_strlen($name) > 50) SendJSONError('Имя не более 50 символов');
            if (mb_strlen($contact) < 3) SendJSONError('Контакт не менее 3 символов');
            if (mb_strlen($contact) > 50) SendJSONError('Контакт не более 50 символов');
//            if (mb_strlen($text) < 3) SendJSONError('Текст не менее 3 символов');
            if (mb_strlen($text) > 255) SendJSONError('Текст не более 255 символов');

            $this->InsertFeedback($tour_id, $this->db->Escaping($name), $this->db->Escaping($contact), $this->db->Escaping($text));

			SendJSONSuccess(null);
		}

        public function InsertFeedback($tour_id, $name, $contact, $text): void {
            $data = [
                'tour_id' => $tour_id,
                'name' => $name,
                'contact' => $contact,
                'text' => $text,
				'state' => Consts\Feedback::STATE_UNVERIFIED
            ];

            $this->db->Insert(self::TABLES['feedback'], $data);
		}

        public function ForTour($id): string {
//            $id = GetInt('id');
            return ForTour::ToVar($id);
        }
	}

	Feedback::init();