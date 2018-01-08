<?php

/**
 * @file
 * Product SKU template file.
 *
 * Theme hook suggestions are available in the format:
 * product-sku-pane--CATEGORY-NAME.tpl.php
 * e.g. product-sku-pane--cruise.tpl.php
 *
 * @var $product_sku string
 *   Product SKU number.
 */
?>
<div class="<?php print $classes; ?>">
  <?php if (isset($title)): ?>
    <<?php print $title_tag; ?><?php print $title_attributes; ?>>
      <?php print $title; ?>
    </<?php print $title_tag; ?>>
  <?php endif; ?>
  <div class="<?php print render($sku['classes']); ?>">
    <?php print render($sku['content']); ?>
  </div>
</div>
