<?php

/**
 * @file
 * Expired Ribbon pane template file.
 *
 * Theme hook suggestions are available in the format:
 * expired-ribbon-pane--CATEGORY-NAME.tpl.php
 * e.g. expired-ribbon-pane--air-transportation.tpl.php.
 *
 * @var $title string
 *   The title if applicable.
 */
?>
<div class="<?php print $classes ?>">
  <?php if (isset($title)): ?>
    <<?php print $title_tag; ?><?php print $title_attributes; ?>>
      <?php print $title; ?>
    </<?php print $title_tag; ?>>
  <?php endif; ?>
  <div class="fcl-expired-ribbon-pane__sku">
    <?php print render($product_sku); ?>
  </div>
  <div class="fcl-expired-ribbon-pane__package">
    <?php print render($expired_package); ?>
  </div>
</div>
