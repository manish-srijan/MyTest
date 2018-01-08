<?php

/**
 * @file
 * Supplier logo template file.
 *
 * Theme hook suggestions are available in the format:
 * supplier-logo-pane--CATEGORY-NAME.tpl.php
 * e.g. supplier-logo-pane--air-transportation.tpl.php.
 *
 * @var $supplier_logo array
 *   Themeable array.
 * @var $supplier_logo_default_text array
 *   Default markup text.
 * @var $supplier_logo_exists bool
 *   Check which returns if logo exists or not.
 */
?>

<div class="<?php print $classes; ?>">
  <?php if (isset($title)): ?>
    <<?php print $title_tag; ?><?php print $title_attributes; ?>>
      <?php print $title; ?>
    </<?php print $title_tag; ?>>
  <?php endif;?>
  <?php print render($supplier_logo_default_text); ?>
  <?php if ($supplier_logo_exists): ?>
    <?php print render($supplier_logo); ?>
  <?php endif; ?>
</div>
