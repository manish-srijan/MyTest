<?php

/**
 * @file
 * Plugin definition and callbacks for a ctools:content_types plugin.
 *
 * @ingroup CToolsPlugin CToolsPluginContentTypes
 */

$plugin = [
  'category' => t('Form'),
  'title' => t('Product button'),
  'description' => t('Product bookable button.'),
  'single' => TRUE,
  'required context' => new ctools_context_optional(t('FCL Procat Product'), 'fcl_procat_product'),
  'edit form' => 'fcl_product_components_product_button_ctools_edit_form',
  'edit form submit' => 'fcl_product_components_product_button_ctools_edit_form_submit',
  'admin info' => 'fcl_product_components_product_button_ctools_admin_info',
  'render callback' => 'fcl_product_components_product_button_ctools_render',
];

/**
 * Edit form callback.
 */
function fcl_product_components_product_button_ctools_edit_form($form, &$form_state) {
  $defaults = [
    'title' => 'Enquire NOW',
    'style' => 'default',
  ];

  $conf = $form_state['conf'] + $defaults;

  $form['title'] = [
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Button text'),
    '#description' => t('Text to go on the button'),
    '#default_value' => $conf['title'],
  ];

  $button_styles = [
    'default' => 'Default',
    'success' => 'Success',
    'secondary' => 'Secondary',
    'info' => 'Info',
    'alert' => 'Alert',
  ];

  $form['style'] = [
    '#type' => 'select',
    '#required' => TRUE,
    '#title' => t('Style'),
    '#description' => t('Style of button'),
    '#default_value' => $conf['style'],
    '#options' => foundie_get_theme_setting('button_style', $button_styles),
  ];

  // TODO: make pluggable?
  $form['action'] = [
    '#type' => 'select',
    '#required' => FALSE,
    '#title' => t('Action'),
    '#description' => t('What action to perform'),
    '#default_value' => $conf['action'],
    '#empty_option' => t('- Select -'),
    '#options' => [
      'link' => t('Link'),
      'scroll' => t('Scroll'),
    ],
  ];

  $form['scroll_target'] = [
    '#type' => 'textfield',
    '#title' => t('Scroll target'),
    '#description' => t('What pane should we scroll to'),
    '#default_value' => $conf['scroll_target'],
    '#states' => [
      'visible' => [
        ':input[name="action"]' => ['value' => 'scroll'],
      ],
    ],
  ];

  // If we have the rule module enabled, we can trigger visibility.
  if (module_exists('rules')) {
    $rules = rules_get_components(TRUE);
    $form['rule_component'] = [
      '#type' => 'select',
      '#required' => FALSE,
      '#title' => t('Visibility rule'),
      '#description' => t('Rule for determining when to show.'),
      '#default_value' => $conf['rule_component'],
      '#empty_option' => t('- Select -'),
      '#options' => $rules,
    ];
  }

  return $form;
}

/**
 * Edit form submit callback.
 */
function fcl_product_components_product_button_ctools_edit_form_submit($form, &$form_state) {
  foreach ($form_state['values'] as $key => $value) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

/**
 * Admin info callback.
 *
 * @param string $subtype
 *   Identifier of subtype.
 * @param array $conf
 *   Pane configuration. Array keys are depends on the _edit_form.
 *   - override_title
 *   - override_title_text.
 * @param array $context
 *   An array of context objects available for use. These may be placeholders.
 *
 * @return object
 *   Administrative title and description of the $subtype pane.
 *   The keys are:
 *   - title: string
 *   - content: string|array
 */
function fcl_product_components_product_button_ctools_admin_info($subtype, $conf, $context) {
  $return = new stdClass();
  $return->title = 'Product Button';
  $return->content = "This is the admin info of price-pane:price-pane:$subtype";

  return $return;
}

/**
 * Render callback.
 *
 * "CTools:Content types" plugin render callback for "Product:Call to action".
 *
 * @param string $subtype
 *   Subtype identifier.
 * @param array $conf
 *   Configuration of the $subtype instance.
 * @param array $args
 *   The arguments provided to the owner of the content type.
 * @param array $pane_context
 *   An array of context objects available for use.
 * @param array $incoming_content
 *   Any incoming content, if this display is a wrapper.
 *
 * @return object
 *   The content.
 */
function fcl_product_components_product_button_ctools_render($subtype, $conf, $args, $pane_context, $incoming_content) {
  $block = new stdClass();

  // Passing selector settings.
  $settings = [
    'scrollToSelector' => !empty($conf['scroll_target']) ? '#' . $conf['scroll_target'] : '',
    'buttonSelector' => '.pane-product-button a',
  ];

  $block->module = 'product_button';
  $block->content = [
    '#theme' => 'product_button',
    'title' => $conf['title'],
    'style' => $conf['style'],
  ];

  if ($conf['action'] === 'scroll' && !$pane_context->data->bookable) {
    // Attach scroll js if action is scroll and product is not bookable.
    $block->content['#attached'] = [
      'library' => [
        ['libraries_load', 'jquery.scrollTo'],
      ],
      'js' => [
        [
          'data' => [
            'fcl_product_components' => [
              'product_button' => $settings,
            ],
          ],
          'type' => 'setting',
        ],
        drupal_get_path('module', 'fcl_product_components') . '/components/product_button/js/product_button_scroll.js',
      ],
    ];
  }

  if (!empty($pane_context->data->sku)) {
    $block->content['sku'] = $pane_context->data->sku;
  }

  if (!empty($pane_context->data->bookable)) {
    $block->content['bookable'] = $pane_context->data->bookable;
  }

  if (isset($conf['scroll_target'])) {
    $block->content['scroll_target'] = $conf['scroll_target'];
  }

  return $block;
}
