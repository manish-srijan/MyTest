<?php

/**
 * @file
 * Product commerce expiry date template file.
 *
 * Theme hook suggestions are available in the format:
 * expiry-date-pane--CATEGORY-NAME.tpl.php
 * e.g. expiry-date-pane--air-transportation.tpl.php.
 *
 * @var $expiry_date array
 *   Themeable array.
 * @var $expiry_date_default_text_label array
 *   Default markup text label.
 */
?>

<?php if ($expiry_date): ?>
  <div class="<?php print $classes; ?>">
    <?php if (isset($title)): ?>
      <<?php print $title_tag; ?><?php print $title_attributes; ?>>
        <?php print $title; ?>
      </<?php print $title_tag; ?>>
    <?php endif; ?>
    <?php if ($expiry_date_icon): ?>
      <span class="<?php print $expiry_date_icon['classes']; ?>">
        <?php print render($expiry_date_icon['icon']); ?>
      </span>
    <?php endif; ?>
    <?php if ($expiry_date_text_label): ?>
      <span class="<?php print $expiry_date_text_label['classes']; ?>">
        <?php print render($expiry_date_text_label['content']); ?>
      </span>
    <?php endif; ?>
    <span class="expiry-date-pane__product-expiry-date">
      <?php print render($expiry_date); ?>
    </span>
  </div>
<?php endif; ?>
