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
<?php if ($gne_reference): ?>
<div class="<?php print $classes; ?>">
  <?php if (isset($title)): ?>
        <<?php print $title_tag; ?><?php print $title_attributes; ?>>
    <?php print $title; ?>
        </<?php print $title_tag; ?>>
  <?php endif; ?>
    <div class="gne-reference-pane__gne-wrapper">
        <div class="gne-reference-pane__gne-reference">
          <?php print render($gne_reference); ?>
        </div>
    </div>
    </div>
<?php endif; ?>
