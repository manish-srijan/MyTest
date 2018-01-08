<?php

/**
 * @file
 * Product star rating pane template file.
 *
 * Theme hook suggestions are available in the format:
 * star-rating-pane--CATEGORY-NAME.tpl.php
 * e.g. star-rating-pane--accommodation.tpl.php.
 *
 * @var $star_rating array
 *   The product star rating if applicable.
 */
?>
<?php if (!empty($star_rating)): ?>
  <div class="<?php print $classes; ?>">
    <?php if (isset($title)): ?>
      <<?php print $title_tag; ?><?php print $title_attributes; ?>>
        <?php print $title; ?>
      </<?php print $title_tag; ?>>
    <?php endif;?>
    <?php print render($star_rating); ?>
  </div>
<?php endif; ?>
