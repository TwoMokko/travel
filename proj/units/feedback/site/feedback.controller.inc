<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . '/feedback/site/feedback.actions.inc';
	require DIR_UNITS . '/feedback/site/feedback.model.inc';

	require DIR_UNITS . '/feedback/site/views/forTour.tpl';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Instance;
	use Base\Helper\Response;
	use Proj\Site\Actions;
	use Proj\Site\Model;
	use Proj\Site\Templates as TPLs;
	use Proj\Units\Consts;
	use Closure;

	class Feedback extends Actions\Feedback {
		use Instance;

		private function __construct() {
			parent::__construct(__FILE__);

			self::$view->Push([self::ENTRY_XHR], self::$feedback_add, Closure::fromCallable([$this, 'Add']));
		}

		#[NoReturn] public function Add() {
            $tour_id = GetInt('tour_id');
			$name = trim(GetParam('name', ''));
			$contact = trim(GetParam('contact', ''));
			$text = trim(GetParam('text', ''));

            if (mb_strlen($name) < 3) Response::SendNoticeError('Имя не менее 3 символов');
            if (mb_strlen($name) > 50) Response::SendNoticeError('Имя не более 50 символов');
            if (mb_strlen($contact) < 3) Response::SendNoticeError('Контакт не менее 3 символов');
            if (mb_strlen($contact) > 50) Response::SendNoticeError('Контакт не более 50 символов');
            if (mb_strlen($text) > 255) Response::SendNoticeError('Текст не более 255 символов');

			$data = [
				'tour_id' => $tour_id,
				'name' => $name,
				'contact' => $contact,
				'text' => $text,
				'state' => Consts\Feedback::STATE_UNVERIFIED
			];

			Model\Feedback::instance()->AddFeedback($data);

			Response::PushData([]);
			Response::SendJSON();
		}

        public function ForTour($id): string {
            return TPLs\Feedback\ForTour::ToVar($id);
        }

	}

	Feedback::init();