<?php

/**
 * @file
 * Terms and Conditions template file.
 *
 * Theme hook suggestions are available in the format:
 * terms-and-conditions--CATEGORY-NAME.tpl.php
 * e.g. terms-and-conditions--cruise.tpl.php.
 *
 * @var $condition string
 *   Terms and Conditions content.
 */
?>
<?php if (isset($condition)): ?>
  <div class="<?php print $classes; ?>">
    <?php if (isset($title)): ?>
      <<?php print $title_tag; ?><?php print $title_attributes; ?>>
        <?php print $title; ?>
      </<?php print $title_tag; ?>>
    <?php endif;?>
    <?php print render($condition); ?>
  </div>
<?php endif; ?>
