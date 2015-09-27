<?php

/**
 * @file
 * Provides an authentication method to Services.
 */

/**
 * Services authentication "authenticate_call" callback.
 */
function oauth2_server_services_authenticate_call($auth_settings, $controller, $args) {
  if (empty($auth_settings['require_authentication'])) {
    return FALSE;
  }
  // No server specified, cannot proceed.
  if (empty($auth_settings['server'])) {
    throw new Exception('No server configured for Services OAuth2 authentication.');
  }

  // Verify access. The request will be aborted if verification fails.
  $token = oauth2_server_verify_access($auth_settings['server'], $auth_settings['scope']);
  // If the resource owner is known, switch the current user to it.
  if ($token['user_id']) {
    global $user;
    $user = user_load($token['user_id']);
  }
}

/**
 * Services authentication "security_settings" callback.
 */
function oauth2_server_services_security_settings($settings, &$form_state) {
  if (isset($form_state['values']['oauth2']['server'])) {
    $settings['server'] = $form_state['values']['oauth2']['server'];
  }

  $options = array('' => t('- Select -'));
  $servers = entity_load('oauth2_server');
  foreach ($servers as $server) {
    $options[$server->name] = $server->label;
  }

  $form = array();
  $form['server'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => isset($settings['server']) ? $settings['server'] : '',
    '#title' => t('OAuth2 server'),
    '#required' => TRUE,
  );

  return $form;
}

/**
 * Services authentication "default_security_settings" callback.
 */
function oauth2_server_services_default_security_settings() {
  return array(
    'server' => '',
  );
}

/**
 * Services authentication "controller_settings" callback.
 */
function oauth2_server_services_controller_settings($settings, $controller, $endpoint, $class, $name) {
  $form = array();
  $form['require_authentication'] = array(
    '#type' => 'checkbox',
    '#title' => t('Require authentication'),
    '#default_value' => isset($settings['require_authentication']) ? $settings['require_authentication'] : FALSE,
  );
  $form['scope'] = array(
    '#type' => 'textfield',
    '#title' => t('Scope'),
    '#default_value' => isset($settings['scope']) ? $settings['scope'] : '',
    '#description' => t('A space-separated list of required scopes. Leave empty to ignore the check.'),
  );

  return $form;
}
