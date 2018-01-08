<?php

/**
 * @file
 * Product SKU theming functions.
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function fcl_product_components_preprocess_product_sku_pane(&$vars) {
  $product = $vars['product'];
  $category = fcl_utilities_slugify($product->category);
  $vars['classes_array'] = [
    'fcl-product-sku-pane',
    'fcl-product-sku-pane--' . $category,
  ];
  $vars['title_attributes_array'] = [
    'class' => ['fcl-product-sku-pane__title'],
  ];
  $vars['theme_hook_suggestions'][] = 'product_sku_pane';

  // Defining markup for the SKU number so that its easy to
  // preprocess and override.
  $vars['sku'] = [
    'content' => [
      '#markup' => t('Deal Number: @sku', ['@sku' => $product->sku]),
    ],
    'classes' => 'fcl-product-sku-pane__deal-number',
  ];
}
