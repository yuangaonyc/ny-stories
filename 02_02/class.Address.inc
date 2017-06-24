<?php

class Address {
  public $street_address_1;
  public $street_address_2;
  public $city_name;
  public $subdivision_name;
  protected $_postal_code;
  public $country_name;
  protected $_address_id;
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
      if ('postal_code' == $name) {
        $this->$name = $value;
        return;
      }

      trigger_error('Undefined or unallowed property via _set: ' .$name);
  }

  protected function _postal_code_guess() {
    return 'LOOKUP';
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
}
