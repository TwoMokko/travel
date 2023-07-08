<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'review/consts.inc';
	require DIR_UNITS . 'review/site/views/lists.tpl';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Units;
	use Proj\Site\Templates\Template;
	use Proj\Units\Consts;
	use Proj\DBQuery;
	use Proj\Site;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\Reviews\Lists;
	use Proj\Site\Templates\General;

	class Reviews extends Units implements Consts\Reviews {
		use Instance;

		private DBQuery $db;

//		public Action $for_main;
//		public Action $for_tour;
//		public Action $for_list;
		public Action $get;
		public Action $add;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBQuery::instance();

//			$this->for_main = new Action();
//			$this->for_tour = new Action('tours', 'show');
//			$this->for_list = new Action('review');
			$this->get = new Action('review', 'get');
			$this->add = new Action('review', 'add');

//			Controller::instance()->view->Push($this->for_main, [$this, 'ForMain']);
//			Controller::instance()->view->Push($this->for_tour, [$this, 'ForTour']);
//			Controller::instance()->view->Push($this->for_list, [$this, 'SetSeoForReview'], [$this, 'Header']);
			Controller::instance()->view->Push($this->get, [$this, 'OnReview']);
			Controller::instance()->work->Push($this->add, [$this, 'AddReview']);
		}

		public function GetReviewsForMain(): string {
			$state = self::STATE_VERIFIED;
			$result = $this->db->Select(self::TABLES['review'], ['id', 'name', 'text', 'avatar'], "`state` = {$state}", '`date_create` DESC', 20);
			$items = $this->db->FetchAll($result);

			if (!$items) return '';

			return Lists::ToVarCarousel($items, Consts\Reviews::AVATARS);
		}

		public function ForTour($tid): string {

			$state = self::STATE_VERIFIED;
//			 = GetInt('id');
            $gid = Tour::instance()->GetGroupId($tid);
			$result = $this->db->Select(self::TABLES['review'], ['id', 'name', 'text', 'avatar'], "(`state` = {$state}) AND (`gid` = {$gid})", '`date_create` DESC', 20);
			$items = $this->db->FetchAll($result);

			if (!$items) return '';

			return Lists::ToVarCarousel($items, []);
		}

		public function ForList(): string {
			$state = self::STATE_VERIFIED;
			$result = $this->db->Select(self::TABLES['review'], ['id', 'name', 'text', 'avatar'], "`state` = {$state}", '`date_create` DESC', 20);
			$items = $this->db->FetchAll($result);

			return Lists::ToVarGrid($items);
		}

		public function Header(): string {
			$image = Site\Units\General::instance()->GetImage('review');
			return General\HeaderForPages::ToVar("{$image}", 'Отзывы', 'Возможно, текст');
		}

		#[NoReturn] public function OnReview(): void {
			$id = GetInt('id');

			$state = self::STATE_VERIFIED;
			$item = $this->db->SelectOne(self::TABLES['review'], ['name', 'text', 'avatar'], "(`state` = {$state}) AND (`id` = {$id})");
			$item['image'] = Consts\Reviews::AVATARS[$item['avatar']];

			SendJSONSuccess($item);
		}

//		public function SetSeoForReview() {
//			Template::instance()->SetTitle('Отзывы');
//			Template::instance()->SetDescription('');
//		}

		#[NoReturn] public function AddReview() {
			$name = GetParam('name', '');
			$text = GetParam('text', '');
			$avatar = GetInt('avatar');

			if (!isset(self::AVATARS[$avatar])) $avatar = rand(1, count(self::AVATARS));

			$data = [
				'name' => $name,
				'text' => $text,
				'state' => Consts\Reviews::STATE_UNVERIFIED,
				'avatar' => $avatar
			];

			$this->db->Insert(self::TABLES['review'], $data);

			SendJSONSuccess(null);
		}

	}

	Reviews::init();