<?php
/**
 * @file
 * Administrative page callbacks for the Livefyre module.
 */

/**
 * Menu callback; Displays the administration settings for Livefyre.
 */
function livefyre_admin_settings_form($form, &$form_state) {
  $form = array();
  $form['livefyre_disabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable Livefyre comments?'),
    '#default_value' => variable_get('livefyre_disabled', FALSE),
    '#description' => t('Need to kill the comments real quick-like? Prevent Livefyre comments from being displayed by checking this box.'),
  );
  $form['livefyre_acct_num'] = array(
    '#type' => 'textfield',
    '#title' => t('Site ID'),
    '#default_value' => variable_get('livefyre_acct_num', ''),
    '#description' => t('This is the Livefyre account number, unique to each account.'),
  );
  if (user_access('add livefyre html')) {
    $form['livefyre_supplied_js'] = array(
      '#type' => 'textfield',
      '#title' => t('Path to script supplied by Livefyre'),
      '#default_value' => variable_get('livefyre_supplied_js', ''),
      '#description' => t("Post the path to the script supplied by Livefyre. Paths only. No quotation marks or spaces allowed. <br /> <br /> According to the current Livefyre site, the current Livefyre javascript file references Version 3:<br /><strong>%url</strong><br /><br />For older installs using v1,<br /><strong>%urlv1</strong><br />...should still work fine.  <br /><br /><strong>Site Keys are not needed in the Drupal install at this time.</strong><br /><br />Please note: <br />I'm not affiliated with Livefyre so I rely on input from them and/or the community to update this module so these paths could change.", array('%url' => 'http://zor.livefyre.com/wjs/v3.0/javascripts/livefyre.js', '%urlv1' => 'http://zor.livefyre.com/wjs/v1.0/javascripts/livefyre_init.js')),
    );
  }
  if (user_access('add livefyre html')) {
    $form['advanced_settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('Optional Advanced Settings: Custom HTML, CSS, Javascript'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['advanced_settings']['livefyre_parent_div'] = array(
      '#type' => 'textfield',
      '#title' => t('Nest the Livefyre div within my custom div (Optional)'),
      '#default_value' =>  variable_get('livefyre_parent_div', ''),
      '#description' => t('By default, the Livefyre Comment javascript inserts a div with an id of "livefyre" into your page.  It looks like this:<br /><br /> <code>@<div></code><br /><br />For display/theming purposes, it\'s possible to surround the @<div> with your own custom div.  Please enter its ID here and note that <strong>only a div ID can be used.</strong>  For example, if you wanted to nest the @<div> within a div having the ID of "my_comment_div", then enter "my_comment_div" (without the quotes, obviously) into the textfield above.  <br /><br />The resulting html would look like this: <br /><br /><code> @<div2></code>', array('@<div>' => '<div id="livefyre"></div>', '@<div2>' => '<div id="my_comment_div"><div id="livefyre"></div></div>')),
    );
    $form['advanced_settings']['livefyre_custom_instantiate_lf'] = array(
      '#type' => 'checkbox',
      '#title' => t('<strong>v1.0 USERS ONLY:  Are you using a custom script that instantiates Livefyre\'s LF function?</strong><br />If so, check this box.  If not, leave it blank.'),
      '#default_value' => variable_get('livefyre_custom_instantiate_lf', ''),
      '#description' => t("It's possible to instantiate Livefyre's LF function with your own custom javascript.  If you are doing this, check this box.  This will ensure that the LF function does not get called twice.  If you will be instantiating the LF function with your own custom script be sure to include it in the \"Custom HTML Snippet\" box below."),
    );
    $form['advanced_settings']['livefyre_custom_script_snippet'] = array(
      '#type' => 'textarea',
      '#title' => t('Custom HTML Snippet'),
      '#default_value' => variable_get('livefyre_custom_script_snippet', ''),
      '#rows' => 5,
      '#wysiwyg' => FALSE,
      '#description' => t("Need tracking? Or other variables for your Livefyre comments? Put in your custom HTML and/or javascript here. For javascript make sure to include @<script> tags and be careful.  Messing this up could have bad effects on your site!", array('@<script>' => '<script>')),
    );
  }
  $form['livefyre_location'] = array(
    '#type' => 'select',
    '#title' => t('Location'),
    '#description' => t('Display the Livefyre Comments in the given location. If you select "Content Area" the comments will show up on a node view.  Choose what types of nodes below. <br /><br />When "Block" is selected, the comments will appear in the Livefyre Comments block on <a href="@livefyre">the "Blocks" page</a>.', array('@livefyre' => url('admin/structure/block'))),
    '#default_value' => variable_get('livefyre_location', 'content_area'),
    '#options' => array(
      'content_area' => t('Content Area'),
      'block' => t('Block'),
    ),
    '#attached' => array(
      'js' => array(
        'vertical-tabs' => drupal_get_path('module', 'livefyre') . "/js/livefyre_hide_and_show.js"
      ),
    ),
  );
  $form['livefyre_weight'] = array(
    '#type' => 'select',
    '#title' => t('Weight'),
    '#description' => t('When the comments are displayed in the content area, you can change the position at which they will be shown.'),
    '#default_value' => variable_get('livefyre_weight', 50),
    '#options' => drupal_map_assoc(array(-100, -50, -25, 0, 25, 50, 100)),
  );
  $form['livefyre_node_types'] = array(
    '#type' => 'checkboxes',
    '#default_value' => variable_get('livefyre_node_types', array()),
    '#title' => t('Show Livefyre Comments on these node Types'),
    '#description' => t('Display comments only on the selected node types'),
    '#options' => node_type_get_names(),
  );
  return system_settings_form($form);
}

/**
 * Checks for correct permissions, values and file origin.
 */
function livefyre_admin_settings_form_validate($form, &$form_state) {
  if (!is_numeric($form_state['values']['livefyre_acct_num'])) {
    form_set_error('livefyre_acct_num', t("Livefyre account number should be a number."));
  }
  // Make sure the js file originates from Livefyre.com.
  $domain = parse_url($form_state['values']['livefyre_supplied_js']);
  $pieces = array_reverse(explode('.', $domain['host']));
  if (!preg_match("/^com$/", $pieces[0])   ||   !preg_match("/^livefyre$/", $pieces[1])) {
    form_set_error('livefyre_supplied_js', t("Path to Livefyre javascript file must originate from Livefyre.com."));
  }
}
