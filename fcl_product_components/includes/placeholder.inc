<?php
/**
 * @file
 * Helpers for placeholder ctools stuff.
 *
 * Basically we want to export ctools content types in features, but don't want
 * to make their modules dependencies for sites that don't need that particular
 * pane.  We create dummy ctool types in the plugin folder to help this.
 *
 * This file just speeds up the creation of these dummies with common stuff.
 */

/**
 * Default plugin definition for placeholder content.
 *
 * @return array
 *   a ctools plugin array.
 */
function fcl_product_components_dummy_content() {
  $plugins = array(
    'category' => t('Placeholder'),
    'title' => t('Placeholder Content Type'),
    'description' => t('This pane is a placeholder for a feature not enabled on this website'),
    'required context' => NULL,
    'edit form' => 'fcl_product_components_dummy_content_ctools_edit_form',
    'edit form validate' => 'fcl_product_components_dummy_content_ctools_edit_form_validate',
    'edit form submit' => 'fcl_product_components_dummy_content_ctools_edit_form_submit',
    'admin info' => 'fcl_product_components_dummy_content_ctools_admin_info',
    'render callback' => 'fcl_product_components_dummy_content_ctools_render',
  );
  return $plugins;
}


/**
 * Edit form callback.
 */
function fcl_product_components_dummy_content_ctools_edit_form($form, &$form_state) {

  $conf = $form_state['conf'];

  $form['fcl_dummy_content_text'] = array(
    '#markup' => '<div>This is a placeholder for BLANK</div>',
  );

  return $form;
}

/**
 * Edit form submit callback.
 */
function fcl_product_components_dummy_content_ctools_edit_form_submit($form, &$form_state) {

}

/**
 * Admin info callback.
 *
 * @param string $subtype
 *   Identifier of subtype.
 * @param array $conf
 *   Pane configuration. Array keys are depends on the _edit_form.
 *   - override_title
 *   - override_title_text
 * @param array $context
 *   An array of context objects available for use. These may be placeholders.
 *
 * @return object
 *   Administrative title and description of the $subtype pane.
 *   The keys are:
 *   - title: string
 *   - content: string|array
 */
function fcl_product_components_dummy_content_ctools_admin_info($subtype, $conf, $context) {
  $return = new stdClass();
  $return->title = t('Placeholder: %type', array('%type' => $subtype));
  $return->content = t('Placeholder for optional pane.');

  return $return;
}

/**
 * Placeholder render callback.
 *
 * @param string $subtype
 *   Subtype identifier.
 * @param array  $conf
 *   Configuration of the $subtype instance.
 * @param array  $args
 *   The arguments provided to the owner of the content type.
 * @param array  $pane_context
 *   An array of context objects available for use.
 * @param array  $incoming_content
 *   Any incoming content, if this display is a wrapper.
 *
 * @return object
 *   The content.
 */
function fcl_product_components_dummy_content_ctools_render($subtype, $conf, $args, $pane_context, $incoming_content) {
  $block = new stdClass();
  $block->module = 'dummy_content';
  $block->content = '';

  return $block;
}
