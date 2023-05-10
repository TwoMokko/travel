<?php

    namespace Base\DB;

    class QueryMySQLi extends Query {
        public static function select(): QuerySelectMySQLi { return new QuerySelectMySQLi(); }
//        public static function insert(): QueryInsertMySQLi { return new QueryInsertMySQLi(); }
//        public static function update(): QueryUpdateMySQLi { return new QueryUpdateMySQLi(); }
//        public static function delete(): QueryDeleteMySQLi { return new QueryDeleteMySQLi(); }

    }

    class QuerySelectMySQLi extends QuerySelect {
        private array $fields;
        private string $table;
        private string $table_alias;
        private array $leftJoin;
        private array $where;
        private string $limit;
        private string $order;
        private string $group;

        public function execute(): string {
           //SELECT `field1`, `field2` FROM `table` WHERE `id` > 3 AND `name` LIKE '%ан'
            $fields_list = []; foreach ($this->fields as $field) $fields_list[] = "`{$field}`";
            $fields = implode(', ', $fields_list);

            $where = ($this->where) ? ' WHERE ' . implode(' AND ', $this->where) : '';

            $leftJoin = '';
            foreach ($this->leftJoin as $item) $leftJoin .= " LEFT JOIN `{$item['table']}` ON ({$item['on']})";

            return "SELECT {$fields} FROM `{$this->table}`{$leftJoin}{$where}";
        }

        public function fields(string ...$fields): self {
            $this->fields = $fields;
            return $this;
        }

        public function table(string $table): self {
            $this->table = $table;
            return $this;
        }

        public function where(string ...$where): self {
            $this->where = $where;
            return $this;
        }

        public function leftJoin(string $table, string $on): self {
            $this->leftJoin[] = ['table' => $table, 'on' => $on];
            return $this;
        }

        public function order(): self {
            return $this;
        }

        public function limit(): self {
            return $this;
        }

        public function group(): self {
            return $this;
        }

    }

//    QueryMySQLi::select()->fields('id', 'name', 'date_cr')->table('student')->where('`id` > 3', "`name` LIKE '%ан'")->leftJoin('group', '`student`.`gid` = `group`.`id`')->leftJoin('university', '`student`.`uid` = `university`.`id`')->execute();

//    class QueryInsertMySQLi extends QueryInsert {  }
//
//    class QueryUpdateMySQLi extends QueryUpdate {  }
//
//    class QueryDeleteMySQLi extends QueryDelete {  }