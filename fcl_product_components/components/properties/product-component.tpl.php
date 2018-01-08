<?php

/**
 * @file
 * Generic product component template.
 *
 * @var string $title
 *   the title of the property.
 * @var string $property_value
 *   the raw property value.
 */
?>
<?php if (!empty($property_value)): ?>
  <div class="<?php print $classes; ?>">
    <?php if (isset($title)): ?>
      <<?php print $title_tag; ?><?php print $title_attributes; ?>>
        <?php print $title; ?>
      </<?php print $title_tag; ?>>
    <?php endif; ?>
    <span class="product-component__value">
      <?php print $property_value; ?>
    </span>
  </div>
<?php endif; ?>
