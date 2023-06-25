<?php

namespace Proj\Admin\Structure;

require DIR_UNITS . 'people/consts.inc';

use Base\Units;
use Base\DB\MySQLi\Table;
use Proj\Units\Consts;
use Proj\DBObject;

class People extends Units implements Consts\People {
	private DBObject $db;

	protected Table $table_people;

	protected function __construct() {
		parent::__construct(self::ID, self::NAME);
		$this->db = DBObject::instance();

		$this->table_people = new Table(self::TABLES['people'], $this->db);
		$this->table_people->id('id');
		$this->table_people->uint8('state');
		$this->table_people->timestamp('date_create');
		$this->table_people->timestamp('date_modify');
		$this->table_people->string('name', 50);
		$this->table_people->string('hash', 32);
		$this->table_people->string('ext', 6);
		$this->table_people->text('text');
		$this->table_people->string('number', 20);
		$this->table_people->string('link_vk', 50);
		$this->table_people->string('link_wa', 50);

		$this->db->PushTables($this->table_people);
	}

}