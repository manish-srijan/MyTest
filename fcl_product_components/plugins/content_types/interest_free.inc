<?php
/**
 * @file
 * Plugin definition and callbacks for a ctools:content_types plugin.
 *
 * Placeholder content for the interest free component if site does not have
 * fcl interest free enabled.
 *
 * @ingroup CToolsPlugin CToolsPluginContentTypes
 */

if (!module_exists('fcl_interest_free')) {
  $module = drupal_get_path('module', 'fcl_product_components');
  include $module . '/includes/placeholder.inc';

  $plugin = array(
    'category' => t('Product'),
    'title' => t('Interest Free'),
    'description' => t('Interest Free prices'),
    'single' => TRUE,
  );

  $plugin = array_merge(fcl_product_components_dummy_content(), $plugin);
}
