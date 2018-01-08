<?php

/**
 * @file
 * Itinerary theming functions.
 *
 * Itineraries are build from either of two ways:
 * 1. From well formatted fcl_procat_product_itineraries (if available)
 * 2. Extracted from product description field.(Otherwise)
 */

include_once __DIR__ . '/itinerary_formatters.inc';

/**
 * Implements hook_preprocess_HOOK().
 */
function fcl_product_components_preprocess_itinerary_pane(&$vars) {
  $product = $vars['product'];
  // Early return if no itinerary or no description.
  if (empty($product->itineraries) && empty($product->product_description)) {
    return NULL;
  }

  $category = fcl_utilities_slugify($product->category);
  $vars['category'] = $category;
  $vars['brand'] = $product->brand;
  $vars['itinerary_data'] = array();
  $vars['classes_array'] = array(
    'fcl-itinerary-pane',
    'fcl-itinerary-pane--' . $category,
  );
  $vars['title_attributes_array'] = array(
    'class' => array('fcl-itinerary-pane__title'),
  );
  $vars['theme_hook_suggestions'][] = 'itinerary_pane__' . $category;

  if (!empty($product->itineraries)) {
    // If itineraries available from `fcl_procat_product_itinerary` entity then
    // display it.
    _fcl_product_components_itinerary($vars);
  }
  else {
    // If itineraries not available, extract it from product description.
    _fcl_product_components_itinerary_from_description($vars);
  }

  // Add map button with itinerary.
  _fcl_product_components_add_map_button($vars);
}

/**
 * Callback for building itinerary from `fcl_procat_product_itinerary` entity.
 *
 * @param array $vars
 *   Array passed to fcl_product_components_preprocess_itinerary_pane.
 */
function _fcl_product_components_itinerary(&$vars) {
  $product = $vars['product'];
  switch ($vars['category']) {
    case 'cruise':
      // For cruise display itinerary as list.
      $itineraries = array_map('_fcl_product_components_array_map_cruise_itineraries', $product->itineraries);

      // Define headings for cruise itineraries.
      $itinerary_headings = array(
        'day_heading' => t('Day'),
        'date_heading' => t('Date'),
        'destination_heading' => t('Destination'),
        'arrival_heading' => t('Arrive'),
        'departure_heading' => t('Depart'),
      );

      $vars['itinerary_headings'] = array(
        '#theme' => 'fcl_itinerary_heading__cruise',
        '#content' => $itinerary_headings,
        '#has_itinerary' => TRUE,
      );

      $vars['itinerary'] = array(
        '#theme' => 'fcl_item_list',
        '#type' => 'fcl_itinerary_item__cruise',
        '#content' => $itineraries,
      );
      break;

    case 'tour':
      // For tour display itinerary as accordion.
      $vars['itinerary_data'] = array_map('_fcl_product_components_array_map_tour_itineraries', $product->itineraries);
      // Make itinerary as accordion from itinerary data.
      _fcl_product_components_itinerary_accordion($vars);
      break;
  }
}

/**
 * Callback for building itinerary from product description.
 *
 * @param array $vars
 *   Array passed to fcl_product_components_preprocess_itinerary_pane.
 */
function _fcl_product_components_itinerary_from_description(&$vars) {
  $product = $vars['product'];
  $supplier = $vars['brand'];
  // This "category - supplier" string will be used to choose formatters.
  $category_supplier = "{$vars['category']} - $supplier";
  $formatter_applied = FALSE;
  $fns = array();

  // Get list of available itinearry formatter functions.
  $formatters = _fcl_product_components_itinerary_formatters();
  // Make a list of formatter functions to be applied on this product.
  foreach ($formatters as $formatter => $category_suppliers) {
    if (in_array($category_supplier, $category_suppliers)) {
      $fns[] = $formatter;
    }
  }

  // Sometimes text has non ASCII characters convert them if possible
  // otherwise ignore them. Non ASCII chars may break regex.
  $description = iconv('UTF-8', 'ASCII//TRANSLIT//IGNORE', $product->product_description);

  // Apply formatters on product description.
  foreach ($fns as $fn) {
    if (is_callable($fn)) {
      $description = $fn($description);
      $formatter_applied = TRUE;
    }
  }

  // Format itinerary data as expected for accordion.
  $vars['itinerary_data'] = $formatter_applied ? _fcl_product_components_itinerary_format($description) : array(array('description' => $description));
  // Make itinerary as accordion from itinerary data.
  _fcl_product_components_itinerary_accordion($vars);
}

/**
 * Callback to array_map itineraries list.
 *
 * @param object $itinerary
 *   A single itinerary item object.
 *
 * @return array
 *   An array of itinerary item tpl variables.
 */
function _fcl_product_components_array_map_tour_itineraries($itinerary) {
  // Extract required object values for the itinerary pane into an array.
  return array(
    'day_range' => $itinerary->day_range,
    'destination_name' => $itinerary->destination_name,
    'description' => $itinerary->description,
  );
}

/**
 * Callback to array_map itineraries list.
 *
 * @param object $itinerary
 *   A single itinerary item object.
 *
 * @return array
 *   An array of itinerary item tpl variables.
 */
function _fcl_product_components_array_map_cruise_itineraries($itinerary) {
  // Extract required object values for the itinerary pane into an array.
  return array(
    'day_range' => $itinerary->day_range ? 'Day ' . $itinerary->day_range : '',
    'date' => $itinerary->datestamp ? fcl_utilities_get_user_time($itinerary->datestamp, 'd M y') : '',
    'destination_name' => $itinerary->destination_name ? $itinerary->destination_name : '',
    'arrive_time' => $itinerary->arrival_time ? format_date(strtotime($itinerary->arrival_time), 'custom', 'g:i A') : '',
    'departure_time' => $itinerary->departure_time ? format_date(strtotime($itinerary->departure_time), 'custom', 'g:i A') : '',
  );
}

/**
 * Return list of available formatter.
 *
 * @return array
 *   Array of formatters where key is formatter function name and value is array
 *   of  "$category - $supplier" strings. This string denote to products of this
 *   "$category - $supplier" to which this formatter will be applied. You can
 *   apply multiple formatters by adding "$category - $supplier" to that
 *   formatter function array. Please note that this string should exactly match
 *   with "$category - $supplier". e.g., `tour - Escape Travel` including hyphen
 *   and space.
 */
function _fcl_product_components_itinerary_formatters() {
  return array(
    '_itinerary_formatter__strip_tags_and_new_line_splitter' => array(
      // Tour - $supplier.
      'tour - Escape Travel',
      'tour - My Adventure Store - Intrepid JV',
      // Cruise - $supplier.
      'cruise - Escape Travel',
      'cruise - My Adventure Store - Intrepid JV',
    ),
    '_itinerary_formatter__div_content_extracter' => array(
      'tour - Topdeck Tours',
    ),
    '_itinerary_formatter__strip_tags_and_br_tag_splitter' => array(
      'tour - Backroads Touring',
      'tour - Exodus',
      'tour - Peregrine Adventures',
      'tour - Intrepid Tours',
      'tour - The Travel Corporation',
    ),
    '_itinerary_formatter__br_breaker_and_new_line_splitter' => array(
      'tour - Australian Pacific Touring',
    ),
  );
}

/**
 * Return itinerary information as accordion.
 *
 * This function expects that itinerary information is available under
 * $vars['itinerary_data'] as an array.
 *
 * @param array &$vars
 *   Array passed to fcl_product_components_preprocess_itinerary_pane.
 */
function _fcl_product_components_itinerary_accordion(&$vars) {
  $tabs = array();
  // Build the data array of tab elements with the
  // list of itinerary data. These use individual theme
  // functions to allow for unique markup and styles.
  foreach ($vars['itinerary_data'] as $itinerary) {
    $tabs[] = array(
      'title_classes_array' => array(
        // These classes define items as Elements
        // as well as a Block because each item will
        // also contain Elements.
        'fcl-itinerary-list__item',
        'fcl-itinerary-item',
      ),
      'title' => theme('fcl_itinerary_heading__' . $vars['category'], array(
        'content' => array(
          'day_range' => isset($itinerary['day_range']) ? $itinerary['day_range'] : '',
          'destination_name' => isset($itinerary['destination_name']) ? $itinerary['destination_name'] : '',
        ),
      )),
      'content' => theme('fcl_itinerary_description__' . $vars['category'], array(
        'content' => array(
          'description' => isset($itinerary['description']) ? $itinerary['description'] : '',
        ),
      )),
    );
  }

  // Render the tabs array with Foundie Tabs
  // and set responsive behaviour options.
  $vars['itinerary'] = theme('foundie_tabs', array(
    'tabs' => $tabs,
    'attributes_array' => array(
      'class' => array(
        // These classes define the list as an Element
        // as well as a Block because the list will
        // also contain item Elements.
        'fcl-itinerary-pane__list',
        'fcl-itinerary-pane__list--' . $vars['category'],
        'fcl-itinerary-list',
        'fcl-itinerary-list--' . $vars['category'],
      ),
      'data-readmore' => 'fcl-itinerary-list',
    ),
    'navigation' => FALSE,
    'responsive' => 'accordion',
    'breakpoints' => array(
      'small' => 'accordion',
    ),
  ));

  // Ensure the read more library is included for the Foundie List to work.
  libraries_load('foundation.readMore');
}

/**
 * Format itineraries data with valid keys.
 *
 * This function takes the itineraries data array and return itineraries array
 * where each item is individual itinerary with following keys:
 * day_range
 * destination_name
 * description.
 *
 * @param array $description
 *   Itineraries data array.
 *
 * @return array
 *   Well formatted itineraries array.
 */
function _fcl_product_components_itinerary_format($description) {
  $itinerary_count = -1;
  $itineraries = array();

  // Trim leading and trailing whitespaces.
  $description = array_map('trim', $description);
  // Remove empty entries from array.
  $description = array_filter($description);

  // Loop through itinerary information array and extract itinerary day,
  // itinerary title and itinerary description.
  foreach ($description as $text) {
    // Check if current text item is itinerary title.
    // Regex try to match:
    // ^(?:days)?\s?[0-9-]+ = String with Day(s) or not followed by optional
    // space followed by number.
    // [:.\s] = Any of these character optional.
    // [A-z0-9\s,\-\?]+ = Followed by text containing any of these (,.-?) one or
    // more times.
    // (?:<\s*br[\/\s]*>)* = Followed 0 or more `<br>` tags even if tag is
    // incorrect.
    //
    // Few itinerary title examples accepted by this regex:
    // Days 1
    // Days 2: Some place
    // Days 3. Some place, with - extra place
    // 4 Interesting place - with stop.
    preg_match('/(^(?:days?)?\s?[0-9-]+)[:.\s]?([A-z0-9\s,\-\?]+)?/i', $text, $matches);
    if (!empty($matches)) {
      // Increment count only if this is itinerary title.
      $itinerary_count++;
      $itineraries[$itinerary_count]['day_range'] = $matches[1];
      $itineraries[$itinerary_count]['destination_name'] = isset($matches[2]) ? $matches[2] : '';
    }
    else {
      // If this is not itinerary title then this is itinerary description.
      $itineraries[$itinerary_count]['description'] = isset($itineraries[$itinerary_count]['description']) ? $itineraries[$itinerary_count]['description'] . " $text" : $text;
    }
  }

  return $itineraries;
}

/**
 * Add map button with itinerary header.
 *
 * @param array &$vars
 *   Array passed to fcl_product_components_preprocess_itinerary_pane().
 */
function _fcl_product_components_add_map_button(&$vars) {
  $product = $vars['product'];
  // Show itinerary map button only for cruise.
  if (!empty($product->field_product_media_img2) && $vars['category'] === 'cruise') {
    $supplier_map = file_create_url($product->field_product_media_img2[LANGUAGE_NONE][0]['uri']);
    $vars['header'] = array(
      '#theme_wrappers' => array('container'),
      '#markup' => l(
        t('See Map'),
        $supplier_map,
        array(
          'attributes' => array(
            'target' => '_blank',
            'class' => 'fcl-itinerary-map-button__link pui-btn-accent waves-effect waves-light',
          ),
        )
      ),
      '#attributes' => array(
        'class' => array('fcl-itinerary-map-button'),
      ),
    );
  }
}
