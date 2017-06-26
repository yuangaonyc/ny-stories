# New York Stories

This is a php application, which extracts the story headings from the nytimes.com website and returns them in JSON format.

## Architecture

The app consists of two components:

 - **HTMLParser** : HTMLParser fetches the html content from the provided URL using cURL, turns it into DOMDocument, and then extracts the DOMElements that meet target conditions using php DOM manipulation.

 - **StoryHeading** : StoryHeading takes in a DOMElement, which is an h2 element with a child anchor tag or the other way around, and turns it into an object with heading and href properties.

By utilizing these two classes, html content is first fetched and filtered down to an array of DOMElements. The array is then passed into a map function, where each element of the array gets objectified and the href and heading information gets exposed. Finally, by JSON-encoding the array, which contains many custom story heading objects, the output data is generated.

## Assumptions

1. All story-heading tags have 'story-heading', and possibly more values, in their class attributes.

2. If a story-heading h2 tag doesn't have an anchor tag with href attribute in it's child nodes, the anchor tag exists in one of its ancestor nodes.

## Modules

 - php 7.0.18

 - phpunit 5.5.4
