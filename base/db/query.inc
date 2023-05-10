<?php

    namespace Base\DB;

    abstract class Query {
        abstract static public function select();
//        abstract static public function insert();
//        abstract static public function update();
//        abstract static public function delete();
    }

    abstract class QueryExecute {
        abstract public function execute();
    }

    abstract class QuerySelect extends QueryExecute {  }

//    abstract class QueryInsert extends QueryExecute {  }
//
//    abstract class QueryUpdate extends QueryExecute {  }
//
//    abstract class QueryDelete extends QueryExecute {  }