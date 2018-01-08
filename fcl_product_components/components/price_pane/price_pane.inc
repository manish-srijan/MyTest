<?php

/**
 * @file
 * Price pane theming functions.
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function fcl_product_components_preprocess_fpc_price_pane(&$vars) {
  $product = $vars['product'];

  $rule = variable_get('fcl_price_pane_dual_rule');
  $was_label_change = variable_get('price_was_label_change');
  $vars['currency_symbol'] = variable_get('fcl_locale_currency_symbol');

  $category = fcl_utilities_slugify($product->category);
  $price = intval(trim($product->pricead_from));
  $was_price = intval(trim($product->pricead_was));

  $vars['price'] = t('Call us');
  $vars['was_price_label'] = t('Was');
  $vars['from_price_label'] = t('From');
  $vars['conditions'] = t('Per person');

  $vars['has_price'] = FALSE;
  $vars['is_dual_price'] = FALSE;
  $vars['classes_array'] = [
    'price-pane',
    'price-pane--' . $category,
    'column',
    'row',
  ];
  $vars['title_attributes_array'] = [
    'class' => [
      'price-pane__title'
    ],
  ];

  $vars['campaign_medium'] = '';
  $field_campaign_medium = 'field_product_campaign_medium:name';

  // Escape Fare icon needs to show based on the class of travel.
  if (!empty($product->selection)) {
    $vars['escape_fare_class'] = (substr(strtolower($product->selection), 0, strlen('Escape Fare')) === strtolower('Escape Fare'));

    // Change the label for specific product selection.
    if (in_array($product->selection, $was_label_change)) {
      $vars['was_price_label'] = variable_get('price_was_escapefare_label');
    }
  }

  // Check the price and format it.
  if ($price) {
    $vars['has_price'] = TRUE;
    $vars['price'] = number_format($product->pricead_from);

    // Check product to determine if is dual price or not.
    if ($was_price && $price !== $was_price) {
      $vars['is_dual_price'] = TRUE;
      $vars['classes_array'][] = 'price-pane--dual-price';
      $vars['was_price'] = number_format($was_price);
    }
  }

  // Add price condition based on product category.
  switch ($category) {
    case 'air_transportation':
      $vars['from_price_label'] = $product->oneway_flag ? t('One way from') : t('Return from');
      $vars['campaign_medium'] = (isset($product->$field_campaign_medium) && in_array('Limited Availability', $product->$field_campaign_medium)) ? 'Limited Availability' : '';
      break;

    case 'cruise':
      $vars['from_price_label'] = t('@selection from', array('@selection' => $product->selection));
      break;
  }

  $vars['theme_hook_suggestions'][] = 'fpc_price_pane__' . $category;
  // Add theme hook suggestion based on dual pricing rules.
  if (rules_invoke_component($rule, $product)) {
    $vars['theme_hook_suggestions'][] = 'fpc_price_pane__dual';
    $vars['theme_hook_suggestions'][] = 'fpc_price_pane__' . $category . '__dual';
  }
}
