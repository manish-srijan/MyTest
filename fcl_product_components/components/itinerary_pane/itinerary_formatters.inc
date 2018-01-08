<?php

/**
 * @file
 * Itinerary formatter functions to extract data from product description.
 *
 * Products of different category(e.g., tours, cruise etc) from different
 * suppliers(e.g., topdeck, ET, backroad, APT etc) has different format
 * of product description. These formatter functions accept product description
 * and return an itinerary array which later can be passed to
 * _fcl_product_components_itinerary_format() function.
 *
 * Formatter function index:
 * _itinerary_formatter__div_content_extracter
 * _itinerary_formatter__strip_tags_and_new_line_splitter
 * _itinerary_formatter__strip_tags_and_br_tag_splitter
 * _itinerary_formatter__br_breaker_and_new_line_splitter
 */

/**
 * Formatter function to extract itinerary from div.
 *
 * Targeted category - supplier:
 * - `tour - Topdeck Tours`
 *
 * Expected format of product description:
 * For `tour - Topdeck Tours`
 * <div class="itinerary-title">Day 1 Itinerary 1 title</div>
 * <div class="itinerary-description">Itinerary 1 description</div>
 * <div class="itinerary-title">Day 2 Itinerary 2 title</div>
 * <div class="itinerary-description">Itinerary 2 description</div>
 * ...
 *
 * @param string $description
 *   The product description.
 *
 * @return array
 *   Array of itinerary from product description with unnecessary markup
 *   stripped.
 */
function _itinerary_formatter__div_content_extracter($description) {
  // Extract all the text contained within <div> tags.
  // Regex try to match:
  // <\s*?div\b[^>]*> = Any `<div>` tag.
  // (\X*?) = Followed by any string including new line character.
  // <\/div\b[^>]*> = Followed by closing `</div>` tag.
  preg_match_all('/<\s*?div\b[^>]*>(\X*?)<\/div\b[^>]*>/i', $description, $matches);
  $description = isset($matches[1]) ? $matches[1] : array();

  return $description;
}

/**
 * Formatter function to strip tags and split by new line.
 *
 * Targeted category - supplier:
 * - `tour - Escape Travel`
 * - `tour - My Adventure Store - Intrepid JV`
 * - `cruise - Escape Travel`
 *
 * Expected format of product description:
 * For `tour - Escape Travel`:
 * Day 1 itinerary title 1<br>
 * Itinerary description 1<br>
 * Day 2 Itinerary title 2<br>
 * Itinerary description 2<br>
 * ...
 * Sometimes it may include <br></br> tags inconsistently.
 *
 * For `tour - My Adventure Store - Intrepid JV`:
 * Day 1 Itinerary title 1<br />
 * Itinerary description 1<br />
 * Day 2 Itinerary title 2<br />
 * Itinerary description 2<br />
 * ...
 * Sometimes it may include <br></br> tags inconsistently.
 *
 * For `cruise - Escape Travel`:
 * <strong>Day 1: Itinerary title 1.</strong><br />
 * Itinerary description 1.<br />
 * Itinerary few more description 1.<br />
 * <br /><br />
 * <strong>Day 2: Itinerary title 2.</strong><br />
 * Itinerary description 2.<br />
 * Itinerary few more description 2.<br />
 * <br /><br />
 *
 * @param string $description
 *   The product description.
 *
 * @return array
 *   Array of itinerary from product description with unnecessary markup
 *   stripped.
 */
function _itinerary_formatter__strip_tags_and_new_line_splitter($description) {
  // Strip all the tags.
  $description = strip_tags($description);
  // Split by new line to get itinerary information as array.
  $description = preg_split('/\n/', $description);

  return $description;
}

/**
 * Formatter function to strip tags and split by <br> tag.
 *
 * Targeted category - supplier:
 * - `tour - Backroads Touring`
 * - `tour - Exodus`
 *
 * Expected format of product description:
 * For `tour - Backroads Touring`:
 * Day 1 itinerary title 1 <br><p>Itinerary description 1</p>
 * Day 2 itinerary title 2 <br><p>Itinerary description 2</p>
 * ...
 *
 * For `tour - Exodus`:
 * Day 1<br>Itinerary description 1.<br>Day 2<br>Itinerary description 2<br>
 * Day 3<br>Itinerary description 3<br>
 *
 * Description does not contains new line characters and sometimes description
 * may contain extra html tags and inline style.
 *
 * @param string $description
 *   The product description.
 *
 * @return array
 *   Array of itinerary from product description with unnecessary markup
 *   stripped.
 */
function _itinerary_formatter__strip_tags_and_br_tag_splitter($description) {
  // Strip all the tags except `<br>` and `<p>`tag.
  $description = strip_tags($description, '<br><p>');
  // Split by <br> tag to get itinerary information as array.
  $description = preg_split('/<br\s?\/?\s?>/', $description);
  // Remove unnecessary tags.
  $description = array_map('strip_tags', $description);
  return $description;
}

/**
 * Formatter function to break at br and split at new line.
 *
 * This function add new line character at each <br> tag and then split
 * by that new line character.
 *
 * Targeted category - supplier:
 * - `tour - Australian Pacific Touring`
 *
 * Expected format of product description:
 * Day 1: Itinerary title 1<br>Itinerary description 1 containing <br> tags
 * Day 2: Itinerary title 2<br>Itinerary description 2 containing <br> tags.
 *
 * @param string $description
 *   The product description.
 *
 * @return array
 *   Array of itinerary from product description with unnecessary markup
 *   stripped.
 */
function _itinerary_formatter__br_breaker_and_new_line_splitter($description) {
  // Match text with provided regex and replace match by appending new line
  // characters so that later can be split by new line characters.
  //
  // Regex try to match:
  // days?\s?[0-9-]+ = String with Day(s) followed by optional space followed by
  // number.
  // [:.\s] = Any of these character optional.
  // [A-z0-9\s,\-\?]+ = Followed by text containing any of these (,.-?) one or
  // more times.
  // (?:<\s*br[\/\s]*>)* = Followed by 0 or more `<br>` tags even if tag is
  // incorrect.
  $description = preg_replace_callback('/(days?\s?[0-9-]+[:.\s]?[A-z0-9\s,\-\?]+)(?:<\s*br[\/\s]*>)*/i', function ($matches) {
    if (isset($matches[1])) {
      return "\n" . $matches[1] . "\n";
    }
  }, $description);

  $description = preg_split('/\n/', $description);

  return $description;
}
