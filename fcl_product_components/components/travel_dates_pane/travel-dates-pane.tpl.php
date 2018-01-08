<?php

/**
 * @file
 * Travel Dates pane template file.
 *
 * Theme hook suggestions are available in the format:
 * travel-dates--CATEGORY-NAME.tpl.php
 * e.g. travel-dates--air-transportation.tpl.php.
 */
?>
<?php if (!empty($travel_dates['#content'])): ?>
<div class="<?php print $classes; ?>">
  <?php if (isset($title)): ?>
    <<?php print $title_tag; ?><?php print $title_attributes; ?>>
      <?php print $title; ?>
    </<?php print $title_tag; ?>>
  <?php endif; ?>
  <?php if (!empty($travel_dates['#content'][0]['start']['date']) && !empty($travel_dates['#content'][0]['end']['date'])): ?>
    <?php print render($travel_dates_headings); ?>
  <?php endif; ?>
  <?php print render($travel_dates); ?>
</div>
<?php endif; ?>
