<?php

/**
 * @file
 * Price pane template file.
 *
 * Theme hook suggestions are available in the format:
 * fpc-price-pane--CATEGORY-NAME.tpl.php
 * e.g. fpc-price-pane--air-transportation.tpl.php.
 *
 * @var $title string
 *   The title of the price if applicable.
 *   e.g. promotion type: Escape Fare, Black Market, Red Label, etc.
 * @var $price string
 *   The price, should already have currency code attached.
 * @var $from_price_label string
 *   Any conditions that need to be tied closely to the price.
 *   e.g. "Twin Share From", "Economy From", etc..
 */
?>

<div class="<?php print $classes; ?>">
  <?php if ($title): ?>
    <<?php print $title_tag; ?><?php print $title_attributes; ?>>
      <?php print $title; ?>
    </<?php print $title_tag; ?>>
  <?php endif; ?>

  <?php if ($escape_fare_class): ?>
    <div class="price-pane--dual-price-icon column"></div>
  <?php endif; ?>

  <div class="price-pane__item column <?php ($is_dual_price) ? print 'small-6 medium-3 large-6' : ''; ?>">
    <div class="price">
      <?php if ($has_price): ?>
        <span class="price__prefix"><?php print $from_price_label; ?></span>
        <span class="price__unit"><?php print $currency_symbol; ?></span>
        <span class="price__value"><?php print $price; ?></span>
        <span class="price__suffix">*</span>
        <span class="price__prefix"><?php print $conditions; ?></span>
      <?php else: ?>
        <span class="price__value"><?php print $price; ?></span>
      <?php endif; ?>
    </div>
  </div>

  <?php if ($is_dual_price): ?>
    <div class="price-pane__item column small-6 end">
      <div class="price-pane__was-price-container">
        <div class="price-pane__was-price-label"><?php print $was_price_label; ?></div>
        <span class="price-pane__currency-symbol"><?php print $currency_symbol; ?></span>
        <span class="price-pane__was-price"><?php print $was_price; ?></span>
      </div>
    </div>
  <?php endif; ?>

  <?php if (!empty($campaign_medium)): ?>
    <div class="price-pane__campaign-availability column">Limited Availability</div>
  <?php endif;?>
</div>
