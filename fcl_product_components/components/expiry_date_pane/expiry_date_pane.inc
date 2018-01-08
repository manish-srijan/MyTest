<?php

/**
 * @file
 * Product commerce expiry date pane theme hook file.
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function fcl_product_components_preprocess_expiry_date_pane(&$vars) {
  $product = $vars['product'];
  $category = fcl_utilities_slugify($product->category);
  $vars['classes_array'] = [
    'expiry-date-pane',
    'expiry-date-pane--' . $category,
  ];
  $vars['title_attributes_array'] = [
    'class' => ['expiry-date-pane__title'],
  ];
  $vars['theme_hook_suggestions'][] = 'expiry_date_pane__' . $category;

  // Set expiry date icon.
  $vars['expiry_date_icon'] = [
    'icon' => [
      'fcl_icon_hourglass_empty' => [
        '#theme' => 'fcl_icon',
        '#icon_name' => 'hourglass_empty',
      ],
    ],
    'classes' => 'expiry-date-pane__icon',
  ];

  // Expiry date label and classes to be used.
  $vars['expiry_date_text_label'] = [
    'content' => [
      '#markup' => t('This deal expires on the'),
    ],
    'classes' => 'expiry-date-pane__text-label',
  ];

  $vars['expiry_date'] = NULL;
  if (is_numeric($product->commerce_expiry_date)) {
    // Appending 23 hours 59 mins 59 seconds (In timestamp format) to expiry
    // timestamp, so that the product commerce expiry date pane displays correct
    // expiry time i.e end of the day. Currently, product commerce expiry
    // datetime defaults to 12 AM which does not make sense.
    $vars['expiry_date'] = format_date($product->commerce_expiry_date + 86399, 'custom', 'dS M Y');
  }
}
