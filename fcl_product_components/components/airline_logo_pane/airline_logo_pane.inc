<?php

/**
 * @file
 * Airline logo theming functions.
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function fcl_product_components_preprocess_airline_logo_pane(&$vars) {
  $product = $vars['product'];
  $category = fcl_utilities_slugify($product->category);
  $vars['classes_array'] = [
    'airline-logo-pane',
    'airline-logo-pane__' . $category,
  ];
  $vars['theme_hook_suggestions'][] = 'airline_logo_pane__' . $category;

  $vars['title_attributes_array'] = [
    'class' => [
      'airline-logo-pane__title',
    ],
  ];

  // Ensure that the airline code is valid before moving forward.
  $airline_code = $product->airline_name;
  if (property_exists($product, 'airline_code')) {
    $airline_code = $product->airline_code;
  }

  if (module_exists('fcl_airline') && !fcl_airline_validate_airline_code($airline_code)) {
    $airline_code = '';
  }

  // Set airline name incase of multiple airlines.
  if ($product->airline_name && strtolower($product->airline_name) === 'multi') {
    $vars['airline_logo'] = '';

    // Using airline multi text defined in theme hook definition.
    $vars['airline_name'] = $vars['airline_multi_text'];
  }
  else {
    $vars['airline_name'] = $product->airline_name;

    // Using airline logo size defined in theme hook definition.
    $vars['airline_logo'] = _fcl_product_components_get_airline_logo($airline_code, $product->airline_name, $vars['airline_logo_size']);
  }
}

/**
 * Helper function to fetch Airline logos.
 *
 * @param string $airline_code
 *   The Name of the Airline.
 * @param string $size
 *   The logo size you want.
 *
 * @return mixed
 *   Returns an Airline logo.
 */
function _fcl_product_components_get_airline_logo($airline_code, $airline_name, $size = NULL) {
  // Return early if fcl_airline module is not enabled.
  if (!module_exists('fcl_airline')) {
    return FALSE;
  }

  // Cache airline logo.
  $airline_logo = &drupal_static(__FUNCTION__);

  // Check if airline logo is already stored.
  if (isset($airline_logo)) {
    return $airline_logo;
  }

  $airline_entity = fcl_airline_entity_load_single(strtoupper($airline_code));
  // Return early if airline entity is empty.
  if (empty($airline_entity)) {
    return FALSE;
  }

  // Set airline image path and its attributes.
  $airline_image = $airline_entity->{$size};
  $airline_logo_attr = [
    'path' => $airline_image,
    'alt' => $airline_name,
    'attributes' => [
      'class' => array('airline-logo-pane__logo'),
    ],
  ];

  // Push logo back to respective variable (static cached).
  $airline_logo = theme('image', $airline_logo_attr);

  return $airline_logo;
}
