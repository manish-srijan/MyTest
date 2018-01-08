<?php

/**
 * @file
 * Airline name and logo pane template file.
 *
 * Theme hook suggestions are available in the format:
 * airline-logo-pane--CATEGORY-NAME.tpl.php
 * e.g. airline-logo-pane--air-transporation.tpl.php.
 *
 * @var $airline_name string
 *   The product airline name.
 *
 * @var $airline_logo array
 *   The product airline logo renderable array.
 */
?>
<?php if ($airline_name || $airline_logo): ?>
  <div class="<?php print $classes; ?>">
    <?php if (isset($title)): ?>
      <<?php print $title_tag; ?><?php print $title_attributes; ?>>
        <?php print $title; ?>
      </<?php print $title_tag; ?>>
    <?php endif; ?>
    <?php if ($airline_name): ?>
      <div class="airline-logo-pane__airline-name">
        <?php print $airline_name; ?>
      </div>
    <?php endif; ?>
    <?php if ($airline_logo): ?>
      <div class="airline-logo-pane__logo-wrapper">
        <?php print render($airline_logo); ?>
      </div>
    <?php endif; ?>
  </div>
<?php endif; ?>
