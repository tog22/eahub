<?php
/**
 * @file
 * Drush hooks for the OAuth2 Server module.
 */

/**
 * Implements hook_sql_sync_sanitize().
 */
function oauth2_server_drush_sql_sync_sanitize($site) {
  $sql = 'TRUNCATE TABLE oauth2_server_token;'
   . 'TRUNCATE TABLE oauth2_server_authorization_code;'
   . "UPDATE oauth2_server_client SET client_secret = '';";

  drush_sql_register_post_sync_op('oauth2_server', dt('Remove sensitive OAuth2 Server data'), $sql);
}
