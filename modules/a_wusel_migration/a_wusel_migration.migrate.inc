<?php


/**
 * @file
 * Our own hook implementation.
 */
/**
 * Implements hook_migrate_api()
 *
 * Returns 'api' => 2 for the 7.x-2.x branch of Migrate.
 * Registers the migration classes for the 7.x-2.6 branch of Migrate (including
 * 7.x-2.6+xx-dev).
 */
function a_wusel_migration_migrate_api() {
  $api = array(
    'api' => 2,
    // Migrations can be organized into groups. The key used here will be the
    // machine name of the group, which can be used in Drush:
    //  drush migrate-import --group=WuselMigrate
    // The title is a required argument which is displayed for the group in the
    // UI. You may also have additional arguments for any other data which is
    // common to all migrations in the group.
    'groups' => array(
      'WuselMigrate' => array(
        'title' => t('WuselMigrate Imports'),
      ),
    ),
    // Here we register the individual migrations. The keys (Wusel_Step1_User,
    // etc.) are the machine names of the migrations, and the class_name
    // argument is required. The group_name is optional (defaulting to 'default')
    // but specifying it is a best practice.
    'migrations' => array(
      'Wusel_Step1_User' => array(
        'class_name' => 'Wusel_Step1_UserMigration',
        'group_name' => 'WuselMigrate',
      ),
      'Wusel_Step2_Memberlist' => array(
        'class_name' => 'Wusel_Step2_MemberlistMigration',
        'group_name' => 'WuselMigrate',
      ),
      'Wusel_Step3_raw_survey_text' => array(
        'class_name' => 'Wusel_Step3_raw_survey_text',
        'group_name' => 'WuselMigrate',
      ),
      'Wusel_Step3b_hidden_internal_profile2' => array(
        'class_name' => 'Wusel_Step3b_hidden_internal_profile2',
        'group_name' => 'WuselMigrate',
      ),
      'Wusel_Step4_your_views_and_values' => array(
        'class_name' => 'Wusel_Step4_your_views_and_values',
        'group_name' => 'WuselMigrate',
      ),
      'Wusel_Step5_you_and_ea' => array(
        'class_name' => 'Wusel_Step5_you_and_ea',
        'group_name' => 'WuselMigrate',
      ),
      'Wusel_Step6_your_career' => array(
        'class_name' => 'Wusel_Step6_your_career',
        'group_name' => 'WuselMigrate',
      ),
      'Wusel_Step7_basic_information' => array(
        'class_name' => 'Wusel_Step7_basic_information',
        'group_name' => 'WuselMigrate',
      ),
    ),
  );
  return $api;
}
?>

<?php
/**
 * Migration classes for migrating users and profiles
 *
 * based on: drupal.org/node/1269066#comment-4988994
 * and:      drupal.org/node/1190958#comment-4616032
 */
/**
 * Abstract class as a base for all our migration classes
 */
abstract class Wusel_Basic_Migration extends Migration {
  public function __construct($arguments) {
    // Always call the parent constructor first for basic setup
    parent::__construct($arguments);
    // Avoid known line ending issue: "Invalid data value" at drupal.org/node/1152158#InvalidDataValue
    ini_set('auto_detect_line_endings', TRUE);
  }
}
?>

<?php
/**
 * User-only migration - not profile fields
 *
 * The data file is assumed to be in
 *   sites/all/modules/a_wusel_migration/data_sources/
 */
class Wusel_Step1_UserMigration extends Wusel_Basic_Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Import an CSV-file (only "Account"-fields)');
    $columns = array(
      // "Source": ('Fieldname', 'Description')
      0 => array('MID', t('Member-ID (must be unique)')),
      1 => array('mail', t('Email (Account)')),
      2 => array('name', t('Name (Account)')),
      3 => array('password', t('Password (Account)'))
    );
    // TIP: delete ", array('header_rows' => 1)" in the next line, if the CSV-file has NO header-line
    $this->source = new MigrateSourceCSV(DRUPAL_ROOT . '/' . drupal_get_path('module', 'a_wusel_migration') . '/data_sources/drupaluser_import.csv', $columns, array('header_rows' => 1, 'delimiter' => '}', 'enclosure' => '`'));
    
    $this->destination = new MigrateDestinationUser();
    $this->map = new MigrateSQLMap($this->machineName,
        array('MID' => array( // this field is used to connect user und profile2
                'type' => 'varchar',
                'length' => 6,
                'not null' => TRUE,
                'description' => t('User\'s Member-ID') // description never used
              )
             ),
        MigrateDestinationUser::getKeySchema()
    );
    // Mapped fields
    $this->addSimpleMappings(array('name'));
    $this->addFieldMapping('mail', 'mail')
      ->defaultValue('')
      ->description(t('Email address'));
    $this->addFieldMapping('init')
      ->defaultValue('')
      ->description(t('Email address used for initial account creation'));
    $this->addFieldMapping('pass', 'password')
      ->defaultValue('asdf')
      ->description(t("User's password (plain text)"));
    $this->addFieldMapping('is_new')
      ->defaultValue(TRUE)
      ->description(t('Build the new user (0|1)'));
    $this->addFieldMapping('roles')
      ->defaultValue(DRUPAL_AUTHENTICATED_RID)
      ->description(DRUPAL_AUTHENTICATED_RID . t(' = "authenticated user"'));
    $this->addFieldMapping('theme')
      ->defaultValue('')
      ->description(t("User's default theme"));
    $this->addFieldMapping('signature')
      ->defaultValue('')
      ->description(t("User's signature"));
    $this->addFieldMapping('signature_format')
      ->defaultValue('filtered_html')
      ->description(t('Which filter applies to this signature'));
    $this->addFieldMapping('created')
      ->defaultValue(time())
      ->description(t('UNIX timestamp of user creation date'));
    $this->addFieldMapping('access')
      ->defaultValue(0)
      ->description(t('UNIX timestamp for previous time user accessed the site'));
    $this->addFieldMapping('login')
      ->defaultValue(0)
      ->description(t('UNIX timestamp for user\'s last login'));
    $this->addFieldMapping('status')
      ->defaultValue(1)
      ->description(t('Whether the user is active(1) or blocked(0)'));
    $this->addFieldMapping('timezone')
      ->defaultValue(t('Europe/London')) // 'America/Los_Angeles', 'Europe/Berlin', 'UTC', ... from drupal.org/node/714214
      ->description(t("User's time zone"));
    $this->addFieldMapping('language')
      ->defaultValue(t('en')) // e.g.: 'en', 'fr', 'de', ...
      ->description(t("User's default language"));
    $this->addFieldMapping('picture')
      ->defaultValue(0)
      ->description(t('Avatar of the user'));
    // Other handlers
    if (module_exists('path')) {
      $this->addFieldMapping('path')
           ->defaultValue(NULL)
           ->description(t('Path alias'));
    }
    if (module_exists('pathauto')) {
      $this->addFieldMapping('pathauto')
        ->defaultValue(1)
        ->description(t('Perform aliasing (set to 0 to prevent alias generation during migration)'));
    }
    // Unmapped destination fields
    $this->addUnmigratedDestinations(array('role_names', 'data'));
  }
}
?>

<?php
/**
 * Profile2 field migration
 *
 * The data file is assumed to be in
 *   sites/all/modules/a_wusel_migration/data_sources/
 */
class Wusel_Step2_MemberlistMigration extends Wusel_Basic_Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);
    global $user;
    $this->description = t('Import an CSV-file with Profile2-fields ("donations"-fields)');
    $columns = array(
      // "Source": ('Fieldname', 'Description')
      
      0 => array('MID', t('MID (member ID for mapping)')),
      1 => array('mail', t('Email (Account)')),
      2 => array('name', t('Name (Account)')),
      3 => array('password', t('Password (Account)')),
      4 => array('2013total', t('2013total')),
      5 => array('2013income', t('2013income')),
      6 => array('2013charities', t('2013charities')),
      7 => array('lifetime-donations', t('lifetime-donations')),
      8 => array('plan-text', t('plan-text')),
      9 => array('plan-causes', t('plan-causes')),
      10 => array('plan-until', t('plan-until')),
      11 => array('plan-extra', t('plan-extra'))
    );
    // TIP: delete ", array('header_rows' => 1)" in the next line, if the CSV-file has NO header-line
    $this->source = new MigrateSourceCSV(DRUPAL_ROOT . '/' . drupal_get_path('module', 'a_wusel_migration') . '/data_sources/drupaluser_import.csv', $columns, array('header_rows' => 1, 'delimiter' => '}', 'enclosure' => '`'));
    
        
    
    // Declare migration 'Wusel_Step1_User' a dependency in migration 'Wusel_Step2_Memberlist' to have them run in the right order, if needed:
    $this->dependencies = array('Wusel_Step1_User');
    $this->destination = new MigrateDestinationProfile2('donations');  // 'memberlist' is the "Machine name" of the profile2-"Profile type"
    $this->map = new MigrateSQLMap($this->machineName,
        array('MID' => array( // this field is used to connect user und profile2
                'type' => 'varchar',
                'length' => 6,
                'not null' => TRUE,
                'description' => t('User\'s Member-ID') // description never used
              )
             ),
        MigrateDestinationProfile2::getKeySchema()
    );
    $this->addFieldMapping('uid', 'MID') // Connecting the profile2 to the user using 'MID' - this row is "the trick"
         ->sourceMigration('Wusel_Step1_User')  // If your user migration class was named 'MyUserMigration', the string is 'MyUser'
         ->description(t('The assignment of profile2-items to the respective user'));
    // Mapped fields
    $this->addFieldMapping('field_mnr', 'MID')
      ->defaultValue(0)
      ->description(t('The Member-ID (must be unique)'));
    /* Delete this line, if you need the following:
    $this->addFieldMapping('field_mnr:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the Member-ID'));
    /* */
    $this->addFieldMapping('field_mnr:language')
      ->defaultValue('und')
      ->description(t('The language of the Member-ID<br />("und" = no language)'));
    $this->addFieldMapping('field_username', 'name')
      ->defaultValue('')
      ->description(t('The login name'));
    /* Delete this line, if you need the following:
    $this->addFieldMapping('field_username:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the login name'));
    /* */
    $this->addFieldMapping('field_username:language')
      ->defaultValue(t('en'))
      ->description(t('The language of the login name'));
    $this->addFieldMapping('field_name', 'complete_name')
      ->defaultValue('')
      ->description(t('The complete name (for Memberlist)'));
    /* Delete this line, if you need the following:
    $this->addFieldMapping('field_name:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the complete name'));
    /* */
    $this->addFieldMapping('field_name:language')
      ->defaultValue(t('en'))
      ->description(t('The language of the complete name'));
      
      
      
      /*****************************
      mappings only for fieldset in this class
      *****************************/
      
      
      
      
      
    $this->addFieldMapping('field_over_2013_how_much_in_tota', '2013total')
      ->defaultValue('')
      ->description(t('No description'));
    $this->addFieldMapping('field_what_was_your_pre_tax_inco', '2013income')
      ->defaultValue('')
      ->description(t('No description'));
    $this->addFieldMapping('field_over_2013_which_charities_', '2013charities')
      ->defaultValue('')
      ->description(t('No description'))
      ->separator('^');
    $this->addFieldMapping('field_how_much_have_you_donated_', 'lifetime-donations')
      ->defaultValue('')
      ->description(t('No description'));
    $this->addFieldMapping('field_do_you_plan_to_donate_a_ce', 'plan-text')
      ->defaultValue('')
      ->description(t('No description'));
    $this->addFieldMapping('field_if_so_to_which_causes_', 'plan-causes')
      ->defaultValue('')
      ->description(t('No description'))
      ->separator('^');
    $this->addFieldMapping('field_if_so_until_when_', 'plan-until')
      ->defaultValue('')
      ->description(t('No description'));
    $this->addFieldMapping('field_would_you_like_to_give_any', 'plan-extra')
      ->defaultValue('')
      ->description(t('No description'));
      
      
      
      
    
    // Other handlers
    /* Delete this line, if you need the following:
    if (module_exists('path')) {
      $this->addFieldMapping('path')
           ->defaultValue(NULL)
           ->description(t('Path alias'));
    }
    /* */
    // some internal fields
    $this->addFieldMapping('revision_uid')
      ->defaultValue($user->uid)
      ->description(t('The user ID of the user, who started the migration'));
    $this->addFieldMapping('language')
      ->defaultValue(t('en'))
      ->description(t("The default language of the user (e.g. 'en', 'fr', 'de')"));
    // Unmapped fields (this fields are in core and not needed as profile2-fields)
    $this->addUnmigratedSources(array('mail', 'password'));
  }
  public function fixTimestamp($date) {
    // enable empty (= unknown) birthday-string:
    if (strlen($date) > 0) {
      $date = substr($date, 0, 10) . 'T12:00:00'; // we add 'twelve o'clock in the daytime' for automatic compensation of a website time zone difference to UTC
    }
    return $date;
  }
}
?>




<?php
/**
 * Profile2 field migration
 *
 * The data file is assumed to be in
 *   sites/all/modules/a_wusel_migration/data_sources/
 */
class Wusel_Step3_raw_survey_text extends Wusel_Basic_Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);
    global $user;
    $this->description = t('Import an CSV-file with Profile2-fields ("donations"-fields)');
    $columns = array(
      // "Source": ('Fieldname', 'Description')
      
      0 => array('MID', t('MID (member ID for mapping)')),
      1 => array('mail', t('Email (Account)')),
      2 => array('name', t('Name (Account)')),
      3 => array('password', t('Password (Account)')),
      4 => array('2013total', t('2013total')),
      5 => array('2013income', t('2013income')),
      6 => array('2013charities', t('2013charities')),
      7 => array('lifetime-donations', t('lifetime-donations')),
      8 => array('plan-text', t('plan-text')),
      9 => array('plan-causes', t('plan-causes')),
      10 => array('plan-until', t('plan-until')),
      11 => array('plan-extra', t('plan-extra')),
      12 => array('raw_survey_text', t('raw_survey_text'))
    );
    // TIP: delete ", array('header_rows' => 1)" in the next line, if the CSV-file has NO header-line
    $this->source = new MigrateSourceCSV(DRUPAL_ROOT . '/' . drupal_get_path('module', 'a_wusel_migration') . '/data_sources/drupaluser_import.csv', $columns, array('header_rows' => 1, 'delimiter' => '}', 'enclosure' => '`'));
        
    // Declare migration 'Wusel_Step1_User' a dependency in migration 'Wusel_Step2_Memberlist' to have them run in the right order, if needed:
    $this->dependencies = array('Wusel_Step1_User');
    $this->destination = new MigrateDestinationProfile2('raw_survey_text');  // CHANGE THIS -  the "Machine name" of the profile2-"Profile type"
    $this->map = new MigrateSQLMap($this->machineName,
        array('MID' => array( // this field is used to connect user und profile2
                'type' => 'varchar',
                'length' => 6,
                'not null' => TRUE,
                'description' => t('User\'s Member-ID') // description never used
              )
             ),
        MigrateDestinationProfile2::getKeySchema()
    );
    $this->addFieldMapping('uid', 'MID') // Connecting the profile2 to the user using 'MID' - this row is "the trick"
         ->sourceMigration('Wusel_Step1_User')  // If your user migration class was named 'MyUserMigration', the string is 'MyUser'
         ->description(t('The assignment of profile2-items to the respective user'));
    // Mapped fields
    $this->addFieldMapping('field_mnr', 'MID')
      ->defaultValue(0)
      ->description(t('The Member-ID (must be unique)'));
    /* Delete this line, if you need the following:
    $this->addFieldMapping('field_mnr:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the Member-ID'));
    /* */
    $this->addFieldMapping('field_mnr:language')
      ->defaultValue('und')
      ->description(t('The language of the Member-ID<br />("und" = no language)'));
    $this->addFieldMapping('field_username', 'name')
      ->defaultValue('')
      ->description(t('The login name'));
    /* Delete this line, if you need the following:
    $this->addFieldMapping('field_username:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the login name'));
    /* */
    $this->addFieldMapping('field_username:language')
      ->defaultValue(t('en'))
      ->description(t('The language of the login name'));
    $this->addFieldMapping('field_name', 'complete_name')
      ->defaultValue('')
      ->description(t('The complete name (for Memberlist)'));
    /* Delete this line, if you need the following:
    $this->addFieldMapping('field_name:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the complete name'));
    /* */
    $this->addFieldMapping('field_name:language')
      ->defaultValue(t('en'))
      ->description(t('The language of the complete name'));
      
      
      
      /*****************************
      mappings only for fieldset in this class
      *****************************/
      
      
      
      
      
    $this->addFieldMapping('field_raw_survey_text', 'raw_survey_text')
      ->defaultValue('')
      ->description(t('raw_survey_text import'))
      ->arguments(array('format' => 'full_html'));
      
      
      
      
    
    // Other handlers
    /* Delete this line, if you need the following:
    if (module_exists('path')) {
      $this->addFieldMapping('path')
           ->defaultValue(NULL)
           ->description(t('Path alias'));
    }
    /* */
    // some internal fields
    $this->addFieldMapping('revision_uid')
      ->defaultValue($user->uid)
      ->description(t('The user ID of the user, who started the migration'));
    $this->addFieldMapping('language')
      ->defaultValue(t('en'))
      ->description(t("The default language of the user (e.g. 'en', 'fr', 'de')"));
    // Unmapped fields (this fields are in core and not needed as profile2-fields)
    $this->addUnmigratedSources(array('mail', 'password'));
  }
  public function fixTimestamp($date) {
    // enable empty (= unknown) birthday-string:
    if (strlen($date) > 0) {
      $date = substr($date, 0, 10) . 'T12:00:00'; // we add 'twelve o'clock in the daytime' for automatic compensation of a website time zone difference to UTC
    }
    return $date;
  }
}
?>



<?php
/**
 * Profile2 field migration
 *
 * The data file is assumed to be in
 *   sites/all/modules/a_wusel_migration/data_sources/
 */
class Wusel_Step3b_hidden_internal_profile2 extends Wusel_Basic_Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);
    global $user;
    $this->description = t('Import an CSV-file with Profile2-fields ("donations"-fields)');
    $columns = array(
      // "Source": ('Fieldname', 'Description')
      
      0 => array('MID', t('MID (member ID for mapping)')),
      1 => array('mail', t('Email (Account)')),
      2 => array('name', t('Name (Account)')),
      3 => array('password', t('Password (Account)')),
      4 => array('2013total', t('2013total')),
      5 => array('2013income', t('2013income')),
      6 => array('2013charities', t('2013charities')),
      7 => array('lifetime-donations', t('lifetime-donations')),
      8 => array('plan-text', t('plan-text')),
      9 => array('plan-causes', t('plan-causes')),
      10 => array('plan-until', t('plan-until')),
      11 => array('plan-extra', t('plan-extra')),
      12 => array('raw_survey_text', t('raw_survey_text')),
      13 => array('field_weighting', t('field_weighting')),
      14 => array('field_has_profile_data', t('field_has_profile_data'))
    );
    // TIP: delete ", array('header_rows' => 1)" in the next line, if the CSV-file has NO header-line
    $this->source = new MigrateSourceCSV(DRUPAL_ROOT . '/' . drupal_get_path('module', 'a_wusel_migration') . '/data_sources/drupaluser_import.csv', $columns, array('header_rows' => 1, 'delimiter' => '}', 'enclosure' => '`'));
    
    // Declare migration 'Wusel_Step1_User' a dependency in migration 'Wusel_Step2_Memberlist' to have them run in the right order, if needed:
    $this->dependencies = array('Wusel_Step1_User');
    $this->destination = new MigrateDestinationProfile2('hidden_internal_profile2');  // CHANGE THIS -  the "Machine name" of the profile2-"Profile type"
    $this->map = new MigrateSQLMap($this->machineName,
        array('MID' => array( // this field is used to connect user und profile2
                'type' => 'varchar',
                'length' => 6,
                'not null' => TRUE,
                'description' => t('User\'s Member-ID') // description never used
              )
             ),
        MigrateDestinationProfile2::getKeySchema()
    );
    $this->addFieldMapping('uid', 'MID') // Connecting the profile2 to the user using 'MID' - this row is "the trick"
         ->sourceMigration('Wusel_Step1_User')  // If your user migration class was named 'MyUserMigration', the string is 'MyUser'
         ->description(t('The assignment of profile2-items to the respective user'));
    // Mapped fields
    $this->addFieldMapping('field_mnr', 'MID')
      ->defaultValue(0)
      ->description(t('The Member-ID (must be unique)'));
    /* Delete this line, if you need the following:
    $this->addFieldMapping('field_mnr:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the Member-ID'));
    /* */
    $this->addFieldMapping('field_mnr:language')
      ->defaultValue('und')
      ->description(t('The language of the Member-ID<br />("und" = no language)'));
    $this->addFieldMapping('field_username', 'name')
      ->defaultValue('')
      ->description(t('The login name'));
    /* Delete this line, if you need the following:
    $this->addFieldMapping('field_username:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the login name'));
    /* */
    $this->addFieldMapping('field_username:language')
      ->defaultValue(t('en'))
      ->description(t('The language of the login name'));
    $this->addFieldMapping('field_name', 'complete_name')
      ->defaultValue('')
      ->description(t('The complete name (for Memberlist)'));
    /* Delete this line, if you need the following:
    $this->addFieldMapping('field_name:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the complete name'));
    /* */
    $this->addFieldMapping('field_name:language')
      ->defaultValue(t('en'))
      ->description(t('The language of the complete name'));
      
      
      
      /*****************************
      mappings only for fieldset in this class
      *****************************/
      
      
    $this->addFieldMapping('field_weighting', 'field_weighting')
      ->defaultValue('')
      ->description(t('no description'));
    $this->addFieldMapping('field_has_profile_data', 'field_has_profile_data')
      ->defaultValue('')
      ->description(t('no description'));
      
      
      
    
    // Other handlers
    /* Delete this line, if you need the following:
    if (module_exists('path')) {
      $this->addFieldMapping('path')
           ->defaultValue(NULL)
           ->description(t('Path alias'));
    }
    /* */
    // some internal fields
    $this->addFieldMapping('revision_uid')
      ->defaultValue($user->uid)
      ->description(t('The user ID of the user, who started the migration'));
    $this->addFieldMapping('language')
      ->defaultValue(t('en'))
      ->description(t("The default language of the user (e.g. 'en', 'fr', 'de')"));
    // Unmapped fields (this fields are in core and not needed as profile2-fields)
    $this->addUnmigratedSources(array('mail', 'password'));
  }
  public function fixTimestamp($date) {
    // enable empty (= unknown) birthday-string:
    if (strlen($date) > 0) {
      $date = substr($date, 0, 10) . 'T12:00:00'; // we add 'twelve o'clock in the daytime' for automatic compensation of a website time zone difference to UTC
    }
    return $date;
  }
}
?>



<?php
/**
 * Profile2 field migration
 *
 * The data file is assumed to be in
 *   sites/all/modules/a_wusel_migration/data_sources/
 */
class Wusel_Step4_your_views_and_values extends Wusel_Basic_Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);
    global $user;
    $this->description = t('Import an CSV-file with Profile2-fields ("donations"-fields)');
    $columns = array(
      // "Source": ('Fieldname', 'Description')
      
      0 => array('MID', t('MID (member ID for mapping)')),
      1 => array('mail', t('Email (Account)')),
      2 => array('name', t('Name (Account)')),
      3 => array('password', t('Password (Account)')),
      4 => array('2013total', t('2013total')),
      5 => array('2013income', t('2013income')),
      6 => array('2013charities', t('2013charities')),
      7 => array('lifetime-donations', t('lifetime-donations')),
      8 => array('plan-text', t('plan-text')),
      9 => array('plan-causes', t('plan-causes')),
      10 => array('plan-until', t('plan-until')),
      11 => array('plan-extra', t('plan-extra')),
      12 => array('raw_survey_text', t('raw_survey_text')),
      13 => array('field_weighting', t('field_weighting')),
      14 => array('field_has_profile_data', t('field_has_profile_data')),
      15 => array('field_what_moral_philosophy_do_y', t('field_what_moral_philosophy_do_y')),
      16 => array('field_which_of_the_following_cau', t('field_which_of_the_following_cau')),
      17 => array('field_please_list_any_actions_yo', t('field_please_list_any_actions_yo')),
      18 => array('field_roughly_how_many_hours_a_m', t('field_roughly_how_many_hours_a_m')),
      19 => array('field_what_is_your_diet_', t('field_what_is_your_diet_')),
      20 => array('field_do_you_identify_with_any_o', t('field_do_you_identify_with_any_o'))
    );
    // TIP: delete ", array('header_rows' => 1)" in the next line, if the CSV-file has NO header-line
    $this->source = new MigrateSourceCSV(DRUPAL_ROOT . '/' . drupal_get_path('module', 'a_wusel_migration') . '/data_sources/drupaluser_import.csv', $columns, array('header_rows' => 1, 'delimiter' => '}', 'enclosure' => '`'));
    
    // Declare migration 'Wusel_Step1_User' a dependency in migration 'Wusel_Step2_Memberlist' to have them run in the right order, if needed:
    $this->dependencies = array('Wusel_Step1_User');
    $this->destination = new MigrateDestinationProfile2('your_views_and_values');  // CHANGE THIS -  the "Machine name" of the profile2-"Profile type"
    $this->map = new MigrateSQLMap($this->machineName,
        array('MID' => array( // this field is used to connect user und profile2
                'type' => 'varchar',
                'length' => 6,
                'not null' => TRUE,
                'description' => t('User\'s Member-ID') // description never used
              )
             ),
        MigrateDestinationProfile2::getKeySchema()
    );
    $this->addFieldMapping('uid', 'MID') // Connecting the profile2 to the user using 'MID' - this row is "the trick"
         ->sourceMigration('Wusel_Step1_User')  // If your user migration class was named 'MyUserMigration', the string is 'MyUser'
         ->description(t('The assignment of profile2-items to the respective user'));
    // Mapped fields
    $this->addFieldMapping('field_mnr', 'MID')
      ->defaultValue(0)
      ->description(t('The Member-ID (must be unique)'));
    /* Delete this line, if you need the following:
    $this->addFieldMapping('field_mnr:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the Member-ID'));
    /* */
    $this->addFieldMapping('field_mnr:language')
      ->defaultValue('und')
      ->description(t('The language of the Member-ID<br />("und" = no language)'));
    $this->addFieldMapping('field_username', 'name')
      ->defaultValue('')
      ->description(t('The login name'));
    /* Delete this line, if you need the following:
    $this->addFieldMapping('field_username:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the login name'));
    /* */
    $this->addFieldMapping('field_username:language')
      ->defaultValue(t('en'))
      ->description(t('The language of the login name'));
    $this->addFieldMapping('field_name', 'complete_name')
      ->defaultValue('')
      ->description(t('The complete name (for Memberlist)'));
    /* Delete this line, if you need the following:
    $this->addFieldMapping('field_name:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the complete name'));
    /* */
    $this->addFieldMapping('field_name:language')
      ->defaultValue(t('en'))
      ->description(t('The language of the complete name'));
      
      
      
      /*****************************
      mappings only for fieldset in this class
      *****************************/
      
      
    $this->addFieldMapping('field_what_moral_philosophy_do_y', 'field_what_moral_philosophy_do_y')
      ->defaultValue('')
      ->description(t('no description'));
    $this->addFieldMapping('field_which_of_the_following_cau', 'field_which_of_the_following_cau')
      ->defaultValue('')
      ->description(t('no description'))
      ->separator('^');
    $this->addFieldMapping('field_please_list_any_actions_yo', 'field_please_list_any_actions_yo')
      ->defaultValue('')
      ->description(t('no description'));
    $this->addFieldMapping('field_roughly_how_many_hours_a_m', 'field_roughly_how_many_hours_a_m')
      ->defaultValue('')
      ->description(t('no description'));
    $this->addFieldMapping('field_what_is_your_diet_', 'field_what_is_your_diet_')
      ->defaultValue('')
      ->description(t('no description'));
    $this->addFieldMapping('field_do_you_identify_with_any_o', 'field_do_you_identify_with_any_o')
      ->defaultValue('')
      ->description(t('no description'))
      ->separator('^');      
      
    
    // Other handlers
    /* Delete this line, if you need the following:
    if (module_exists('path')) {
      $this->addFieldMapping('path')
           ->defaultValue(NULL)
           ->description(t('Path alias'));
    }
    /* */
    // some internal fields
    $this->addFieldMapping('revision_uid')
      ->defaultValue($user->uid)
      ->description(t('The user ID of the user, who started the migration'));
    $this->addFieldMapping('language')
      ->defaultValue(t('en'))
      ->description(t("The default language of the user (e.g. 'en', 'fr', 'de')"));
    // Unmapped fields (this fields are in core and not needed as profile2-fields)
    $this->addUnmigratedSources(array('mail', 'password'));
  }
  public function fixTimestamp($date) {
    // enable empty (= unknown) birthday-string:
    if (strlen($date) > 0) {
      $date = substr($date, 0, 10) . 'T12:00:00'; // we add 'twelve o'clock in the daytime' for automatic compensation of a website time zone difference to UTC
    }
    return $date;
  }
}
?>



<?php
/**
 * Profile2 field migration
 *
 * The data file is assumed to be in
 *   sites/all/modules/a_wusel_migration/data_sources/
 */
class Wusel_Step5_you_and_ea extends Wusel_Basic_Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);
    global $user;
    $this->description = t('Import an CSV-file with Profile2-fields ("donations"-fields)');
    $columns = array(
      // "Source": ('Fieldname', 'Description')
      
      0 => array('MID', t('MID (member ID for mapping)')),
      1 => array('mail', t('Email (Account)')),
      2 => array('name', t('Name (Account)')),
      3 => array('password', t('Password (Account)')),
      4 => array('2013total', t('2013total')),
      5 => array('2013income', t('2013income')),
      6 => array('2013charities', t('2013charities')),
      7 => array('lifetime-donations', t('lifetime-donations')),
      8 => array('plan-text', t('plan-text')),
      9 => array('plan-causes', t('plan-causes')),
      10 => array('plan-until', t('plan-until')),
      11 => array('plan-extra', t('plan-extra')),
      12 => array('raw_survey_text', t('raw_survey_text')),
      13 => array('field_weighting', t('field_weighting')),
      14 => array('field_has_profile_data', t('field_has_profile_data')),
      15 => array('field_what_moral_philosophy_do_y', t('field_what_moral_philosophy_do_y')),
      16 => array('field_which_of_the_following_cau', t('field_which_of_the_following_cau')),
      17 => array('field_please_list_any_actions_yo', t('field_please_list_any_actions_yo')),
      18 => array('field_roughly_how_many_hours_a_m', t('field_roughly_how_many_hours_a_m')),
      19 => array('field_what_is_your_diet_', t('field_what_is_your_diet_')),
      20 => array('field_do_you_identify_with_any_o', t('field_do_you_identify_with_any_o')),
      21 => array('field_in_which_year_did_you_firs', t('field_in_which_year_did_you_firs')),
      22 => array('field_how_first_heard_about_ea', t('field_how_first_heard_about_ea')),
      23 => array('field_which_factors_were_importa', t('field_which_factors_were_importa')),
      24 => array('field_which_of_the_following_gro', t('field_which_of_the_following_gro')),
      25 => array('field_have_you_volunteered', t('field_have_you_volunteered')),
      26 => array('field_roughly_how_many_of_your_f', t('field_roughly_how_many_of_your_f'))
    );
    // TIP: delete ", array('header_rows' => 1)" in the next line, if the CSV-file has NO header-line
    $this->source = new MigrateSourceCSV(DRUPAL_ROOT . '/' . drupal_get_path('module', 'a_wusel_migration') . '/data_sources/drupaluser_import.csv', $columns, array('header_rows' => 1, 'delimiter' => '}', 'enclosure' => '`'));
    
    // Declare migration 'Wusel_Step1_User' a dependency in migration 'Wusel_Step2_Memberlist' to have them run in the right order, if needed:
    $this->dependencies = array('Wusel_Step1_User');
    $this->destination = new MigrateDestinationProfile2('you_and_ea');  // CHANGE THIS -  the "Machine name" of the profile2-"Profile type"
    $this->map = new MigrateSQLMap($this->machineName,
        array('MID' => array( // this field is used to connect user und profile2
                'type' => 'varchar',
                'length' => 6,
                'not null' => TRUE,
                'description' => t('User\'s Member-ID') // description never used
              )
             ),
        MigrateDestinationProfile2::getKeySchema()
    );
    $this->addFieldMapping('uid', 'MID') // Connecting the profile2 to the user using 'MID' - this row is "the trick"
         ->sourceMigration('Wusel_Step1_User')  // If your user migration class was named 'MyUserMigration', the string is 'MyUser'
         ->description(t('The assignment of profile2-items to the respective user'));
    // Mapped fields
    $this->addFieldMapping('field_mnr', 'MID')
      ->defaultValue(0)
      ->description(t('The Member-ID (must be unique)'));
    /* Delete this line, if you need the following:
    $this->addFieldMapping('field_mnr:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the Member-ID'));
    /* */
    $this->addFieldMapping('field_mnr:language')
      ->defaultValue('und')
      ->description(t('The language of the Member-ID<br />("und" = no language)'));
    $this->addFieldMapping('field_username', 'name')
      ->defaultValue('')
      ->description(t('The login name'));
    /* Delete this line, if you need the following:
    $this->addFieldMapping('field_username:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the login name'));
    /* */
    $this->addFieldMapping('field_username:language')
      ->defaultValue(t('en'))
      ->description(t('The language of the login name'));
    $this->addFieldMapping('field_name', 'complete_name')
      ->defaultValue('')
      ->description(t('The complete name (for Memberlist)'));
    /* Delete this line, if you need the following:
    $this->addFieldMapping('field_name:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the complete name'));
    /* */
    $this->addFieldMapping('field_name:language')
      ->defaultValue(t('en'))
      ->description(t('The language of the complete name'));
      
      
      
      /*****************************
      mappings only for fieldset in this class
      *****************************/
      
      
    $this->addFieldMapping('field_in_which_year_did_you_firs', 'field_in_which_year_did_you_firs')
      ->defaultValue('')
      ->description(t('no description'));
    $this->addFieldMapping('field_how_first_heard_about_ea', 'field_how_first_heard_about_ea')
      ->defaultValue('')
      ->description(t('no description'));
    $this->addFieldMapping('field_which_factors_were_importa', 'field_which_factors_were_importa')
      ->defaultValue('')
      ->description(t('no description'))
      ->separator('^');
    $this->addFieldMapping('field_which_of_the_following_gro', 'field_which_of_the_following_gro')
      ->defaultValue('')
      ->description(t('no description'))
      ->separator('^');
    $this->addFieldMapping('field_have_you_volunteered', 'field_have_you_volunteered')
      ->defaultValue('')
      ->description(t('no description'))
      ->separator('^');
    $this->addFieldMapping('field_roughly_how_many_of_your_f', 'field_roughly_how_many_of_your_f')
      ->defaultValue('')
      ->description(t('no description'));      
      
    
    // Other handlers
    /* Delete this line, if you need the following:
    if (module_exists('path')) {
      $this->addFieldMapping('path')
           ->defaultValue(NULL)
           ->description(t('Path alias'));
    }
    /* */
    // some internal fields
    $this->addFieldMapping('revision_uid')
      ->defaultValue($user->uid)
      ->description(t('The user ID of the user, who started the migration'));
    $this->addFieldMapping('language')
      ->defaultValue(t('en'))
      ->description(t("The default language of the user (e.g. 'en', 'fr', 'de')"));
    // Unmapped fields (this fields are in core and not needed as profile2-fields)
    $this->addUnmigratedSources(array('mail', 'password'));
  }
  public function fixTimestamp($date) {
    // enable empty (= unknown) birthday-string:
    if (strlen($date) > 0) {
      $date = substr($date, 0, 10) . 'T12:00:00'; // we add 'twelve o'clock in the daytime' for automatic compensation of a website time zone difference to UTC
    }
    return $date;
  }
}
?>


<?php
/**
 * Profile2 field migration
 *
 * The data file is assumed to be in
 *   sites/all/modules/a_wusel_migration/data_sources/
 */
class Wusel_Step6_your_career extends Wusel_Basic_Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);
    global $user;
    $this->description = t('Import an CSV-file with Profile2-fields ("donations"-fields)');
    $columns = array(
      // "Source": ('Fieldname', 'Description')
      
      0 => array('MID', t('MID (member ID for mapping)')),
      1 => array('mail', t('Email (Account)')),
      2 => array('name', t('Name (Account)')),
      3 => array('password', t('Password (Account)')),
      4 => array('2013total', t('2013total')),
      5 => array('2013income', t('2013income')),
      6 => array('2013charities', t('2013charities')),
      7 => array('lifetime-donations', t('lifetime-donations')),
      8 => array('plan-text', t('plan-text')),
      9 => array('plan-causes', t('plan-causes')),
      10 => array('plan-until', t('plan-until')),
      11 => array('plan-extra', t('plan-extra')),
      12 => array('raw_survey_text', t('raw_survey_text')),
      13 => array('field_weighting', t('field_weighting')),
      14 => array('field_has_profile_data', t('field_has_profile_data')),
      15 => array('field_what_moral_philosophy_do_y', t('field_what_moral_philosophy_do_y')),
      16 => array('field_which_of_the_following_cau', t('field_which_of_the_following_cau')),
      17 => array('field_please_list_any_actions_yo', t('field_please_list_any_actions_yo')),
      18 => array('field_roughly_how_many_hours_a_m', t('field_roughly_how_many_hours_a_m')),
      19 => array('field_what_is_your_diet_', t('field_what_is_your_diet_')),
      20 => array('field_do_you_identify_with_any_o', t('field_do_you_identify_with_any_o')),
      21 => array('field_in_which_year_did_you_firs', t('field_in_which_year_did_you_firs')),
      22 => array('field_how_first_heard_about_ea', t('field_how_first_heard_about_ea')),
      23 => array('field_which_factors_were_importa', t('field_which_factors_were_importa')),
      24 => array('field_which_of_the_following_gro', t('field_which_of_the_following_gro')),
      25 => array('field_have_you_volunteered', t('field_have_you_volunteered')),
      26 => array('field_roughly_how_many_of_your_f', t('field_roughly_how_many_of_your_f')),
      27 => array('field_what_career_path_do_you_pl', t('field_what_career_path_do_you_pl')),
      28 => array('field_how_confident_are_you_that', t('field_how_confident_are_you_that'))
    );
    // TIP: delete ", array('header_rows' => 1)" in the next line, if the CSV-file has NO header-line
    $this->source = new MigrateSourceCSV(DRUPAL_ROOT . '/' . drupal_get_path('module', 'a_wusel_migration') . '/data_sources/drupaluser_import.csv', $columns, array('header_rows' => 1, 'delimiter' => '}', 'enclosure' => '`'));
    
    // Declare migration 'Wusel_Step1_User' a dependency in migration 'Wusel_Step2_Memberlist' to have them run in the right order, if needed:
    $this->dependencies = array('Wusel_Step1_User');
    $this->destination = new MigrateDestinationProfile2('your_career');  // CHANGE THIS -  the "Machine name" of the profile2-"Profile type"
    $this->map = new MigrateSQLMap($this->machineName,
        array('MID' => array( // this field is used to connect user und profile2
                'type' => 'varchar',
                'length' => 6,
                'not null' => TRUE,
                'description' => t('User\'s Member-ID') // description never used
              )
             ),
        MigrateDestinationProfile2::getKeySchema()
    );
    $this->addFieldMapping('uid', 'MID') // Connecting the profile2 to the user using 'MID' - this row is "the trick"
         ->sourceMigration('Wusel_Step1_User')  // If your user migration class was named 'MyUserMigration', the string is 'MyUser'
         ->description(t('The assignment of profile2-items to the respective user'));
    // Mapped fields
    $this->addFieldMapping('field_mnr', 'MID')
      ->defaultValue(0)
      ->description(t('The Member-ID (must be unique)'));
    /* Delete this line, if you need the following:
    $this->addFieldMapping('field_mnr:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the Member-ID'));
    /* */
    $this->addFieldMapping('field_mnr:language')
      ->defaultValue('und')
      ->description(t('The language of the Member-ID<br />("und" = no language)'));
    $this->addFieldMapping('field_username', 'name')
      ->defaultValue('')
      ->description(t('The login name'));
    /* Delete this line, if you need the following:
    $this->addFieldMapping('field_username:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the login name'));
    /* */
    $this->addFieldMapping('field_username:language')
      ->defaultValue(t('en'))
      ->description(t('The language of the login name'));
    $this->addFieldMapping('field_name', 'complete_name')
      ->defaultValue('')
      ->description(t('The complete name (for Memberlist)'));
    /* Delete this line, if you need the following:
    $this->addFieldMapping('field_name:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the complete name'));
    /* */
    $this->addFieldMapping('field_name:language')
      ->defaultValue(t('en'))
      ->description(t('The language of the complete name'));
      
      
      
      /*****************************
      mappings only for fieldset in this class
      *****************************/
      
      
    $this->addFieldMapping('field_what_career_path_do_you_pl', 'field_what_career_path_do_you_pl')
      ->defaultValue('')
      ->description(t('no description'));
    $this->addFieldMapping('field_how_confident_are_you_that', 'field_how_confident_are_you_that')
      ->defaultValue('')
      ->description(t('no description'));      
      
      
    
    // Other handlers
    /* Delete this line, if you need the following:
    if (module_exists('path')) {
      $this->addFieldMapping('path')
           ->defaultValue(NULL)
           ->description(t('Path alias'));
    }
    /* */
    // some internal fields
    $this->addFieldMapping('revision_uid')
      ->defaultValue($user->uid)
      ->description(t('The user ID of the user, who started the migration'));
    $this->addFieldMapping('language')
      ->defaultValue(t('en'))
      ->description(t("The default language of the user (e.g. 'en', 'fr', 'de')"));
    // Unmapped fields (this fields are in core and not needed as profile2-fields)
    $this->addUnmigratedSources(array('mail', 'password'));
  }
  public function fixTimestamp($date) {
    // enable empty (= unknown) birthday-string:
    if (strlen($date) > 0) {
      $date = substr($date, 0, 10) . 'T12:00:00'; // we add 'twelve o'clock in the daytime' for automatic compensation of a website time zone difference to UTC
    }
    return $date;
  }
}
?>

<?php
/**
 * Profile2 field migration
 *
 * The data file is assumed to be in
 *   sites/all/modules/a_wusel_migration/data_sources/
 */
class Wusel_Step7_basic_information extends Wusel_Basic_Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);
    global $user;
    $this->description = t('Import an CSV-file with Profile2-fields ("donations"-fields)');
    $columns = array(
      // "Source": ('Fieldname', 'Description')
      
      0 => array('MID', t('MID (member ID for mapping)')),
      1 => array('mail', t('Email (Account)')),
      2 => array('name', t('Name (Account)')),
      3 => array('password', t('Password (Account)')),
      4 => array('2013total', t('2013total')),
      5 => array('2013income', t('2013income')),
      6 => array('2013charities', t('2013charities')),
      7 => array('lifetime-donations', t('lifetime-donations')),
      8 => array('plan-text', t('plan-text')),
      9 => array('plan-causes', t('plan-causes')),
      10 => array('plan-until', t('plan-until')),
      11 => array('plan-extra', t('plan-extra')),
      12 => array('raw_survey_text', t('raw_survey_text')),
      13 => array('field_weighting', t('field_weighting')),
      14 => array('field_has_profile_data', t('field_has_profile_data')),
      15 => array('field_what_moral_philosophy_do_y', t('field_what_moral_philosophy_do_y')),
      16 => array('field_which_of_the_following_cau', t('field_which_of_the_following_cau')),
      17 => array('field_please_list_any_actions_yo', t('field_please_list_any_actions_yo')),
      18 => array('field_roughly_how_many_hours_a_m', t('field_roughly_how_many_hours_a_m')),
      19 => array('field_what_is_your_diet_', t('field_what_is_your_diet_')),
      20 => array('field_do_you_identify_with_any_o', t('field_do_you_identify_with_any_o')),
      21 => array('field_in_which_year_did_you_firs', t('field_in_which_year_did_you_firs')),
      22 => array('field_how_first_heard_about_ea', t('field_how_first_heard_about_ea')),
      23 => array('field_which_factors_were_importa', t('field_which_factors_were_importa')),
      24 => array('field_which_of_the_following_gro', t('field_which_of_the_following_gro')),
      25 => array('field_have_you_volunteered', t('field_have_you_volunteered')),
      26 => array('field_roughly_how_many_of_your_f', t('field_roughly_how_many_of_your_f')),
      27 => array('field_what_career_path_do_you_pl', t('field_what_career_path_do_you_pl')),
      28 => array('field_how_confident_are_you_that', t('field_how_confident_are_you_that')),
      29 => array('field_your_age', t('field_your_age')),
      30 => array('field_your_gender', t('field_your_gender')),
      31 => array('field_full_time_student', t('field_full_time_student')),
      32 => array('field_what_is_the_highest_level_', t('field_what_is_the_highest_level_')),
      33 => array('field_in_which_country_do_you_li', t('field_in_which_country_do_you_li')),
      34 => array('field_in_which_city_do_you_live_', t('field_in_which_city_do_you_live_')),
      35 => array('field_your_political_views', t('field_your_political_views')),
      36 => array('field_your_religious_beliefs', t('field_your_religious_beliefs'))
    );
    // TIP: delete ", array('header_rows' => 1)" in the next line, if the CSV-file has NO header-line
    $this->source = new MigrateSourceCSV(DRUPAL_ROOT . '/' . drupal_get_path('module', 'a_wusel_migration') . '/data_sources/drupaluser_import.csv', $columns, array('header_rows' => 1, 'delimiter' => '}', 'enclosure' => '`'));
    
    // Declare migration 'Wusel_Step1_User' a dependency in migration 'Wusel_Step2_Memberlist' to have them run in the right order, if needed:
    $this->dependencies = array('Wusel_Step1_User');
    $this->destination = new MigrateDestinationProfile2('basic_information');  // CHANGE THIS -  the "Machine name" of the profile2-"Profile type"
    $this->map = new MigrateSQLMap($this->machineName,
        array('MID' => array( // this field is used to connect user und profile2
                'type' => 'varchar',
                'length' => 6,
                'not null' => TRUE,
                'description' => t('User\'s Member-ID') // description never used
              )
             ),
        MigrateDestinationProfile2::getKeySchema()
    );
    $this->addFieldMapping('uid', 'MID') // Connecting the profile2 to the user using 'MID' - this row is "the trick"
         ->sourceMigration('Wusel_Step1_User')  // If your user migration class was named 'MyUserMigration', the string is 'MyUser'
         ->description(t('The assignment of profile2-items to the respective user'));
    // Mapped fields
    $this->addFieldMapping('field_mnr', 'MID')
      ->defaultValue(0)
      ->description(t('The Member-ID (must be unique)'));
    /* Delete this line, if you need the following:
    $this->addFieldMapping('field_mnr:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the Member-ID'));
    /* */
    $this->addFieldMapping('field_mnr:language')
      ->defaultValue('und')
      ->description(t('The language of the Member-ID<br />("und" = no language)'));
    $this->addFieldMapping('field_username', 'name')
      ->defaultValue('')
      ->description(t('The login name'));
    /* Delete this line, if you need the following:
    $this->addFieldMapping('field_username:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the login name'));
    /* */
    $this->addFieldMapping('field_username:language')
      ->defaultValue(t('en'))
      ->description(t('The language of the login name'));
    $this->addFieldMapping('field_name', 'complete_name')
      ->defaultValue('')
      ->description(t('The complete name (for Memberlist)'));
    /* Delete this line, if you need the following:
    $this->addFieldMapping('field_name:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the complete name'));
    /* */
    $this->addFieldMapping('field_name:language')
      ->defaultValue(t('en'))
      ->description(t('The language of the complete name'));
      
      
      
      /*****************************
      mappings only for fieldset in this class
      *****************************/
      
      
    $this->addFieldMapping('field_your_age', 'field_your_age')
      ->defaultValue('')
      ->description(t('no description'));
    $this->addFieldMapping('field_your_gender', 'field_your_gender')
      ->defaultValue('')
      ->description(t('no description'));
    $this->addFieldMapping('field_full_time_student', 'field_full_time_student')
      ->defaultValue('')
      ->description(t('no description'));
    $this->addFieldMapping('field_what_is_the_highest_level_', 'field_what_is_the_highest_level_')
      ->defaultValue('')
      ->description(t('no description'));
    $this->addFieldMapping('field_in_which_country_do_you_li', 'field_in_which_country_do_you_li')
      ->defaultValue('')
      ->description(t('no description'));
    $this->addFieldMapping('field_in_which_city_do_you_live_', 'field_in_which_city_do_you_live_')
      ->defaultValue('')
      ->description(t('no description'));
    $this->addFieldMapping('field_your_political_views', 'field_your_political_views')
      ->defaultValue('')
      ->description(t('no description'));
    $this->addFieldMapping('field_your_religious_beliefs', 'field_your_religious_beliefs')
      ->defaultValue('')
      ->description(t('no description'));
      
      
      
      
    
    // Other handlers
    /* Delete this line, if you need the following:
    if (module_exists('path')) {
      $this->addFieldMapping('path')
           ->defaultValue(NULL)
           ->description(t('Path alias'));
    }
    /* */
    // some internal fields
    $this->addFieldMapping('revision_uid')
      ->defaultValue($user->uid)
      ->description(t('The user ID of the user, who started the migration'));
    $this->addFieldMapping('language')
      ->defaultValue(t('en'))
      ->description(t("The default language of the user (e.g. 'en', 'fr', 'de')"));
    // Unmapped fields (this fields are in core and not needed as profile2-fields)
    $this->addUnmigratedSources(array('mail', 'password'));
  }
  public function fixTimestamp($date) {
    // enable empty (= unknown) birthday-string:
    if (strlen($date) > 0) {
      $date = substr($date, 0, 10) . 'T12:00:00'; // we add 'twelve o'clock in the daytime' for automatic compensation of a website time zone difference to UTC
    }
    return $date;
  }
}
?>
