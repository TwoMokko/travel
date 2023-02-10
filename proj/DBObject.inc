<?php

	namespace Proj;

	use Base\DB\DBObjectMySQLi;

	class DBObject extends DBObjectMySQLi {
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

	DBObject::init('localhost', 'dd_travel', 'Lsr-auQ/6q4mkM8y', 'dd_travel');

	if (!DBObject::instance()->State()) die('MySQLi database connection error! Code: ' . DBObject::instance()->GetErrorCode());