<?php

/**
 * @file
 * Product bookable button theme function.
 */

/**
 * Implements theme_HOOK().
 *
 * Theme a Product bookable button.
 */
function theme_product_button($vars) {
  // Add pre definied modal form if foundie version is 6.
  $foundie_v = foundie_get_version();
  $reveal_modal = '';
  if ($foundie_v === '6') {
    $reveal_modal = '<div class="reveal" data-reveal id="soar-form-modal"><a class="close-button" aria-label="Close" data-close>&#215;</a></div>';
  }

  $button = $vars['product_button'];
  $options = array(
    'attributes' => array(
      'class' => array(
        'pui-btn',
        'expanded',
        $button['style'],
      ),
    ),
    'external' => (isset($button['external'])) ? $button['external'] : FALSE,
  );

  // Added class based on the selected button style.
  if ($button['style'] === 'default') {
    array_push($options['attributes']['class'], 'pui-btn-accent waves-effect waves-classic');
  }

  if (isset($button['scroll_target'])) {
    $options['fragment'] = $button['scroll_target'];
    $options['external'] = TRUE;
  };

  // Add path parameter to allow potentially linking to another page.
  $path = (!empty($button['path'])) ? $button['path'] : '';

  if (module_exists('fcl_product_bookable') && !empty($button['sku'])) {
    if (isset($button['bookable'])) {
      return $reveal_modal . theme('booking_modal_button', array('soar_button' => $button));
    }

    // @TODO make button title configurable if button is not bookable.
    // If product is not bookable title will change.
    $button['title'] = t('GET A QUOTE');
    $path = fcl_product_bookable_get_product_link($button['sku']);
  }

  return $reveal_modal . l($button['title'], $path, $options);
}
