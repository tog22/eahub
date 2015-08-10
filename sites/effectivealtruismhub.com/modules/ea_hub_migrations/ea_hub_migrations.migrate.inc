<?php

/**
 * @file
 * Because the name of this file is the module name plus '.migrate.inc', when
 * hook_migrate_api is invoked by the Migrate module this file is automatically
 * loaded - thus, you don't need to implement your hook in the .module file.
 */

/*
 * You must implement hook_migrate_api(), setting the API level to 2, if you are
 * implementing any migration classes. If your migration application is static -
 * that is, you know at implementation time exactly what migrations must be
 * instantiated - then you should register your migrations here. If your
 * application is more dynamic (for example, if selections in the UI determine
 * exactly what migrations need to be instantiated), then you would register
 * your migrations using registerMigration() - see migrate_example_baseball for
 * more information.
 */
function ea_hub_migrations_migrate_api() {
  // Usually field mappings are established by code in the migration constructor -
  // a call to addFieldMapping(). They may also be passed as arguments when
  // registering a migration - in this case, they are stored in the database
  // and override any mappings for the same field in the code. To do this,
  // construct the field mapping object and configure it similarly to when
  // you call addFieldMapping, and pass your mappings as an array below.
  $translate_mapping = new MigrateFieldMapping('translate', NULL);
  $translate_mapping->defaultValue(0);
  $ignore_mapping = new MigrateFieldMapping('migrate_example_beer_styles:ignore_case', NULL);
  $ignore_mapping->defaultValue(1);

  $api = array(
    // Required - tells the Migrate module that you are implementing version 2
    // of the Migrate API.
    'api' => 2,
    // Migrations can be organized into groups. The key used here will be the
    // machine name of the group, which can be used in Drush:
    //  drush migrate-import --group=wine
    // The title is a required argument which is displayed for the group in the
    // UI. You may also have additional arguments for any other data which is
    // common to all migrations in the group.
    'groups' => array(
      'ea_hub_migrations_group' => array(
        'title' => t('EA Hub Migrations'),
      ),
    ),

    // Here we register the individual migrations. The keys (BeerTerm, BeerUser,
    // etc.) are the machine names of the migrations, and the class_name
    // argument is required. The group_name is optional (defaulting to 'default')
    // but specifying it is a best practice.
    'migrations' => array(
      'EA_Group_Migration' => array(
        'class_name' => 'EA_Group_Migration',
        'group_name' => 'ea_hub_migrations_group',
        // Here is where we add field mappings which may override those
        // specified in the group constructor.
        'field_mappings' => array(
          $translate_mapping,
          $ignore_mapping,
        ),
      ),
    ),
  );
  return $api;
}



/**
 * To define a migration process from a set of source data to a particular
 * kind of Drupal object (for example, a specific node type), you define
 * a class derived from Migration. You must define a constructor to initialize
 * your migration object.
 *
 * For your classes to be instantiated so they can be used to import content,
 * you must register them - look at migrate_example.migrate.inc to see how
 * registration works. Right now, it's important to understand that each
 * migration will have a unique "machine name", which is displayed in the UI
 * and is used to reference the migration in drush commands.
 *
 * In any serious migration project, you will find there are some options
 * which are common to the individual migrations you're implementing. You can
 * define an abstract intermediate class derived from Migration, then derive your
 * individual migrations from that, to share settings, utility functions, etc.
 */
abstract class BasicExampleMigration extends Migration {
  // A Migration constructor takes an array of arguments as its first parameter.
  // The arguments must be passed through to the parent constructor.
  public function __construct($arguments) {
    parent::__construct($arguments);

    // With migrate_ui enabled, migration pages will indicate people involved in
    // the particular migration, with their role and contact info. We default the
    // list in the shared class; it can be overridden for specific migrations.
    $this->team = array(
      new MigrateTeamMember('Tom Ash', '',
                            t('Admin')),
    );
  }
}

/**
 * There are four essential components to set up in your constructor:
 *  $this->source - An instance of a class derived from MigrateSource, this
 *    will feed data to the migration.
 *  $this->destination - An instance of a class derived from MigrateDestination,
 *    this will receive data that originated from the source and has been mapped
 *    by the Migration class, and create Drupal objects.
 *  $this->map - An instance of a class derived from MigrateMap, this will keep
 *    track of which source items have been imported and what destination
 *    objects they map to.
 *  Field mappings - Use $this->addFieldMapping to tell the Migration class what
 *    source fields correspond to what destination fields, and additional
 *    information associated with the mappings.
 */
class EA_Group_Migration extends BasicExampleMigration {
  public function __construct($arguments) {
    parent::__construct($arguments);
    // Human-friendly description of your migration process. Be as detailed as
    // you like.
    $this->description =
      t('Migrate EA groups from the source database to Drupal');

	/***************************
	** EXAMPLE: SET UP SOURCE **
	****************************
	
    // In this example, we're using tables that have been added to the existing
    // Drupal database but which are not Drupal tables. You can examine the
    // various tables (starting here with migrate_example_beer_topic) using a
    // database browser such as phpMyAdmin.
    // First, we set up a query for this data. 
    $query = db_select('migrate_example_beer_topic', 'met')
             ->fields('met', array('style', 'details', 'style_parent', 'region',
                                   'hoppiness'));

    // Create a MigrateSource object, which manages retrieving the input data.
    $this->source = new MigrateSourceSQL($query);
	*/

	$columns = array(
	  // "Source": ('Fieldname', 'Description')
	  0 => array('Group name - migrate-defined name', t('Group name - migrate-defined name')),
	  1 => array('field_city', t('City')),
	  2 => array('field_country', t('Country')),
	  3 => array('Name of website', t('Name of website')),
	  4 => array('Website', t('Website'))
	);
	
	$this->source = new MigrateSourceCSV(DRUPAL_ROOT . '/' . drupal_get_path('module', 'ea_hub_migrations') . '/data_sources/import.csv', $columns, array('header_rows' => 1, 'delimiter' => ',', 'enclosure' => '"', 'track_changes' => 0));

    // Set up our destination - terms in the migrate_example_beer_styles
    // vocabulary (note that we pass the machine name of the vocabulary).
    $this->destination = new MigrateDestinationNode('group');

    // Create a map object for tracking the relationships between source rows
    // and their resulting Drupal objects. We will use the MigrateSQLMap class,
    // which uses database tables for tracking. Pass the machine name (BeerTerm)
    // of this migration to use in generating map and message table names.
    // And, pass schema definitions for the primary keys of the source and
    // destination - we need to be explicit for our source, but the destination
    // class knows its schema already.
	$this->map = new MigrateSQLMap($this->machineName,
	    array('Group name - migrate-defined name' => array( // tog: this field is the unique identifier, I think
	            'type' => 'varchar',
	            'length' => 255,
	            'not null' => TRUE,
	            'description' => t('Group name') // description never used
	          )
	         ),
	    MigrateDestinationUser::getKeySchema()
	);

    // Assign mappings TO destination fields FROM source fields. To discover
    // the names used in these calls, use the drush commands
    //  drush migrate-fields-destination BeerTerm
    //  drush migrate-fields-source BeerTerm
    // or review the detail pages in the UI.
    $this->addFieldMapping('title', 'Group name - migrate-defined name');
    $this->addFieldMapping('field_city', 'field_city');
    $this->addFieldMapping('field_country', 'field_country');
    $this->addFieldMapping('field_links', 'Website');
    $this->addFieldMapping('field_links:title', 'Name of website');
  }
  	
  	/* debugging:
  	public function prepare(stdClass $account, stdClass $row) {
		$node->title = 'This title should show on /admin/content'; 
		file_put_contents('/home1/sant0317/confidential-docroot/logs/groupmigr.log', print_r($row, TRUE));
	}
	*/
}


