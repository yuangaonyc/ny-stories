<?php
class StoryHeading {
  public $heading;
  public $href;

  public  function __construct($dom_element) {
    # Set heading attribute
    $this->heading = $dom_element->textContent;

    # Look for href in child nodes
    foreach ($dom_element->childNodes as $childNode) {
      if (@$childNode->tagName === 'a') {
        $this->href = $childNode->getAttribute('href');
      }
    }

    # If didn't find href, look for it in parent node
    if (!$this->href) {
      $this->ensure_href($dom_element);
    }
  }

  # Look in parent node to ensure href exist
  private function ensure_href($dom_element) {
    $this->href = $dom_element->parentNode->getAttribute('href');
  }
}
