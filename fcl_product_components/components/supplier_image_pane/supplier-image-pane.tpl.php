<?php

/**
 * @file
 * Supplier image template file.
 *
 * Theme hook suggestions are available in the format:
 * supplier-image-pane--CATEGORY-NAME.tpl.php
 * e.g. supplier-image-pane--air-transportation.tpl.php
 *
 * @var $supplier_image array
 *   Themeable array.
 */
?>
<?php if (!empty($supplier_image)): ?>
  <div class="<?php print $classes; ?>">
    <?php if (isset($title)): ?>
      <<?php print $title_tag; ?><?php print $title_attributes; ?>>
        <?php print $title; ?>
      </<?php print $title_tag; ?>>
    <?php endif; ?>
    <?php print render($supplier_image); ?>
  </div>
<?php endif; ?>
