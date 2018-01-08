<?php

/**
 * @file
 * Main function for Inclusions component.
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function fcl_product_components_preprocess_inclusions_pane(&$vars) {
  $product = $vars['product'];
  $raw_inclusions = $product->raw_inclusions;
  $category = fcl_utilities_slugify($product->category);
  $vars['classes_array'] = array(
    'inclusions-pane',
    'inclusions-pane--' . $category,
  );
  $vars['title_attributes_array'] = array(
    'class' => array('inclusions-pane__title'),
  );
  $vars['theme_hook_suggestions'][] = 'inclusions_pane__' . $category;
  $vars['inclusions'] = fcl_product_components_format_inclusion_bullets($category, $raw_inclusions);
}

/**
 * Format the raw_inclusions field as an unordered list.
 *
 * @param string $category
 *   The category of the product.
 * @param string $raw_inclusions
 *   The raw_inclusions text from the product.
 *
 * @return string
 *   The formatted inclusions as an unordered list.
 */
function fcl_product_components_format_inclusion_bullets($category, $raw_inclusions) {
  switch ($category) {
    case 'cruise':
      if (substr_count($raw_inclusions, '</div></div>') >= 1) {
        // Cruise feed products.
        $raw_inclusions = str_replace('</div></div>', '. ', $raw_inclusions);
      }
      else {
        // Manually loaded cruise products.
        $raw_inclusions = preg_replace('/.\n/i', '. ', $raw_inclusions);
      }
      $raw_inclusions = strip_tags($raw_inclusions, '<br /><a><strong><b><em><i><span><h4><sub><sup>');
      $raw_inclusions = explode(". ", $raw_inclusions);
      break;

    case 'tour':
      $raw_inclusions = preg_replace('/<\/li>(.|\n)*?<li.*?>/i', '<br />', $raw_inclusions);
      $raw_inclusions = preg_replace("/what.*?included/i", '', $raw_inclusions);
    case 'air_transportation':
    case 'round_the_world':
    case 'multi_stop':
      $raw_inclusions = str_replace('<br', '.<br', $raw_inclusions);
      $raw_inclusions = strip_tags($raw_inclusions, '<br><br /><a><strong><b><em><i><h4><sub><sup>');
      $raw_inclusions = explode(".", $raw_inclusions);
      $clean_inclusions = array();
      foreach ($raw_inclusions as $i => $raw_inclusion) {
        // Trims whitespace at front of a row.
        $raw_inclusion = ltrim($raw_inclusion);
        // Check if array item is not empty.
        if (!empty($raw_inclusion)) {
          // Add full-stop back.
          $raw_inclusion .= '.';
          // Checks for any "- " at the beginning of the row and removes them.
          $clean_inclusions[] = preg_replace(array('/^Included: /', '/^- /'), '', $raw_inclusion);
        }
      }
      $raw_inclusions = $clean_inclusions;
      break;

    default:
      $raw_inclusions = explode("\n", $raw_inclusions);
      break;
  }

  foreach ($raw_inclusions as $key => $value) {
    // Filter any bullets that don't have any text.
    $check_value = strip_tags($value, '');
    // If there was nothing but HTML in the field, remove it from the array.
    if (empty($check_value)) {
      unset($raw_inclusions[$key]);
    }
    else {
      // Strip other HTML tags that won't sit well in our unordered list.
      $raw_inclusions[$key] = strip_tags($value, '<br /><a><strong><b><em><i><span><h4><sub><sup>');
    }
  }

  if (empty($raw_inclusions)) {
    return '';
  }

  $raw_inclusions_html = '<ul>';
  foreach ($raw_inclusions as $li) {
    // Remove <br> if its at the beginning.
    if (strpos($li, '<br />') === 0) {
      $li = substr($li, 4);
    }
    // If it's a heading.
    if (strpos(trim($li), '<h4>') === 0) {
      $raw_inclusions_html .= '<h4>' . strip_tags($li) . '</h4>';
      continue;
    }
    $li = str_replace('<br />', '</li><li>', $li);
    $raw_inclusions_html .= '<li>' . trim($li) . '</li>';
  }
  $raw_inclusions_html .= '</ul>';

  return $raw_inclusions_html;
}
