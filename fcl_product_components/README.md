# FCL Product Components

  Module overview

  * **Availability:** Global
  * **Current version:** 7.x-1.3


  ## Dependencies

  * Fcl Procat Product
  * Fcl Utilities
  * Foundie

  ### Highly recommended
  * Fcl Procat Product Panels


  ## Usage

  After enabling, all Procat Product fields will be available for use in procat panels.
  They are available under 'Fcl_procat_product' category on the 'Add content' option.

  ## Extra Fields

  In addition to the raw property fields, there are also a couple of special fields.
  * Price pane - an easily themeable pane for price information.
  * Itinerary pane - an easily themeable pane for itinerary information.
  * Inclusion pane - an easily themeable pane for inclusion information.
  * Supplier logo pane - an easily themeable pane for supplier logo(if available) otherwise display supplier name.
  * Supplier image pane - An easily themeable pane to display product supplier secondary image(usually itinerary map if available) otherwise display product supplier image.
  * Product expiry date pane - An easily themeable pane to display product commerce expiry date(formatted in dd/mm/yyyy) and appended 23 hours 59 mins and 59 seconds to expiry date timestamp which will help in displaying the correct time i.e end of the day.
  * Terms and Conditions - an easily themeable terms and conditions information.
  * Product star rating pane - an easily themeable pane for star rating.
  * Expired Ribbon pane - an easily themeable pane for expired product ribbon.
  * Product wow factor pane - An easily themeable pane for wow factor. Furthermore, wow factor will only be displayed if the char length of text field being used for respective product type is less than equal to 23.
  * Product type icon pane - an easily themeable pane for displaying product type with its associated icon.
  * Airline name and logo pane - An easily themeable pane for displaying airline name with its associated logo. Incase, if the product has multiple airlines then it will show airline name as "Multiple Airlines" with no default logo.

  Fields from the airline entity are available if a valid airline code is on the product.
  * Airline name: the full name of the airline.
  * Airline logo: small
  * Airline logo: large
  * Airline logo: x-large

  ## CTA Button

  Currently only supports custom text, and scroll target inside the same panel.  Is located in the 'Form'
  pane category.

  ## Itinerary Pane

  Itinerary pane uses `fcl_itinerary_item` for theming specific itinerary item for itinerary accordion(currently Tour products) and `fcl_item_list` for creating itinerary list(currently Cruise products).

  Itineraries are build from either of two ways:
  1. From well formatted `fcl_procat_product_itineraries` (if available)
  2. Extracted from product description field.(Otherwise)

  Itinerary pane component allow you to implement a **category specific itinerary format function for each brand** to extract itinerary from product description. see _fcl_product_components_itinerary_from_description().

  ```
  _fcl_product_components_itinerary_format__CATEGORY__BRAND()
  _fcl_product_components_itinerary_format__tour__et()
  _fcl_product_components_itinerary_format__tour__topdeck()
  _fcl_product_components_itinerary_format__cruise__et()
  ```

  if relevant format function exists then that function will be called to extract itinerary from product description otherwise description will be displayed as it is.

  ## Theming

  The property output is themeable with templates.  They are ultimately run through the `entity_property`
  theme function but inside is a new templatable theme function `product_component`.

  Theme hook suggestions provided are:
  ```
  product-component.tpl.php
  product-component--PROPERTY-NAME.tpl.php
  product-component--PROPERTY-NAME-CATEGORY-NAME.tpl.php
  ```

  So for example, for the `country` property on an `air transportation` product they would be:

  ```
  product-component.tpl.php
  product-component--country.tpl.php
  product-component--country-air-transportation.tpl.php
  ```

  The price pane component has its own suggestions

  ```
  fpc-price-pane.tpl.php
  fpc-price-pane--CATEGORY-NAME.tpl.php
  ```
  Example with `air transportation` would be:
  ```
  fpc-price-pane.tpl.php
  fpc-price-pane--air-transportation.tpl.php
  ```

  The CTA button is just a theme function `theme_cta_button` and can be overridden in
  the normal fashion.

  The Itinerary pane component has its own suggestions

  ```
  itinerary-pane--CATEGORY-NAME.tpl.php
  e.g. itinerary-pane--air-transportation.tpl.php
  ```

  The Supplier logo pane component has its own suggestions

  ```
  supplier-logo-pane--CATEGORY-NAME.tpl.php
  e.g. supplier-logo-pane--air-transportation.tpl.php
  ```

  The Supplier Image pane component has its own suggestions

  ```
  supplier-image-pane--CATEGORY-NAME.tpl.php
  e.g. supplier-image-pane--air-transportation.tpl.php
  ```

  The Product expiry date pane component has its own suggestions

  ```
  expiry-date-pane--CATEGORY-NAME.tpl.php
  e.g. expiry-date-pane--air-transportation.tpl.php
  ```

  The Terms and Conditions component has its own suggestion

  ```
  terms-and-conditions.tpl.php
  ```

  The product star rating component has its own suggestions

  ```
  star-rating-pane--CATEGORY-NAME.tpl.php
  star-rating-pane--accommodation.tpl.php
  ```

  The Expired Ribbon component has its own suggestion

  ```
  expired-ribbon-pane--CATEGORY-NAME.tpl.php
  expired-ribbon-pane--accommodation.tpl.php
  ```
  
  The Product wow factor pane component has its own suggestions

  ```
  wow-factor-pane--CATEGORY-NAME.tpl.php
  e.g. wow-factor-pane--air-transportation.tpl.php
  ```

  The product type icon component has its own suggestions

  ```
  product-type-icon-pane--CATEGORY-NAME.tpl.php
  product-type-icon-pane--accommodation.tpl.php
  ```

  The product airline name and logo component has its own suggestions

  ```
  airline-logo-pane--CATEGORY-NAME.tpl.php
  airline-logo-pane--air-transportation.tpl.php
  ```
