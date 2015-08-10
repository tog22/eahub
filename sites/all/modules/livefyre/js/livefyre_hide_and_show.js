(function ($) {
  Drupal.behaviors.livefyre_hide_and_show = {
    attach: function (context) {
      if ( $('#edit-livefyre-location option:selected').val() =="block"){
        $('.form-item-livefyre-weight').hide();
        $('.form-item-livefyre-node-types').hide();
                  $('#for_block').show();
      }
    
      $("#edit-livefyre-location").click(function() {
        if ( $('#edit-livefyre-location option:selected').val() =="content_area"){
          $('.form-item-livefyre-weight').show();
          $('.form-item-livefyre-node-types').show();
                    $('#for_block').hide();

        } else {
          $('.form-item-livefyre-weight').hide();
          $('.form-item-livefyre-node-types').hide();
          }
        });
    }
  }
})(jQuery);

