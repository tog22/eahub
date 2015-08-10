<?php

/**
 * @file
 * Export of OAuth login provider's OAuth context
 */

/**
 * Implementation of hook_default_oauth_common_context().
 */
function oauthloginprovider_default_oauth_common_context() {
  $contexts = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 1;
  $context->name = 'oauthlogin';
  $context->title = 'OAuth login';
  $context->authorization_options = array(
    'access_token_lifetime' => '120',
    'page_title' => 'Login to @appname',
    'message' => 'Hi @user! Click on the "login" button to log in to @appname. This will log you in to @appname and give it access to details like your username and email, but not to your password.',
    'warning' => 'Click here if you didn\'t ask to be logged in to @appname.',
    'deny_access_title' => 'Cancel',
    'grant_access_title' => 'Login',
    'disable_auth_level_selection' => 1,
    'signature_methods' => array('HMAC-SHA1', 'HMAC-SHA256', 'HMAC-SHA384', 'HMAC-SHA512'),
    'default_authorization_levels' => array('user_info'),
  );
  $context->authorization_levels = array(
    'user_info' => array(
      'title' => 'Yes, I want to log in to @appname as @user',
      'description' => 'This will log you in to @appname and give it access to details like your username and email, but not to your password.',
    ),
  );
  $contexts[$context->name] = $context;

  return $contexts;
}
 