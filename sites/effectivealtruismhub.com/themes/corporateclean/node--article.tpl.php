<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>

  

  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  
  <div style="
    border-top: 1px solid #ccc; 
    margin-bottom: 2.5em;
">
</div>
  <div class="post-info" style="
    border-bottom: 1px solid #ccc;
    padding-bottom: 1.5em;
">
  	<?php print $user_picture;  ?>
  	<div class="submitted"><?php print "Post by $name on $date";?></div>
  	<div id="sharethis-share-buttons">
<span class='st_fblike_hcount' displayText='Facebook Like'></span>
<span class='st_facebook_hcount' displayText='Facebook'></span>
<span class='st_twitter_hcount' displayText='Tweet'></span>
<span class='st_linkedin_hcount' displayText='LinkedIn'></span>
<span class='st_email_hcount' displayText='Email'></span>	
  	</div>
  </div>


  <div class="content clearfix"<?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
    ?>
  </div>

  <div class="clearfix">
    <?php if (!empty($content['links'])): ?>
      <div class="links"><?php print render($content['links']); ?></div>
    <?php endif; ?>

    <?php print render($content['comments']); ?>
  </div>

</div>