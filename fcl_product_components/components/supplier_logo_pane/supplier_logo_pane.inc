<?php

/**
 * @file
 * Supplier logo pane theme hook file.
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function fcl_product_components_preprocess_supplier_logo_pane(&$vars) {
  $product = $vars['product'];
  $category = fcl_utilities_slugify($product->category);
  $vars['classes_array'] = array(
    'supplier-logo-pane',
    'supplier-logo-pane--' . $category,
  );
  $vars['title_attributes_array'] = array(
    'class' => array('supplier-logo-pane__title'),
  );
  $vars['theme_hook_suggestions'][] = 'supplier_logo_pane__' . $category;

  $supplier_logo_file_name = fcl_utilities_slugify($product->supplier, '-') . '.png';
  $supplier_logo_path = 'https://media.fclmedia.com/global-images/supplier-logos/product-page/' . $supplier_logo_file_name;

  // For the time being adding a file_exists check, later we may replace
  // supplier logo as a standalone service as we have done with airline images.
  $vars['supplier_logo_exists'] = file_exists($supplier_logo_path);

  $vars['supplier_logo_default_text'] = array(
    '#markup' => $product->supplier,
    '#prefix' => '<span class="supplier-logo-pane__default-text">',
    '#suffix' => '</span>',
  );
  $vars['supplier_logo'] = array(
    '#theme' => 'image',
    '#path' => $supplier_logo_path,
    '#alt' => $product->supplier,
    '#title' => $product->supplier,
    '#attributes' => array(
      'class' => array('supplier-logo-pane__image'),
    ),
  );
}
