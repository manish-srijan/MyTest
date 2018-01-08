<?php

/**
 * @file
 * Inclusion pane tpl.
 *
 * Outputs formatted raw includes.
 */
?>
<?php if (!empty($inclusions)): ?>
  <div class="<?php print $classes; ?>">
    <?php if (isset($title)): ?>
      <<?php print $title_tag; ?><?php print $title_attributes; ?>>
        <?php print $title; ?>
      </<?php print $title_tag; ?>>
    <?php endif; ?>
    <?php print render($inclusions); ?>
  </div>
<?php endif; ?>
