(function ($) {
  Drupal.behaviors.WebformTableElement = {
    attach: function(context) {
      $('#edit-extra-switch-layout').change(function () {
        var title = $(this).is(':checked') ? Drupal.t('Columns') : Drupal.t('Rows');
        // if the options_element module is enabled
        $('fieldset#edit-rows').find('.fieldset-title').html(title);
        // if the options_element module is not enabled
        $('label[for="edit-extra-rows"]').html($('label[for="edit-extra-rows"]').html().replace(/Columns|Rows/, title));
      });
      $('#edit-extra-switch-layout').trigger('change');
    }
  };
})(jQuery);


