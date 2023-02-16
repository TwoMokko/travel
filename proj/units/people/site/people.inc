<?php

namespace Proj\Site\Units;

require DIR_UNITS . 'people/consts.inc';
require DIR_UNITS . 'people/site/views/team.tpl';

use JetBrains\PhpStorm\NoReturn;

use Base\Instance;
use Base\Controller;
use Base\Action;
use Base\Units;
use Proj\Units\Consts;
use Proj\DBQuery;
use Proj\Site\Templates\Layout;
use Proj\Site\Templates\People\Team;

class People extends Units implements Consts\People {
	use Instance;

	private DBQuery $db;

	public Action $people;
//	public Action $for_tour;
//	public Action $for_list;
//	public Action $get;

	private function __construct() {
		parent::__construct(self::ID, self::NAME);
		$this->db = DBQuery::instance();

		$this->people = new Action('about', 'null');

		Controller::instance()->view->Push($this->people, [$this, 'Team']);
	}

	public function Team(): void {
		$state = self::STATE_ACTIVE;
		$result = $this->db->Select(self::TABLES['people'], ['id', 'name', 'text', 'number', 'link_vk', 'link_wa'], "`state` = {$state}", '`date_create`', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
		$items = $this->db->FetchAll($result);

		Layout::instance()->main->Push(Team::object()->ToVar($items));
	}
//
//	public function ForTour(): void {
//		$state = self::STATE_ACTIVE;
//		$tid = GetInt('id');
//		$result = $this->db->Select(self::TABLES['reviews'], ['id', 'name', 'text'], "(`state` = {$state}) AND (`tid` = {$tid})", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
//		$items = $this->db->FetchAll($result);
//
//		Layout::instance()->main->Push(Lists::object()->ToVarCarousel($items));
//	}
//
//	public function ForList(): void {
//		$state = self::STATE_ACTIVE;
//		$result = $this->db->Select(self::TABLES['reviews'], ['id', 'name', 'text'], "`state` = {$state}", '`date_create` DESC', 20, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `image`"]);
//		$items = $this->db->FetchAll($result);
//
//		Layout::instance()->main->Push(Lists::object()->ToVarGrid($items));
//	}
//
//	#[NoReturn] public function OnReview(): void {
//		$id = GetInt('id');
//
//		$state = self::STATE_ACTIVE;
//		$path = Consts\Reviews::PATH_AVATAR_RELATIVE;
//		$item = $this->db->SelectOne(self::TABLES['reviews'], ['name', 'text'], "(`state` = {$state}) AND (`id` = {$id})", null, null, ["CONCAT('{$path}', `hash`, '.', `id`, '.', `ext`) AS `image`"]);
//
//		SendJSONSuccess($item);
//	}

}

People::init();