/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
(function ($) {
//override the clickField function
Drupal.formBuilder.clickField = function(e) {
  // Allow select lists to be clicked on without opening the edit options.
  if ($(e.target).is('select') || $('.form-builder-wrapper #form-builder-field-configure', $(e.target).parents()).length) {
    return;
  }

  // Find the first configure link for this field, ensuring we don't get a link
  // belonging to a nested form element within this element.
  var $wrapper = $(this).parents('.form-builder-wrapper:first');
  var link = $wrapper.find('a.configure').not($wrapper.find('.form-builder-element .form-builder-element a')).get(0);
  Drupal.formBuilder.editField.apply(link);

  return false;
};
})(jQuery);
