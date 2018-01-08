<?php

/**
 * @file
 * Product wow factor template file.
 *
 * Theme hook suggestions are available in the format:
 * wow-factor-pane--CATEGORY-NAME.tpl.php
 * e.g. wow-factor-pane--air-transportation.tpl.php.
 *
 * @var $wow_factor string
 *   Product wow factor.
 * @var $wow_factor_text_label array
 *   Product wow factor text label.
 */
?>

<?php if ($wow_factor): ?>
  <div class="<?php print $classes; ?>">
    <?php if (isset($title)): ?>
      <<?php print $title_tag; ?><?php print $title_attributes; ?>>
        <?php print $title; ?>
      </<?php print $title_tag; ?>>
    <?php endif; ?>
    <div class="wow-factor-pane__text-label-wrapper">
      <span class="<?php print $wow_factor_text_label['classes']; ?>">
        <?php print render($wow_factor_text_label['content']); ?>
      </span>
    </div>
    <span class="<?php print $wow_factor['classes']; ?>">
      <?php print render($wow_factor['content']); ?>
    </span>
  </div>
<?php endif; ?>
