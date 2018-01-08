<?php

/**
 * @file
 * Product type icon with category name.
 *
 * @var string $category_label
 *   The name of the category.
 * @var array $category_icon
 *   The html markup with icon classes and name.
 */
?>

<?php if (!empty($category_label)): ?>
  <div class="<?php print $classes; ?>">
    <?php if (isset($title)): ?>
      <<?php print $title_tag; ?><?php print $title_attributes; ?>>
        <?php print $title; ?>
      </<?php print $title_tag; ?>>
    <?php endif; ?>
    <span class="product-type-icon-pane__title">
      <?php print $category_label; ?>
    </span>
    <?php if ($category_icon): ?>
      <span class="product-type-icon-pane__icon-container">
        <?php print render($category_icon); ?>
      </span>
    <?php endif; ?>
  </div>
<?php endif; ?>
