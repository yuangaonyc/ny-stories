<?php
namespace App;
class StoryHeading {
  public $heading;
  public $href;

  public  function __construct($dom_element) {
    # Set heading attribute
    $this->heading = trim($dom_element->textContent);

    # Look for href in child nodes
    foreach ($dom_element->childNodes as $childNode) {
      if (@$childNode->tagName === 'a') {
        $this->href = $childNode->getAttribute('href');
      }
    }

    # Keep looking in parent nodes to ensure href exists
    $this->ensureHref($dom_element);
  }

  # If didn't find href, look for it in its parent node
  private function ensureHref($dom_element) {
    while (!$this->href) {
      $this->href = $dom_element->parentNode->getAttribute('href');
      $dom_element = $dom_element->parentNode;
    }
  }
}
