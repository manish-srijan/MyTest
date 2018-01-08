<?php

/**
 * @file
 * GNE reference pane template file.
 *
 * @var $gne_reference string
 *   The product GNE reference value.
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
