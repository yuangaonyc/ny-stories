<?php
require './lib/html_parser.class.inc';
require './lib/story_heading.class.inc';

# Fetch HTML content and filter target story heading tags
$html = new HTMLParser('https://www.nytimes.com');
$story_headings = $html->getStoryHeadings();

# Turn each story heading element in the array into an object
function objectify($story_heading) {
  return new StoryHeading($story_heading);
}
$story_headings = array_map('objectify', $story_headings);

# Output JSON data
echo json_encode($story_headings);
