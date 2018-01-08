<?php

/**
 * @file
 * Itinerary pane template file.
 *
 * Theme hook suggestions are available in the format:
 * itinerary-pane--CATEGORY-NAME.tpl.php
 * e.g. itinerary-pane--air-transportation.tpl.php.
 *
 * @var $title string
 *   The title if applicable.
 */
?>
<?php if (isset($itinerary)): ?>
  <?php if (isset($header)): ?>
    <?php print render($header); ?>
  <?php endif ?>
  <div class="<?php print $classes; ?>">
    <?php if (isset($title)): ?>
      <<?php print $title_tag; ?><?php print $title_attributes; ?>>
        <?php print $title; ?>
      </<?php print $title_tag; ?>>
    <?php endif; ?>
    <?php if (!empty($itinerary_headings)): ?>
      <?php print render($itinerary_headings); ?>
    <?php endif; ?>
    <?php if ($itinerary): ?>
      <?php print render($itinerary); ?>
    <?php endif; ?>
  </div>
<?php endif; ?>
