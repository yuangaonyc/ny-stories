<?php

class Address {
  const ADDRESS_TYPE_RESIDENCE = 1;
  const ADDRESS_TYPE_BUSINESS = 2;
  const ADDRESS_TYPE_PARK = 3;

  static public $valid_address_types = array(
    Address::ADDRESS_TYPE_RESIDENCE => 'Residence',
    Address::ADDRESS_TYPE_BUSINESS => 'Business',
    Address::ADDRESS_TYPE_PARK => 'Park',
  );

  public $street_address_1;
  public $street_address_2;
  public $city_name;
  public $subdivision_name;
  protected $_postal_code;
  public $country_name;
  protected $_address_id;
  protected $address_type_id;
  protected $_time_created;
  protected $_time_updated;

  function __construct($data = array()) {
    $this->_time_created = time();

    if (!is_array($data)) {
      trigger_error('Unable to construct address with a  ' . get_class($name));
    }

    if (count($data) > 0) {
      foreach ($data as $name => $value) {
        if (in_array($name, array(
          'time_created',
          'time_updated',
        ))) {
          $name = '_' . $name;
        }
        $this->$name = $value;
      }
    }

  }

  function __toString() {
    return $this->display();
  }

  function __get($name) {
    if (!$this->_postal_code) {
      $this->_postal_code = $this->_postal_code_guess();
    }
    $protected_property_name = '_' . $name;
    if (property_exists($this, $protected_property_name)) {
      return $this->$protected_property_name;
    }

    trigger_error('Undefined property via _get: ' . $name);
    return NULL;
  }

  function __set($name, $value) {
      if ('address_type_id' == $name) {
        $this->_setAddressTypeId($value);
        return;
      }
      if ('postal_code' == $name) {
        $this->$name = $value;
        return;
      }

      trigger_error('Undefined or unallowed property via _set: ' .$name);
  }

  protected function _postal_code_guess() {
    $db = Database::getInstance();
    $mysqli = $db->getConnection();

    $sql_query = 'SELECT postal_code ';
    $sql_query .= 'FROM location ';

    $city_name = $mysqli->real_escape_string($this->city_name);
    $sql_query .= 'WHERE city_name = "' . $city_name . '" ';

    $subdivision_name = $mysqli->real_escape_string($this->subdivision_name);
    $sql_query .= 'AND subdivision_name = "' . $subdivision_name . '" ';

    $result = $mysqli->query($sql_query);

    if ($row = $result->fetch_assoc()) {
      return $row['postal_code'];
    }
  }

  function display() {
    $output = '';
    $output .= $this->street_address_1;
    if ($this->street_address_2) {
      $output .= '<br/>' . $this->street_address_2;
    }
    $output .= '<br/>';
    $output .= $this->city_name . ', ' . $this->subdivision_name;
    $output .= ' ' . $this->postal_code;
    $output .= '<br/>';
    $output .= $this->country_name;
    return $output;
  }

  static public function isValidAddressTypeId($address_type_id) {
    return array_key_exists($address_type_id, self::$valid_address_types);
  }

  protected function _setAddressTypeId($address_type_id) {
    if (self::isValidAddressTypeId($address_type_id)) {
      $this->address_type_id = $address_type_id;
    }
  }
}
