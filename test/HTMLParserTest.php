<?php
class HTMLParserTest extends PHPUnit_Framework_TestCase {
  public function test_construct() {
    $url = 'https://www.nytimes.com';
    $html_parser = new App\HTMLParser($url);

    $this->assertEquals(
      'DOMDocument',
      get_class($html_parser->dom),
      'Should set a DOMDocument object for the dom instance variable.'
    );

    $this->assertStringStartsWith(
      'The New York Times',
      $html_parser->dom->textContent,
      'DOMDocument should have The New York Times header in the content.'
    );
  }

  public function test_get_story_headings() {
    $html_parser = $this->getMockBuilder('App\HTMLParser')
      ->disableOriginalConstructor()
      ->setMethods()
      ->getMock();
    $html_parser->dom = new DOMDocument();
    $html_parser->dom->loadHTML(
      '<!DOCTYPE html>
      <html>
        <head>
          <meta charset="utf-8">
          <title></title>
        </head>
        <body>
          <h2 class="story-heading"><a href="https://www.nytimes.com/2017/06/25/us/politics/mitch-mcconnell-senate-health-care-bill.html">Senate Leaders Push on Health Bill; Opposition Gains Strength</a></h2>
        </body>
      </html>'
    );
    $result = $html_parser->getStoryHeadings();

    $this->assertEquals(
      1,
      count($result),
      'Output array should contain 1 DOMElement.'
    );

    $this->assertEquals(
      'h2',
      $result[0]->nodeName,
      'The selected DOMElement should be an h2 tag.'
    );

    $this->assertRegexp(
      '/story-heading/',
      $result[0]->getAttribute('class'),
      'The selected DOMElement should have "story-heading" as class value.'
    );
  }
}
