<?php
class Database {
  static private $_instance;

  static public function getInstance() {
    if (!self::$_instance) {
      self::$_instance = new self();
    }
    return self::$_instance;
  }

  private $_connection;

  public function __construct() {
    $this->_connection = new mysqli('localhost', 'root', 'password', 'sandbox');
    if (mysqli_connect_error()) {
      trigger_error('Failed to connect to MySQL: ' . mysqli_connect_error(), E_USER_ERROR);
    }
  }

  public function getConnection() {
    return $this->_connection;
  }

  private function __clone() {}
}
