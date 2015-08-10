<?php

/**
 * @file
 * Default theme implementation to display the basic html structure of a single
 * Drupal page.
 *
 * Variables:
 * - $css: An array of CSS files for the current page.
 * - $language: (object) The language the site is being displayed in.
 *   $language->language contains its textual representation.
 *   $language->dir contains the language direction. It will either be 'ltr' or 'rtl'.
 * - $rdf_namespaces: All the RDF namespace prefixes used in the HTML document.
 * - $grddl_profile: A GRDDL profile allowing agents to extract the RDF data.
 * - $head_title: A modified version of the page title, for use in the TITLE
 *   tag.
 * - $head_title_array: (array) An associative array containing the string parts
 *   that were used to generate the $head_title variable, already prepared to be
 *   output as TITLE tag. The key/value pairs may contain one or more of the
 *   following, depending on conditions:
 *   - title: The title of the current page, if any.
 *   - name: The name of the site.
 *   - slogan: The slogan of the site, if any, and if there is no title.
 * - $head: Markup for the HEAD section (including meta tags, keyword tags, and
 *   so on).
 * - $styles: Style tags necessary to import all CSS files for the page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 *   for the page.
 * - $page_top: Initial markup from any modules that have altered the
 *   page. This variable should always be output first, before all other dynamic
 *   content.
 * - $page: The rendered page content.
 * - $page_bottom: Final closing markup from any modules that have altered the
 *   page. This variable should always be output last, after all other dynamic
 *   content.
 * - $classes String of classes that can be used to style contextually through
 *   CSS.
 *
 * @see template_preprocess()
 * @see template_preprocess_html()
 * @see template_process()
 */
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML+RDFa 1.0//EN"
  "http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" version="XHTML+RDFa 1.0" dir="<?php print $language->dir; ?>"<?php print $rdf_namespaces; ?>>
<head profile="<?php print $grddl_profile; ?>">
	<?php print $head; ?>
    <?php 
  	//fetch node for later
  	$is_node = FALSE;
  	$node = FALSE;
  	if(arg(0) == 'node'  && is_numeric(arg(1))) {
  		$is_node = TRUE;
  		$node = node_load(arg(1));
  	}
  	?>
	<title><?php 
	if($is_node) {
		if ($node->nid == 2) {
			print 'Effective Altruism Hub';
		} else {
			print $head_title;
		}
	} else if (arg(0) == 'user'  && is_numeric(arg(1))) {
  		$account = user_load(arg(1));
  		print $account->name."'s Effective Altruist Profile";
  	} else {
		print $head_title;
	}
	?></title>  	
  <meta name="robots" content="noarchive">		<!-- tog addition: prevent caching of edited EA Profiles -->
  <?php 
  	// FB image
  	if($is_node) {
		if ($node->nid == 34 || $node->nid == 16) {
			print '<meta property="og:image" content="http://effectivealtruismhub.com/sites/effectivealtruismhub.com/media/images/specific-pages/eaprofiles-mosaic-fbsize-600x315.jpg" />';
		} else if ($node->nid == 35 || $node->nid == 7 || $node->nid == 8 || $node->nid == 9 || $node->nid == 28 || $node->nid == 32 || $node->nid == 37) {
			print '<meta property="og:image" content="http://effectivealtruismhub.com/sites/effectivealtruismhub.com/media/images/specific-pages/donations-piggy-bank-fb-size-white-borders.jpg" />';
		} else if ($node->nid == 40) {
			print '<meta property="og:image" content="http://effectivealtruismhub.com/sites/effectivealtruismhub.com/media/images/specific-pages/grim-reaper-for-will-guide.jpg" />';
		} else if ($node->nid == 2) {
			// URL not working - redo? print '<link rel="image_src" href="http://effectivealtruismhub.com/sites/effectivealtruismhub.com/files/color/corporateclean-7a227d2e/logo.png" />';
		} else if ($node->nid == 91) {
			print '<meta property="og:image" content="http://effectivealtruismhub.com/sites/effectivealtruismhub.com/media/images/specific-pages/groups-map-fb.png" />';
		} else if ($node->nid == 13) {
			print '<meta property="og:image" content="http://effectivealtruismhub.com/sites/effectivealtruismhub.com/media/images/specific-pages/map-central-area-screenshot-600x315.png" />';
		}
	}
	?>
  
	<!-- CSS -->
	<link href='http://fonts.googleapis.com/css?family=Roboto+Slab:700,400' rel='stylesheet' type='text/css'>
  	<?php print $styles; ?>

  
  <?php if (theme_get_setting('responsive_respond','corporateclean')) {
    global $base_path; 
    global $base_root; 
  ?>
<!--[if lt IE 9]>
  <script src="<?php print $base_root . $base_path . path_to_theme() ?>/js/respond.min.js"></script>
  <![endif]-->
  <?php } ?>
    
    <!-- JS -->
    <?php print $scripts; ?>
    <?php
    if($is_node) {
        // Donating (EA Action)
        if ($node->nid == 37) { 
            ?>
                  <!-- Add fancyBox -->
                  <link rel="stylesheet" href="/sites/all/libraries/fancyapps-fancyBox-18d1712/source/jquery.fancybox.css?v=2.1.5" type="text/css" media="screen" />
                  <script type="text/javascript" src="/sites/all/libraries/fancyapps-fancyBox-18d1712/source/jquery.fancybox.pack.js?v=2.1.5"></script>
            <?php
        } 
        /* yeilds errors, probably switch to arg() method including '&& arg(2) != 'edit':
        else if ($node->nid == 2 || $node->nid == 13 || $node->nid == 23 || $node->nid == 91) {
            ?>
            <link type="text/css" rel="stylesheet" href="http://cdn.leafletjs.com/leaflet-0.7.3/leaflet.css" media="all" />
<link type="text/css" rel="stylesheet" href="http://cdnjs.cloudflare.com/ajax/libs/leaflet.markercluster/0.4.0/MarkerCluster.Default.css" media="all" />

<!-- messes up:         
    <link type="text/css" rel="stylesheet" href="http://cdn.leafletjs.com/leaflet-0.7.3/leaflet.css" media="all" />
    <link href="http://maxcdn.bootstrapcdn.com/font-awesome/4.2.0/css/font-awesome.min.css" rel="stylesheet">
    <link href="http://cdnjs.cloudflare.com/ajax/libs/Leaflet.awesome-markers/2.0.0/leaflet.awesome-markers.css" rel="stylesheet">
    <script src="http://cdn.leafletjs.com/leaflet-0.7.3/leaflet.js"></script>
    <script src="http://cdnjs.cloudflare.com/ajax/libs/leaflet.markercluster/0.4.0/leaflet.markercluster.js"></script>
    <script src="http://cdnjs.cloudflare.com/ajax/libs/Leaflet.awesome-markers/2.0.0/leaflet.awesome-markers.js"></script>
-->
            <?
        }*/
    }
  ?>
  <script type="text/javascript">var switchTo5x=true;</script>
<script type="text/javascript" src="http://w.sharethis.com/button/buttons.js"></script>
<script type="text/javascript">stLight.options({publisher: "4e72a5f6-559e-41ed-90db-cb3b76d08015", doNotHash: true, doNotCopy: true, hashAddressBar: false});</script>

</head>
<body class="<?php print $classes; ?>" <?php print $attributes;?>>
  <div id="skip-link">
    <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
  </div>
  <div id="fb-root"></div>
<script>(function(d, s, id) {
  var js, fjs = d.getElementsByTagName(s)[0];
  if (d.getElementById(id)) return;
  js = d.createElement(s); js.id = id;
  js.src = "//connect.facebook.net/en_GB/sdk.js#xfbml=1&appId=285795838275703&version=v2.0";
  fjs.parentNode.insertBefore(js, fjs);
}(document, 'script', 'facebook-jssdk'));</script>
  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $page_bottom; ?>
</body>
</html>

