<?php
class StoryHeadingTest extends PHPUnit_Framework_TestCase {
  protected static function getMethod($name) {
    $class = new ReflectionClass('App\StoryHeading');
    $method = $class->getMethod($name);
    $method->setAccessible(true);
    return $method;
  }

  public function setUP() {
    $this->dom = new DOMDocument();
    $this->h2 = $this->dom->createElement('h2', 'Test Heading');
    $this->a = $this->dom->createElement('a');
    $this->a->setAttribute('href', 'http://test-href.html');
  }

  public function tearDown() {
    unset($this->dom);
    unset($this->h2);
    unset($this->a);
  }

  public function test_contruct() {
    $this->h2->appendChild($this->a);
    $story_heading = new App\StoryHeading($this->h2);

    $this->assertEquals(
      'Test Heading',
      $story_heading->heading,
      'Object should contain the correct heading property.'
    );

    $this->assertEquals(
      'http://test-href.html',
      $story_heading->href,
      'Object should contain the correct href property.'
    );
  }

  public function test_ensure_href() {
    $this->a->appendChild($this->h2);
    $story_heading = $this->getMockBuilder('App\StoryHeading')
      ->disableOriginalConstructor()
      ->setMethods()
      ->getMock();
    $ensureHref = self::getMethod('ensureHref');
    $ensureHref->invokeArgs($story_heading, [$this->h2]);
    $this->assertEquals(
      'http://test-href.html',
      $story_heading->href,
      'When anchor tag is outside of h2 tag, object should contain the correct href property.'
    );
  }
}
