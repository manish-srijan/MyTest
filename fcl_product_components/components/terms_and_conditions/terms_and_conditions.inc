<?php

/**
 * @file
 * Terms and Conditions theming functions.
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function fcl_product_components_preprocess_terms_and_conditions(&$vars) {
  $product = $vars['product'];
  $conditions = $product->conditions;
  // Early return if no condition.
  if (empty($conditions)) {
    return NULL;
  }

  $category = fcl_utilities_slugify($product->category);
  $vars['theme_hook_suggestions'][] = 'terms-and-conditions';
  $vars['classes_array'] = array(
    'fcl-terms-and-conditions',
    'fcl-terms-and-conditions--' . $category,
  );
  $vars['title_attributes_array'] = array(
    'class' => array('fcl-terms-and-conditions__title'),
  );
  $tab_settings = '';
  // Build the data array of tab elements with the
  // list of terms and conditions data.
  $tab_settings['tabs'][0]['title'] = t('Terms of Service');
  $tab_settings['tabs'][0]['content'] = $conditions;
  $tab_settings['attributes_array']['data-allow-all-closed'] = TRUE;
  $tab_settings['css_class_modifiers'] = 'fcl-terms-and-conditions';
  $tab_settings['breakpoints']['small'] = 'accordion';
  $tab_settings['is-active'] = -1;
  $tab_settings['responsive'] = 'accordion';

  // Render the tabs array with Foundie Tabs
  // and set responsive behaviour options.
  $vars['condition'] = theme(array('foundie_tabs'), $tab_settings);
}
