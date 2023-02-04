<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'feedback/consts.inc';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Units;
	use Proj\Units\Consts;

	class Feedback extends Units implements Consts\Feedback {
		use Instance;

		private Action $feedback;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);

			$this->feedback = new Action('feedback', 'null');

			Controller::instance()->view->Push($this->feedback, [$this, 'Feedback']);
		}

		#[NoReturn] public function Feedback() {
			$name = GetParam('name', 'Не известно');
			$contact = GetParam('contact', 'Не известно');

			$file = fopen('feedback.txt', 'a');
			fwrite($file, "Имя: {$name} Контакт: {$contact}\n");
			fclose($file);

//			$db = new \mysqli('localhost', 'root', '', 'travel');
//			$db->query("INSERT INTO `feedback`(`name`, `contact`) VALUES ('{$name}','{$contact}')");

			SendJSONSuccess(null);
		}
	}

	Feedback::init();