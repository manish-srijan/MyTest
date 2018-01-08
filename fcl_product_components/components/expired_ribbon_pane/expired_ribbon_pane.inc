<?php

/**
 * @file
 * Expired Product theming functions.
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function fcl_product_components_preprocess_expired_ribbon_pane(&$vars) {
  $product = $vars['product'];
  $category = fcl_utilities_slugify($product->category);

  // Render the expired ribbon content.
  $vars['product_sku'] = t('Deal Number') . ' ' . $product->sku;
  $vars['expired_package'] = t('Expired Package');
  $vars['classes_array'] = [
    'fcl-expired-ribbon-pane',
    'fcl-expired-ribbon-pane--' . $category,
  ];
  $vars['title_attributes_array'] = [
    'class' => ['expired-ribbon-pane__title'],
  ];
  $vars['theme_hook_suggestions'][] = 'expired_ribbon_pane';
}
