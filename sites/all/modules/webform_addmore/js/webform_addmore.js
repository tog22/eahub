// $Id$

(function ($) {

Drupal.behaviors.webform_addmore = {
  attach: function(context) {
    function fieldsetRepeater(container, fieldsetSelecter, addBtnTxt, delBtnTxt, numberFirstShown) {
      var collections = Drupal.settings.webform_addmore.collections;

      if (collections.length == 0) {
        collections.push('');
      }

      for (index in collections) {
        if (collections[index].length == 0) {
          var parent_fieldset_selector = fieldsetSelecter;
        }
        else {
          var parent_fieldset_selector = '#' + collections[index] + ' ' + fieldsetSelecter;
        }
        //console.debug('parent_fieldset_selector: %o', parent_fieldset_selector);
        var add_more_button_id = 'webform-addmore-' + collections[index];
        var del_more_button_id = 'webform-addmore-del-' + collections[index];
        var addBtn = $('<input type="button" id="' + add_more_button_id + '" class="add-more button white" />').val(addBtnTxt);
        addBtn.click(function() {
          var parent_fieldset = $(this).parents('fieldset');
          if (parent_fieldset.length > 0) {
            var parent_id = parent_fieldset.attr('id');
            var hiddenFieldsets = $('#' + parent_id + ' ' + fieldsetSelecter).not(':visible');
          }
          else {
            var hiddenFieldsets = fieldsets.not(':visible');
          }

          var next = hiddenFieldsets.filter(':first');
          next.fadeIn();
          var delBtn = $('<input type="button" class="del-btn button white" />').val('Remove');
          $(next).append(delBtn);

          if(hiddenFieldsets.size() < 2) {
            $(this).hide();
          }

        });


      $('.del-btn').livequery(function(){
        $('.del-btn').click(function() {
          var parent_fieldset = $(this).parent();
          parent_fieldset.find(':input').val('');
          parent_fieldset.find('.del-btn').remove();
          parent_fieldset.hide();


          // We need to rescan the page for shown fieldsets
          if (parent_fieldset.length > 0) {
            var parent_id = parent_fieldset.attr('id');
            var shownFieldsets = $('#' + parent_id + ' ' + fieldsetSelecter).not(':hidden');

          }
          else {
            var shownFieldsets = fieldsets.not(':hidden');
          }

          if(shownFieldsets.size() < 2) {
            $(this).hide();
          }

          var hiddenFieldsets = $('#' + parent_id + ' ' + fieldsetSelecter).not(':visible');

          var cont = parent_fieldset.parent().parent();

          $(cont).append(addBtn);
          addBtn.show();
        });
      });

        var fieldsets = container.find(parent_fieldset_selector)
          .not(container.find(parent_fieldset_selector + ' ' + parent_fieldset_selector))
          .hide();

        fieldsets.filter(':last').after($('<div/>').append(addBtn));
        var count = 0;
        $.each(fieldsets, function(i, fieldset){
          var val = $(fieldset).find(':input').val();
          if (val.length > 0){
            count += 1;
          }
        })
        if (count > 1) {
          for( var i = 0; i < count; i++ ) {
            addBtn.click();
          }
        }
        else {
          for( var i = 0; i < numberFirstShown; i++ ) {
            addBtn.click();
          }
        }
      }
    }

    Drupal.settings.webform_addmore.collections = new Array();
    $.each(
      Drupal.settings.webform_addmore.fieldsets,
      function(i, fieldset) {
        var parent_fieldset = $('#' + fieldset).parents('fieldset');
        if (parent_fieldset.length > 0) {
          var parent_id = parent_fieldset.attr('id');
          if ($.inArray(parent_id, Drupal.settings.webform_addmore.collections) < 0) {
            Drupal.settings.webform_addmore.collections.push(parent_id);
          }
        }
        $('#' + fieldset).addClass('webform-addmore');
      }
    );



    fieldsetRepeater($('.webform-client-form'), '.webform-addmore', Drupal.settings.webform_addmore.addlabel, Drupal.settings.webform_addmore.dellabel, 1);
  }
};

})(jQuery);
