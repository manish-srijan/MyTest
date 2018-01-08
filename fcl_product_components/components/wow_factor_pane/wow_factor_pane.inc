<?php

/**
 * @file
 * Product wow factor pane theme hook file.
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function fcl_product_components_preprocess_wow_factor_pane(&$vars) {
  $product = $vars['product'];
  $category = fcl_utilities_slugify($product->category);
  $vars['classes_array'] = [
    'wow-factor-pane',
    'wow-factor-pane--' . $category,
  ];
  $vars['title_attributes_array'] = [
    'class' => ['wow-factor-pane__title'],
  ];
  $vars['theme_hook_suggestions'][] = 'wow_factor_pane__' . $category;

  // Initialising array.
  $vars['wow_factor'] = [];

  // Defining markup for the wow factor label so that its easy to
  // preprocess and override.
  $vars['wow_factor_text_label'] = [
    'content' => [
      '#markup' => t('Bonus'),
    ],
    'classes' => 'wow-factor-pane__text-label',
  ];

  // Wow factor will only be displayed if the char length of text field
  // being used as wow factor for respective product type is less than equal
  // to 23.
  switch ($category) {
    case 'cruise':
      if (!empty($product->tag_line) && strlen(trim($product->tag_line)) <= 23) {
        $vars['wow_factor'] = [
          'content' => [
            '#markup' => $product->tag_line,
          ],
          'classes' => 'wow-factor-pane__product-wow-factor',
        ];
      }
      break;

    default:
      if (!empty($product->package_description) && strlen(trim($product->package_description)) <= 23) {
        $vars['wow_factor'] = [
          'content' => [
            '#markup' => $product->package_description,
          ],
          'classes' => 'wow-factor-pane__product-wow-factor',
        ];
      }
      break;
  }
}
