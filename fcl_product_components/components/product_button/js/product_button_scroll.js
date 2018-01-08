/**
 * @file
 *
 * Product button scroll to target on click of button.
 */
'use strict';

(function ($, Drupal, window, document) {
  Drupal.behaviors.productButtonScrollTarget = {
    attach: function (context, settings) {
      var settingsNamespace = settings.fcl_product_components.product_button;
      var $buttonSelector = $(settingsNamespace.buttonSelector, context);
      var $scrollToTarget = $(settingsNamespace.scrollToSelector, context);
      if (!$scrollToTarget.length) {
        // Early return if page does not has target selector.
        return;
      }
      $buttonSelector.on('click', function (e) {
        e.preventDefault();
        $.scrollTo($scrollToTarget, 300, {
          offset: {top: -50}
        });
      });
    }
  };
})(jQuery, Drupal, this, this.document);
