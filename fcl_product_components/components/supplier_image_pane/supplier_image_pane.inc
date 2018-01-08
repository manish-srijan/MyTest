<?php

/**
 * @file
 * Supplier image pane theme hook file.
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function fcl_product_components_preprocess_supplier_image_pane(&$vars) {
  $product = $vars['product'];
  $category = fcl_utilities_slugify($product->category);
  $vars['classes_array'] = array(
    'supplier-image-pane',
    'supplier-image-pane__' . $category,
  );
  $vars['title_attributes_array'] = array(
    'class' => array('supplier-image-pane__title'),
  );
  $vars['theme_hook_suggestions'][] = 'supplier_image_pane__' . $category;

  // The `Product supplier secondary image` is usually itinerary map image, if
  // this image is available return this as supplier image otherwise return
  // `Product supplier image` as supplier image.

  // If this site is set to download the product images, use the image fields
  // on the Product.
  if (variable_get('fcl_procat_product_download_images', TRUE)) {
    $supplier_image_field_name = !empty($product->field_product_media_img2) ? 'field_product_media_img2' : 'field_product_media_img1';
    $vars['supplier_image'] = field_view_field('fcl_procat_product', $product, $supplier_image_field_name, 'page');
  }
  else {
    $supplier_image_field_name = !empty($product->supplier_secondary_product_image) ? 'supplier_secondary_product_image_remote' : 'supplier_product_image_remote';
    $vars['supplier_image'] = fcl_product_remote_images_psuedo_field_render_array($product, 'page', $supplier_image_field_name);
  }
}
