<?php

/**
 * @file
 * Airline logo theming functions.
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function fcl_product_components_preprocess_gne_reference_pane(&$vars) {
  $product = $vars['product'];
  $category = fcl_utilities_slugify($product->category);
  $vars['classes_array'] = [
    'gne-reference-pane',
    'gne-reference-pane__' . $category,
  ];
  $vars['theme_hook_suggestions'][] = 'gne_reference_pane__' . $category;

  $vars['title_attributes_array'] = [
    'class' => [
      'gne-reference-pane__title',
    ],
  ];

  $vars['gne_reference'] = '';
  if ($product->oneway_flag) {
    $vars['gne_reference'] = $product->gne_reference;
  }
}
