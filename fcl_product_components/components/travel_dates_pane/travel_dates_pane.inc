<?php
/**
 * @file
 * Travel Dates pane theming functions.
 */

module_load_include('inc', 'fcl_product', 'fcl_product.utils');

/**
 * Implements hook_preprocess_HOOK().
 */
function fcl_product_components_preprocess_travel_dates_pane(&$vars) {
  $product = $vars['product'];
  $travel_dates = $product->travel_dates;
  $extra_info = $product->extra_info;
  $duration = $product->duration;
  $category = fcl_utilities_slugify($product->category);
  $vars['classes_array'] = array(
    'travel-dates-pane',
    'travel-dates-pane--' . $category,
  );
  $vars['title_attributes_array'] = array(
    'class' => array('travel-dates-pane__title'),
  );
  $vars['theme_hook_suggestions'][] = 'travel_dates_pane__' . $category;

  $travel_dates = _fcl_product_components_travel_dates($category, $extra_info, $travel_dates, $duration);

  $travel_dates_headings = array(
    'date_heading' => t('Dates'),
    'availability_heading' => t('Availability'),
    'price_heading' => t('Price'),
    'blank_heading' => '',
  );

  $vars['travel_dates_headings'] = array(
    '#theme' => 'fcl_travel_dates_heading__tour',
    '#content' => $travel_dates_headings,
    '#has_travel_dates' => TRUE,
  );

  $vars['travel_dates'] = array(
    '#theme' => 'fcl_item_list',
    '#type' => 'fcl_travel_dates_item__tour',
    '#content' => $travel_dates,
  );
}

/**
 * Get the array keys from the `extra_info` JSON structure.
 *
 * Different suppliers and categories use different travel date keys.
 *
 * @param string $category
 *   The product category.
 * @param array $extra_info
 *   JSON decoded `extra_info` string.
 *
 * @return array
 *   Contains the `id`, `start`, and `end` keys of the `extra_info` data.
 */
function _fcl_product_components_extra_info_keys($category, $extra_info) {
  $keys = array();

  switch ($category) {
    case 'tour':
      $keys['id'] = current(array_keys($extra_info));

      if ($keys['id'] === 'traveldateprices') {
        $keys['start'] = 'start';
        $keys['end'] = 'end';
      }

      if ($keys['id'] === 'traveldaterange') {
        $keys['start'] = 'availability_start';
        $keys['end'] = 'availability_end';
      }
      break;

    case 'air_transportation':
      $keys['id'] = 'traveldaterange';
      $keys['start'] = 'depart_start';
      $keys['end'] = 'depart_end';
      break;

    case 'holiday_package':
      $keys['id'] = 'traveldaterange';
      $keys['start'] = 'availability_start';
      $keys['end'] = 'availability_end';
      break;
  }

  return $keys;
}

/**
 * Create an array of product travel dates.
 *
 * @param string $category
 *   The product category.
 * @param string $extra_info
 *   Stringified JSON array of travel dates.
 * @param string $travel_dates
 *   The product travel date range.
 * @param array $duration
 *   The product duration for calculcating end dates.
 *
 * @return array
 *   List of start/end dates, price, and availability.
 */
function _fcl_product_components_travel_dates($category, $extra_info, $travel_dates, $duration) {
  $extra_info = drupal_json_decode($extra_info);
  $travel_dates_list = array();
  $now = REQUEST_TIME;

  // Fallback to travel dates if no extra info.
  if (empty($extra_info)) {
    // Extract a value from the travel dates field.
    $travel_dates = fcl_product_utils_parse_travel_dates($travel_dates);
    if (empty($travel_dates)) {
      // Return a default message if no extra info or travel dates exist.
      return array(
        '#theme' => 'container',
        '#attributes' => array(
          'class' => array('fcl-travel-dates-item__enquire-markup'),
        ),
        '#markup' => t('Travel dates subject to availability. Please !enquire for the latest information.', array(
          '!enquire' => '<a class="fcl-travel-dates-item__link" href="#enquire">contact us</a>',
        )),
      );
    }

    // Add start/end date values to travel dates list.
    $travel_dates_list[] = array(
      'start' => array(
        'date' => date('M D d Y', $travel_dates['start']),
        'raw' => $travel_dates['start'],
      ),
      'end' => array(
        'date' => date('M D d Y', $travel_dates['end']),
        'raw' => $travel_dates['end'],
      ),
    );
  }
  else {
    // Extact the id, start, and end keys from `$extra_info`.
    $extra_info_keys = _fcl_product_components_extra_info_keys($category, $extra_info);

    // Allow soft integration with react forms if its available.
    // This avoids having to do a hard dependency on this module to
    // the react forms.
    $support_react_form_integration = module_exists('fcc_react_forms');

    foreach ($extra_info[$extra_info_keys['id']] as $value) {
      // Can't do anything with a missing start date.
      if (empty($value[$extra_info_keys['start']])) {
        continue;
      }

      $travel_dates_item = array();
      $start = strtotime($value[$extra_info_keys['start']]);

      // Skip items already started or too far in the future.
      if ($start < $now || $start > strtotime('+1 year')) {
        continue;
      }

      if (!empty($value[$extra_info_keys['end']])) {
        $end = strtotime($value[$extra_info_keys['end']]);
      }
      elseif (preg_match('/(\d{1,2})/', $duration, $match)) {
        // Calculate end date based on duration.
        // Subtracting one day as there will be an extra day for this type.
        $end = strtotime('+' . $match[1] - 1 . ' day', $start);
      }
      else {
        // Can't do anything with a missing end date.
        continue;
      }

      $travel_dates_item['start'] = array(
        'date' => date('M D d Y', $start),
        'raw' => $start,
      );
      $travel_dates_item['end'] = array(
        'date' => date('M D d Y', $end),
        'raw' => $end,
      );

      // Clean up price format.
      if (isset($value['price']) && $value['price'] > 0) {
        $travel_dates_item['price'] = number_format($value['price']);
      }

      // Format availability text.
      if (isset($value['status'])) {
        $travel_dates_item['status'] = '<span class="' . drupal_html_class($value['status']) . '">' . $value['status'] . '</span>';
      }

      // Link attributes.
      // We have used fragment and external here to append
      // #enquire to the current url.
      $link_attributes = array(
        'fragment' => 'enquire',
        'external' => TRUE,
        'attributes' => array(
          'class' => array('fcl-travel-dates-item__link'),
        ),
      );

      // If react form integration is supported (the site has the fcc
      // react forms enabled).
      if ($support_react_form_integration) {
        $form_integration_data = array(
          'departDate' => $travel_dates_item['start']['raw'] * 1000,
          'returnDate' => $travel_dates_item['end']['raw'] * 1000,
          'questions' => t('I am interested in travelling from @start-date to @end-date @price.', array(
            '@start-date' => $travel_dates_item['start']['date'],
            '@end-date' => $travel_dates_item['end']['date'],
            '@price' => !empty($travel_dates_item['price']) ? 'from $' . $travel_dates_item['price'] : '',
          )),
        );
        $link_attributes['attributes'] = array_merge($link_attributes['attributes'], fcc_react_forms_build_update_attributes('click', $form_integration_data, 'Form/Enquiry/General'));
      }

      // Pass the link on to the travel dates list.
      $travel_dates_item['link'] = l(t('Enquire'), '', $link_attributes);
      $travel_dates_list[] = $travel_dates_item;
    }
    // Add the js for the form interface.
    if ($support_react_form_integration) {
      fcc_react_forms_include_form_update_scripts();
    }

    // Sort the travel dates chronologically.
    usort($travel_dates_list, '_fcl_product_components_sort_travel_dates');
  }

  return $travel_dates_list;
}

/**
 * Sort the travel date list by chronological order.
 */
function _fcl_product_components_sort_travel_dates($a, $b) {
  if ($a['start']['raw'] === $b['start']['raw']) {
    return 0;
  }

  return ($a['start']['raw'] > $b['start']['raw']) ? 1 : -1;
}
