<?php

/**
 * @file
 * Product star rating theming functions.
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function fcl_product_components_preprocess_star_rating_pane(&$vars) {
  $product = $vars['product'];
  $category = fcl_utilities_slugify($product->category);
  $vars['classes_array'] = array(
    'fcl-icon',
    'star-rating-pane',
    'star-rating-pane--' . $category,
  );
  $vars['title_attributes_array'] = array(
    'class' => array('star-rating-pane__title'),
  );
  $vars['theme_hook_suggestions'][] = 'star_rating_pane__' . $category;
  $vars['star_rating'] = _fcl_product_components_get_formatted_star_rating($product->star_rating);
}

/**
 * Adds the stars to the products based on the rating.
 *
 * @param array $star_rating
 *   Taxonomy array for processing star ratings.
 *
 * @return mixed
 *   Product star rating themeable array or boolean based on availability.
 */
function _fcl_product_components_get_formatted_star_rating($star_rating) {
  // Early checking to make sure star rating is available and the selected value
  // is not Other.
  if (empty($star_rating) || $star_rating === 'Other') {
    return FALSE;
  }

  // Setting variables.
  $max_stars = 5;
  $star_half = FALSE;

  $no_of_stars = str_replace(' Star', '', $star_rating);
  $round_stars = round($no_of_stars, 0, PHP_ROUND_HALF_DOWN);

  // Initialising output array.
  $output = array();

  // Render the stars.
  for ($i = 1; $i <= $max_stars; $i++) {
    if ($i <= $round_stars) {
      $output['fcl_icon_star'][] = [
        '#theme' => 'fcl_icon',
        '#settings' => [
          'name' => 'star',
          'additional_classes' => [
            'star-rating-pane--star-icon',
            'star-rating-pane--star',
          ],
        ],
      ];
    }
    elseif (strpos($no_of_stars, '.') && !$star_half) {
      $output['fcl_icon_star_half'][] = [
        '#theme' => 'fcl_icon',
        '#settings' => [
          'name' => 'star-half',
          'additional_classes' => [
            'star-rating-pane--star-icon',
            'star-rating-pane--star-half',
          ],
        ],
      ];
      $star_half = TRUE;
    }
    else {
      $output['fcl_icon_star_border'][] = [
        '#theme' => 'fcl_icon',
        '#settings' => [
          'name' => 'star-border',
          'additional_classes' => [
            'star-rating-pane--star-icon',
            'star-rating-pane--star-border',
          ],
        ],
      ];
    }
  }

  return $output;
}
