<?php

	namespace Proj;

	use Base\DB\DBQueryMySQLi;

	class DBQuery extends DBQueryMySQLi {
		static protected ?self $instance = null;

		public function __construct($hostname, $user, $password, $dbname) {
			parent::__construct($hostname, $user, $password, $dbname);
		}

		public static function Connect(?string $hostname = null, ?string $user = null, ?string $password = null, ?string $dbname = null, string|int|null $port = null, ?string $socket = null): self {
			return new self($hostname, $user, $password, $dbname);
		}

		public static function instance(): ?self { return self::$instance; }
		public static function init(?string $host = null, ?string $username = null, ?string $password = null, ?string $dbname = null, string|int|null $port = null, ?string $socket = null) { if (!self::$instance) self::$instance = self::Connect($host, $username, $password, $dbname, $port, $socket); }

	}

//	DBQuery::init('localhost', 'root', '', 'travel');
	DBQuery::init('localhost', 'dd_travel', 'Lsr-auQ/6q4mkM8y', 'dd_travel');
//	const DB_NAME = 'dd_travel';
//	const DB_USER = 'dd_travel';
//	const DB_PASS = 'Lsr-auQ/6q4mkM8y';

	if (!DBQuery::instance()->State()) die('MySQLi database connection error! Code: ' . DBQuery::instance()->GetErrorCode());