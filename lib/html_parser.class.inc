<?php
class HTMLParser {
  public $dom;

  public function __construct($url) {
    // Get HTML content using cURL
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_HEADER, false);
    $output = curl_exec($ch);
    if ($output === false) {
      echo 'cURL Error: ' . curl_error($ch);
    }
    curl_close($ch);

    // Set instance variable dom
    $this->dom = new DOMDocument();
    @$this->dom->loadHTML($output);
  }

  # Return all target story heading tags in an array
  public function getStoryHeadings() {
    $h2_tags = $this->dom->getElementsByTagName('h2');
    $story_headings = array();

    # Add to output array if class attribute contains 'story-heading'
    foreach ($h2_tags as $h2_tag) {
      $class_attribute = $h2_tag->getAttribute('class');
      if (strpos($class_attribute, 'story-heading') !== false) {
        array_push($story_headings, $h2_tag);
      }
    }

    return $story_headings;
  }
}
