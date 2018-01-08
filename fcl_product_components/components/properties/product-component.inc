<?php

/**
 * @file
 * Generic product component preprocess.
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function fcl_product_components_preprocess_product_component(&$vars) {
  /* @var EntityMetadataWrapper */
  $product = $vars['product'];
  $category = $product->category_id->name->value();
  $category_slug = fcl_utilities_slugify($category);
  $vars['category'] = $category_slug;
  $property_slug = fcl_utilities_slugify($vars['property']);
  $vars['classes_array'] = array(
    'product-component',
    'product-component--' . $category_slug,
  );
  $vars['title_attributes_array'] = array(
    'class' => array('product-component__title'),
  );
  $vars['theme_hook_suggestions'][] = 'product_component__' . $property_slug;
  $vars['theme_hook_suggestions'][] = 'product_component__' . $property_slug . '_' . $category_slug;
  // Initialize property value to avoid warnings.
  $vars['property_value'] = NULL;
  if ($product->{$vars['property']}->value()) {
    $property = $product->{$vars['property']}->value();
    $vars['property_value'] = $property;
    // Check if property is an object and if name property exists.
    if (is_object($property) && property_exists($property, 'name')) {
      $vars['property_value'] = $property->name;
    }
  }

  $vars['hero_product'] = FALSE;
  if (arg(0) === 'product' && arg(1) === $product->getIdentifier()) {
    $vars['hero_product'] = TRUE;
  }
}
