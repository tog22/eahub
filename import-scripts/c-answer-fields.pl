#!/usr/bin/perl

use Text::CSV;
use Data::Dumper;
use warnings;
no warnings 'uninitialized'; # can be fine - not totally sure fine here though

# OUTPUT, gets written to file
my $csvoutput;
$csvoutput =
"`member_nr`}`email`}`username`}`password`}`2013total`}`2013income`}`2013charities`}`lifetime-donations`}`plan-text`}`plan-causes`}`plan-until`}`plan-extra`}`rawtext`}`field_weighting`}`field_has_profile_data`}`field_what_moral_philosophy_do_y`}`field_which_of_the_following_cau`}`field_please_list_any_actions_yo`}`field_roughly_how_many_hours_a_m`}`field_what_is_your_diet_`}`field_do_you_identify_with_any_o`}`field_in_which_year_did_you_firs`}`field_how_first_heard_about_ea`}`field_which_factors_were_importa`}`field_which_of_the_following_gro`}`field_have_you_volunteered`}`field_roughly_how_many_of_your_f`}`field_what_career_path_do_you_pl`}`field_how_confident_are_you_that`}`field_your_age`}`field_your_gender`}`field_full_time_student`}`field_what_is_the_highest_level_`}`field_in_which_country_do_you_li`}`field_in_which_city_do_you_live_`}`field_your_political_views`}`field_your_religious_beliefs`\n";

# get list of old MIDs to assign to people
my $old_mids_csv = Text::CSV->new(
    { binary => 1, escape_char => "\\", sep_char => '}', quote_char => '`' }
  )    # should set binary attribute.
  or die "Cannot use CSV: " . Text::CSV->error_diag();

open my $old_mids_file, "<:encoding(utf8)", "old-mids.csv" or die "$!";

my %mids_in_remote_import;
my $ignored_header_line = $old_mids_csv->getline($old_mids_file);

while ( my $row = $old_mids_csv->getline($old_mids_file) ) {
    $mids_in_remote_import{ $row->[1] } = $row->[0];  # key = email; value = mid
    $mids_in_remote_import{ $row->[0] } = $row->[1];    # vice versa, for assigning fresh mids
    # weighting (key = {$email}{"weighting"})
    $mids_in_remote_import{ $row->[1] }{ "weighting" } = $row->[13];
 	# ADD WEIGHTING
    #add old row - safe to not add questions answers, after weighting & has profile data, as these'll get picked up in the next while loop
    
    ## here, i was making the whole row available in the next loop, but not i'm printing it here, so i won't update this with new columns
    $mids_in_remote_import{ $row->[0] }{"whole_row"} = '`'
      . $row->[0] . '`}`'
      . $row->[1] . '`}`'
      . $row->[2] . '`}`'
      . $row->[3] . '`}`'
      . $row->[4] . '`}`'
      . $row->[5] . '`}`'
      . $row->[6] . '`}`'
      . $row->[7] . '`}`'
      . $row->[8] . '`}`'
      . $row->[9] . '`}`'
      . $row->[10] . '`}`'
      . $row->[11] . '`}`'
      . $row->[12] . '`}`'
      . $row->[13] . '`}`'
      . $row->[14] . '`' . "\n";
    
    ### when i was using this, I did:
    #test tues 6th pm

    #foreach ( keys %mids_in_remote_import ) {
    #    if ( !$mids_to_catch_missed_ones{"$_"} ) {
    #        $csvoutput .= $mids_in_remote_import{"$_"}{"whole_row"};
    #    }
    #}
    
    
    ## print row - best option
    #debug
    print "Outputting old row for ".$row->[1]."\n$row->[20]\n";
    my $row_to_print;
    for (@{$row}) {
    	$row_to_print .= "`$_`}";
    	
    }
    $row_to_print =~ s/}$/\n/;
    $csvoutput .= $row_to_print;
    
    # debugging
    #print $mids_in_remote_import{ $row->[0] }{"whole_row"};
}

# Close old CSV;
$old_mids_csv->eof or $old_mids_csv->error_diag();
close $old_mids_file;
print "\n\nErrors below are in the new CSV\n\n";

# go through CSV with data to import
my $csv = Text::CSV->new(
    { binary => 1, sep_char => '}', quote_char => '`'  } )    # should set binary attribute.
  or die "Cannot use CSV: " . Text::CSV->error_diag();

open my $fh, "<:encoding(utf8)", "SOURCE.csv" or die "$!";

# HEADERS: IGNORE IN SOURCE, ADD TO OUTPUT
$ignored_header_line = $csv->getline($fh);

my $_member_nr = 1001;
my $pw         = 394235;

my %mids_to_catch_missed_ones;
my %duplicate_emails;

while ( my $row = $csv->getline($fh) ) {
    #debug
    #print "\n==New row==\n";
    
    # get email
	my $email = $row->[69];
	if ($row->[69] =~ /@/) {
	
	} else {
		if ($row->[118] =~ /@/) {
			$email = $row->[118];
			#print "row69 has no email - so using following from row118\n$email\n";
		}
	}
    #debugging
    #print "$email \n";

    ### Should we skip this line?
   	
   	##### Skip line if no email given
    if ( $email =~ /@/ ) {
    } else {
        next;
    }
    
    ##### Skip line if already in file
    if ( exists $mids_in_remote_import{$email} ) {
    	#debug
    	print "NOTICE: email already in old-mids ($email)\n";
    	next;
    }
    
    
    ##### Skip line if email already outputted
    if ($duplicate_emails{$email}) {
    	print "NOTICE: Not outputting duplicate email $email\n";
    	next;
    }
    ###### Flag email for next time we check the above
    $duplicate_emails{$email} = 1;

    ########
    # FIELD:
    # mid

    my $member_nr = 'unset';
    if ( !$mids_in_remote_import{$email} ) {
        while ( $mids_in_remote_import{$_member_nr} ) {
            $_member_nr++;
        }
        $mids_in_remote_import{$_member_nr} = $email;
        $member_nr = $_member_nr;
    }
    else {
        $member_nr = $mids_in_remote_import{$email};
    }

# record that this mid outputted to the csv, so we can add the mids not outputted back to the csv, pasting in their exact rows from old-mids.csv
    $mids_to_catch_missed_ones{"$member_nr"} = 1;    #try same with email

    ########
    # FIELD:
    # username if no name given
    my $username;
    if ( $row->[68] eq '' ) {
        $username = $email;
        $username =~ s/(.*)?@.*/$1/;
    }
    else {
        $username = $row->[68];
    }

    ########
    # FIELD:
    # Until when
    my $planUntil;
    if ( $row->[97] eq 'Other' ) {
        $planUntil = $row->[98];
    }
    else {
        $planUntil = $row->[97];
    }

    ########
    # FIELD:
    # 2013charities

    #prep concatenated cells
    my $v2013charities = '';
    if ( $row->[73] eq 'Yes' ) {
        $v2013charities .= '80,000 Hours^';
    }
    if ( $row->[74] eq 'Yes' ) {
        $v2013charities .= 'Against Malaria Foundation^';
    }
    if ( $row->[75] eq 'Yes' ) {
        $v2013charities .= 'Animal Charity Evaluators^';
    }
    if ( $row->[76] eq 'Yes' ) {
        $v2013charities .=
          'The Centre for Effective Altruism (unrestricted donation)^';
    }
    if ( $row->[77] eq 'Yes' ) {
        $v2013charities .= 'Center For Applied Rationality^';
    }
    if ( $row->[78] eq 'Yes' ) {
        $v2013charities .= 'Deworm the World^';
    }
    if ( $row->[79] eq 'Yes' ) {
        $v2013charities .= 'GiveDirectly^';
    }
    if ( $row->[80] eq 'Yes' ) {
        $v2013charities .= 'GiveWell (itself)^';
    }
    if ( $row->[81] eq 'Yes' ) {
        $v2013charities .= 'Giving What We Can (itself)^';
    }
    if ( $row->[82] eq 'Yes' ) {
        $v2013charities .= 'The Humane League^';
    }
    if ( $row->[83] eq 'Yes' ) {
        $v2013charities .= 'Leverage Research^';
    }
    if ( $row->[84] eq 'Yes' ) {
        $v2013charities .= 'Machine Intelligence Research Institute^';
    }
    if ( $row->[85] eq 'Yes' ) {
        $v2013charities .= 'Project Healthy Children^';
    }
    if ( $row->[86] eq 'Yes' ) {
        $v2013charities .= 'Schistosomiasis Control Initiative (SCI)^';
    }
    if ( $row->[87] eq 'Yes' ) {
        $v2013charities .= 'Vegan Outreach^';
    }

    #add Other
    $v2013charities .= $row->[88];

    #remove final ;
    $v2013charities =~ s/^$//;

    ########
    # FIELD:
    # plan causes
    my $planCauses = '';
    if ( $row->[92] eq 'Yes' ) {
        $planCauses .= 'Animal welfare^';
    }
    if ( $row->[93] eq 'Yes' ) {
        $planCauses .= 'Existential risk alleviation^';
    }
    if ( $row->[94] eq 'Yes' ) {
        $planCauses .=
          'Far future causes other than existential risk alleviation^';
    }
    if ( $row->[95] eq 'Yes' ) {
        $planCauses .= 'Global poverty^';
    }

    #add Other
    $planCauses .= $row->[96];

    #remove final ;
    $planCauses =~ s/^$//;
    
    # Print line
    if ( $row->[90] eq 'Yes' || $row->[100] eq 'Yes' || $row->[120] eq 'Yes' ) {
		#debug
		#print "some donations present\n";
        ## basics
        $csvoutput .= '`'
          . $member_nr . '`}`'
          . $email . '`}`'
          . $username . '`}`'
          . $pw;
        ## past donations
        if ( $row->[90] eq 'Yes'
            || ( $row->[90] eq 'N/A' && $row->[120] eq 'Yes' ) )
        {
            $csvoutput .= '`}`'
              . $row->[71] . '`}`' . '' . '`}`'
              . $v2013charities . '`}`'
              . $row->[89];
        }
        else {
            $csvoutput .= '`}``}``}``}`';
        }
        ## planned donations
        if ( $row->[100] eq 'Yes'
            || ( $row->[100] eq 'N/A' && $row->[120] eq 'Yes' ) )
        {
            $csvoutput .= '`}`'
              . $row->[91] . '`}`'
              . $planCauses . '`}`'
              . $planUntil . '`}`'
              . $row->[99] . '`}';
        }
        else {
            $csvoutput .= '`}``}``}``}``}';
        }
        ############
        ############
        ############
        ############
        ## all survey answers
        
        # raw text deliberately blank as fields replace it
        $csvoutput .= '``}';
        
        # HIDDEN FIELDSET: weighting
        # setting preset weighting from mids csv
        if (!$mids_in_remote_import{$email}{"weighting"}) {
        	$csvoutput .= '`500`}';
        } else {
        	$csvoutput .= '`'.$mids_in_remote_import{$email}{"weighting"}.'`}';
        }
        
        if ( $email eq 'singerp@gmail.com' || $email eq 'Jim@GreenbaumFoundation.org' ) {
        	$csvoutput .= '`1`}'; # show in profiles list, but don't add answers
        }


        if ( $row->[120] eq 'Yes' ) {
        	#debug 
        	#print "answers public\n";
            
            # HIDDEN FIELDSET: answers public
            $csvoutput .= '`1`}';
            
            my $output = '';
            if ( $row->[11] eq '' ) {
                $csvoutput .= '``}';
            }
            elsif ( $row->[11] eq 'Other' ) {

                # What moral philosophy do you subscribe to, if any?
                $csvoutput .= '`' . $row->[12] . '`}';
            }
            else {
                # What moral philosophy do you subscribe to, if any?
                $csvoutput .= '`' . $row->[11] . '`}';
            }

            if ( $row->[13] eq 'N/A' ) {
                $csvoutput .= '``}';
            }
            else {
                my $answer = '';
                if ( $row->[13] eq 'Yes' ) {
                    $answer .= 'Global poverty^';
                }

                if ( $row->[14] eq 'Yes' ) {
                    $answer .= 'Environmentalism^';
                }

                if ( $row->[15] eq 'Yes' ) {
                    $answer .= 'Animal welfare^';
                }

                if ( $row->[16] eq 'Yes' ) {
                    $answer .= 'Improving rationality or science^';
                }

                if ( $row->[17] eq 'Yes' ) {
                    $answer .= 'Political reform^';
                }

                if ( $row->[18] eq 'Yes' ) {
                    $answer .= 'Existential risk (artificial intelligence)^';
                }

                if ( $row->[19] eq 'Yes' ) {
                    $answer .= 'Existential risk (other)^';
                }

                if ( $row->[20] eq 'Yes' ) {
                    $answer .=
                      'Far future concerns (besides existential risk)^';
                }

                if ( $row->[21] eq 'Yes' ) {
                    $answer .= 'Cause prioritization^';
                }

                if ( $row->[22] eq 'Yes' ) {
                    $answer .=
                      'Meta charities which direct resources to these causes^';
                }

                if ( $row->[23] eq 'Yes' ) {
                    $answer .= 'No opinion^';
                }
                $answer .= $row->[24];
                $answer =~ s/\^$//;

    # Which of the following causes do you think you should devote resources to?
                $csvoutput .= '`' . $answer . '`}';
            }

            if ( $row->[25] eq '' ) {
                $csvoutput .= '``}';
            }
            else {
                # Please list any actions you are taking to support these causes
                $csvoutput .= '`' . $row->[25] . '`}';
            }

            if ( $row->[26] eq '' ) {
                $csvoutput .= '``}';
            }
            else {
              # Roughly how many hours a month do you spend on these activities?
                $csvoutput .= '`' . $row->[26] . '`}';
            }

            if ( $row->[27] eq '' ) {
                $csvoutput .= '``}';
            }
            elsif ( $row->[27] eq 'Other' ) {

                # What is your diet?
                $csvoutput .= '`' . $row->[28] . '`}';    # +1 row
            }
            else {
                # What is your diet?
                $csvoutput .= '`' . $row->[27] . '`}';
            }

            if ( $row->[29] eq 'N/A' ) {
                $csvoutput .= '``}';
            }
            else {
                my $answer = '';
                if ( $row->[29] eq 'Yes' ) {
                    $answer .= 'Animal rights^';
                }

                if ( $row->[30] eq 'Yes' ) {
                    $answer .= 'Environmentalist^';
                }

                if ( $row->[31] eq 'Yes' ) {
                    $answer .= 'Feminist^';
                }

                if ( $row->[32] eq 'Yes' ) {
                    $answer .= 'LGBTQ^';
                }

                if ( $row->[33] eq 'Yes' ) {
                    $answer .= 'Rationalist/LessWrong^';
                }

                if ( $row->[34] eq 'Yes' ) {
                    $answer .= 'Transhumanist^';
                }

                if ( $row->[35] eq 'Yes' ) {
                    $answer .= 'Skeptic/atheist^';
                }

                $answer .= $row->[36];    # other option
                $answer =~ s/\^$//;

                # Do you identify with any other social movements?
                $csvoutput .= '`' . $answer . '`}';
            }

            if ( $row->[38] eq '' ) {
                $csvoutput .= '``}';
            }
            else {
             # In which year did you first hear the term \'Effective Altruism\'?
                $csvoutput .= '`' . $row->[38] . '`}';
            }

            if ( $row->[39] eq '' ) {
                $csvoutput .= '``}';
            }
            elsif ( $row->[39] eq 'Other' ) {

                # How did you first hear about \'Effective Altruism\'?
                $csvoutput .= '`' . $row->[40] . '`}';    # +1 row
            }
            else {
                # How did you first hear about \'Effective Altruism\'?
                $csvoutput .= '`' . $row->[39] . '`}';
            }

            if ( $row->[41] eq 'N/A' ) {
                $csvoutput .= '``}';
            }
            else {
                my $answer = '';
                if ( $row->[41] eq 'Yes' ) {
                    $answer .= 'Personal contact with an EA or EAs^';
                }

                if ( $row->[42] eq 'Yes' ) {
                    $answer .= '80,000 Hours^';
                }

                if ( $row->[43] eq 'Yes' ) {
                    $answer .= 'The Life You Can Save^';
                }

                if ( $row->[44] eq 'Yes' ) {
                    $answer .= 'LessWrong^';
                }

                if ( $row->[45] eq 'Yes' ) {
                    $answer .= 'Giving What We Can^';
                }

                if ( $row->[46] eq 'Yes' ) {
                    $answer .= 'GiveWell^';
                }

                if ( $row->[47] eq 'Yes' ) {
                    $answer .= 'Friends^';
                }

                if ( $row->[48] eq 'Yes' ) {
                    $answer .= 'The online EA community^';
                }

                if ( $row->[49] eq 'Yes' ) {
                    $answer .= 'Local chapter of an EA organisation^';
                }

                $answer .= $row->[50];    # other option
                $answer =~ s/\^$//;

# Which factors were important in \'getting you into\' Effective Altruism, or altering your actions in its direction?
                $csvoutput .= '`' . $answer . '`}';
            }

            if ( $row->[51] eq 'N/A' ) {
                $csvoutput .= '``}';
            }
            else {
                my $answer = '';
                if ( $row->[51] eq 'Yes' ) {
                    $answer .= 'The \'Effective Altruists\' Facebook group^';
                }

                if ( $row->[52] eq 'Yes' ) {
                    $answer .=
                      'Giving What We Can (you\'ve taken the pledge)^';
                }

                if ( $row->[53] eq 'Yes' ) {
                    $answer .= 'LessWrong^';
                }

                if ( $row->[54] eq 'Yes' ) {
                    $answer .=
                      'The Life You Can Save (you\'ve taken the pledge)^';
                }

                if ( $row->[55] eq 'Yes' ) {
                    $answer .= 'Local EA group^';
                }

                $answer .= $row->[56];    # other option
                $answer =~ s/\^$//;

                # Which of the following groups are you a member of, if any?
                $csvoutput .= '`' . $answer . '`}';
            }

            if ( $row->[57] eq 'N/A' ) {
                $csvoutput .= '``}';
            }
            else {
                my $answer = '';
                if ( $row->[57] eq 'Yes' ) {
                    $answer .= '80,000 Hours^';
                }

                if ( $row->[58] eq 'Yes' ) {
                    $answer .=
'Animal Charity Evaluators (formerly Effective Animal Activism)^';
                }

                if ( $row->[59] eq 'Yes' ) {
                    $answer .= 'Center For Applied Rationality^';
                }

                if ( $row->[60] eq 'Yes' ) {
                    $answer .= 'GiveWell^';
                }

                if ( $row->[61] eq 'Yes' ) {
                    $answer .= 'Giving What We Can^';
                }

                if ( $row->[62] eq 'Yes' ) {
                    $answer .= 'Leverage Research^';
                }

                if ( $row->[63] eq 'Yes' ) {
                    $answer .= 'The Life You Can Save^';
                }

                if ( $row->[64] eq 'Yes' ) {
                    $answer .= 'Machine Intelligence Research Institute^';
                }

                $answer .= $row->[65];    # other option
                $answer =~ s/\^$//;

        # Have you volunteered or worked for any of the following organisations?
                $csvoutput .= '`' . $answer . '`}';
            }

            if ( $row->[66] eq '' ) {
                $csvoutput .= '``}';
            }
            else {
# Roughly how many of your friends would describe themselves as Effective Altruists?
                $csvoutput .= '`' . $row->[66] . '`}';
            }

            # between 67 and 101 is donations stuff already done

            if ( $row->[102] eq '' ) {
                $csvoutput .= '``}';
            }
            elsif ( $row->[102] eq 'Other' ) {

                # What career path do you plan to follow?
                $csvoutput .= '`' . $row->[103] . '`}';    # +1 row
            }
            else {
                # What career path do you plan to follow?
                $csvoutput .= '`' . $row->[102] . '`}';
            }

            if ( $row->[104] eq '' ) {
                $csvoutput .= '``}';
            }
            else {
                # How confident are you that you will take this career path?
                $csvoutput .= '`' . $row->[104] . '`}';
            }

            if ( $row->[106] eq '' ) {
                $csvoutput .= '``}';
            }
            else {
                # Your age
                $csvoutput .= '`' . $row->[106] . '`}';
            }

            if ( $row->[107] eq '' ) {
                $csvoutput .= '``}';
            }
            elsif ( $row->[107] eq 'Other' ) {

                # Your gender
                $csvoutput .= '`' . $row->[108] . '`}';    # +1 row
            }
            else {
                # Your gender
                $csvoutput .= '`' . $row->[107] . '`}';
            }

            if ( $row->[109] eq '' ) {
                $csvoutput .= '``}';
            }
            else {
                # Are you a full-time student?
                $csvoutput .= '`' . $row->[109] . '`}';
            }
            
            if ( $row->[109] eq '' ) {
                $csvoutput .= '``}';
            }
            else {
                # field_what_is_the_highest_level_
                $csvoutput .= '`' . $row->[110] . '`}';
            }

            if ( $row->[111] eq '' ) {
                $csvoutput .= '``}';
            }
            else {
                # In which country do you live?
                $csvoutput .= '`' . $row->[111] . '`}';
            }

            if ( $row->[112] eq '' ) {
                $csvoutput .= '``}';
            }
            else {
                # In which city do you live?
                $csvoutput .= '`' . $row->[112] . '`}';
            }

            if ( $row->[114] eq '' ) {
                $csvoutput .= '``}';
            }
            else {
                # Your political views
                $csvoutput .= '`' . $row->[114] . '`}';
            }

            if ( $row->[115] eq '' ) {
                $csvoutput .= '``}';
            }
            elsif ( $row->[115] eq 'Other' ) {

                # Your religious beliefs
                $csvoutput .= '`' . $row->[116] . '`}';    # +1 row
            }
            else {
                # Your religious beliefs
                $csvoutput .= '`' . $row->[115] . '`}';
            }
        }

        #newline, whether answers public or not
        $csvoutput .= "\n";

        # up id and pw
        $member_nr = $member_nr + 1;
        $pw        = $pw + 1;
    }

}

# Close old CSV;
$csv->eof or $csv->error_diag();
close $fh;

# Final corrections
$csvoutput =~ s/\\'/'/g;
# Save to new CSV
#print "\n\n=== SAVING OUTPUT TO FILE ===\n\n";
#print $csvoutput;
open NEWCSV, ">", "RESULT-c-answer-fields.csv";
print NEWCSV $csvoutput;
close NEWCSV;