<?php

/**
 * @file
 * Supplier logo pane theme hook file.
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function fcl_product_components_preprocess_product_type_icon_pane(&$vars) {
  $product = $vars['product'];
  $category = fcl_utilities_slugify($product->category);
  $vars['classes_array'] = [
    'product-type-icon-pane',
    'product-type-icon-pane--' . $category,
  ];
  $vars['theme_hook_suggestions'][] = 'product-type-icon-pane__' . $category;

  // Product category human readable name.
  $vars['category_label'] = ($category === 'air_transportation') ? 'Flight' : $product->category;
  $vars['category_icon'] = _fcl_product_components_product_type_fcl_icon($category);
}

/**
 * Get the icon classes based on category.
 *
 * @param string $category
 *   The product category.
 *
 * @return array
 *   Contains the `icon_class` data.
 */
function _fcl_product_components_product_type_fcl_icon($category) {
  $icon_output = [];

  // Icons for respective category.
  $icons_name = [
    'tour' => 'directions-bus',
    'air_transportation' => 'flight',
    'accommodation' => 'local-hotel',
    'cruise' => 'directions-boat',
  ];

  switch ($category) {
    case 'tour':
    case 'air_transportation':
    case 'accommodation':
    case 'cruise':
      // Call fcl_icon theme to get icon.
      $icon_output['fcl_icon_' . $category] = [
        '#theme' => 'fcl_icon',
        '#settings' => [
          'name' => $icons_name[$category],
          'additional_classes' => [
            'product-type-icon-pane__icon',
          ],
        ],
      ];
      break;

    case 'holiday_package':
      // Icons for holiday package category.
      $icons_name = [
        'air_transportation' => 'flight',
        'plus' => 'add',
        'accommodation' => 'local-hotel',
      ];

      foreach ($icons_name as $key => $icon) {
        // Call fcl_icon theme to get icon.
        $icon_output['fcl_icon_' . $key] = [
          '#theme' => 'fcl_icon',
          '#settings' => [
            'name' => $icon,
            'additional_classes' => [
              'product-type-icon-pane__icon',
            ],
          ],
        ];
      }
      break;
  }
  return $icon_output;
}
