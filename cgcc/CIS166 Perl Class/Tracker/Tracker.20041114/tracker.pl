#!/usr/bin/perl -w
# tracker.pl
# Written By: Chris Tjon
# Time Tracking System for Problem Calls
# 15 Oct 2004
#
#use strict;
use DBI;

my $database = 'tracker_db';
my $db_host = 'localhost';
my $db_port = '3306';
my $db_user = 'tracker_user';
my $db_passwd = 'password';
my $debug_flag = 1;


&debug("*******************************************************************************");
#&test_user_table_functions;
#&test_event_name_table_functions;
&test_time_record_table_functions;

sub test_event_name_table_functions
###############################################################################
# TEST_EVENT_NAME_TABLE_FUNCTIONS:                                            #
# REQUIRES:                                                                   #
# MODIFIES:                                                                   #
# EFFECTS:                                                                    #
# RETURNS:                                                                    #
###############################################################################
{
	&truncate_event_name_table;
	&dump_event_name_table;
	&add_event("DWT Outage");
	&add_event("SEntry Problem");
	&add_event("Host Fallback");
	&add_event("SIM DOWN");
	&add_event("MARS TIR");
	&dump_event_name_table;
	&change_event_name("SENTry Problem", "LSPA FAilure");
	&dump_event_name_table;
	&delete_event("SIM DOWN");
	&dump_event_name_table;
	&delete_event("NONEXIST");
	&dump_event_name_table;
}

sub test_time_record_table_functions
###############################################################################
# TEST_TIME_RECORD_TABLE_FUNCTIONS:                                           #
# REQUIRES:                                                                   #
# MODIFIES:                                                                   #
# EFFECTS:                                                                    #
# RETURNS:                                                                    #
###############################################################################
{
	&truncate_time_record_table;
	&dump_time_record_table;
	&add_time_record("LSPA Outage", "chris", "DS", "2004-10-15", "2", "TL");
	&dump_time_record_table;
	&add_time_record("LSPB Outage", "scott", "DS", "2004-10-15", "2", "TL");
	&dump_time_record_table;
#	&change_time_record("LSPA Outage", "chris", "DS", "2004-10-15", "2", "TL");
#	&dump_time_record_table;
	&delete_time_record("LSPA Outage", "chris", "DS", "2004-10-15", "2", "TL");
	&dump_time_record_table;
}

sub test_user_table_functions
###############################################################################
# TEST_USER_TABLE_FUNCTIONS:                                                  #
# REQUIRES:                                                                   #
# MODIFIES:                                                                   #
# EFFECTS:                                                                    #
# RETURNS:                                                                    #
###############################################################################
{
	&truncate_user_table;
	&dump_user_table;
	&add_user("JB");
	&add_user("Scott");
	&add_user("CHRIS");
	&add_user("Mary");
	&add_user("JOHN");
	&add_user("Keith");
	&add_user("Rob");
	&add_user("Tim");
	&add_user("Daryl");
	&dump_user_table;
	&change_user_name("JB", "Johnathan");
	&dump_user_table;
	&delete_user("Daryl");
	&dump_user_table;
	&delete_user("NOONE");
	&dump_user_table;
}

sub add_time_record # (char $event_name, $user_name, $prob_space, $event_date, $duration, $event_type)
###############################################################################
# ADD_TIME_RECORD:                                                            #
# REQUIRES:                                                                   #
# MODIFIES:                                                                   #
# EFFECTS:                                                                    #
# RETURNS:                                                                    #
###############################################################################
{
	my $db_handle; 
	my $sql_buf;
	my $event_name = $_[0];
	my $user_name = $_[1];
	my $prob_space = $_[2];
	my $event_date = $_[3];
	my $duration = $_[4];
	my $event_type = $_[5];

	&debug("add_time_record: adding [$event_name,$user_name,$prob_space,$event_date,$duration,$event_type] to time_record_table");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });
	my $sql_fmt = "INSERT INTO time_record_table VALUES(UPPER('%s'), UPPER('%s'), UPPER('%s'), %s, %d, UPPER('%s'));";
	$sql_buf = sprintf($sql_fmt, $event_name, $user_name, $prob_space, $event_date, $duration, $event_type);
	&debug("add_time_record: \$sql_buf = [$sql_buf]");
	$db_handle->do($sql_buf);
	$db_handle->disconnect;
	&debug("add_time_record: added [$event_name,$user_name,$prob_space,$event_date,$duration,$event_type] to time_record_table");
}

sub change_time_record # (char $event_name, $user_name, $prob_space, $event_date, $duration, $event_type)
###############################################################################
# CHANGE_TIME_RECORD:                                                         #
# REQUIRES:                                                                   #
# MODIFIES:                                                                   #
# EFFECTS:                                                                    #
# RETURNS:                                                                    #
###############################################################################
{
	my $db_handle; 
	my $sql_buf;
	my $event_name = $_[0];
	my $user_name = $_[1];
	my $prob_space = $_[2];
	my $event_date = $_[3];
	my $duration = $_[4];
	my $event_type = $_[5];

	&debug("change_time_record: updating [$event_name,$user_name,$prob_space,$event_date,$duration,$event_type] in time_record_table");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });
	my $sql_fmt = "UPDATE time_record_table SET event_name = UPPER('%s'), user_name = UPPER('%s'), prob_space = UPPER('%s') event_date =  %s, duration = %d, event_type = UPPER('%s');";
	$sql_buf = sprintf($sql_fmt, $event_name, $user_name, $prob_space, $event_date, $duration, $event_type);
	&debug("change_time_record: \$sql_buf = [$sql_buf]");
	$db_handle->do($sql_buf);
	$db_handle->disconnect;
	&debug("change_time_record: updated [$event_name,$user_name,$prob_space,$event_date,$duration,$event_type] in time_record_table");
}

sub delete_time_record # (char $event_name, $user_name, $prob_space, $event_date, $duration, $event_type)
###############################################################################
# DELETE_TIME_RECORD:                                                         #
# REQUIRES:                                                                   #
# MODIFIES:                                                                   #
# EFFECTS:                                                                    #
# RETURNS:                                                                    #
###############################################################################
{
	my $db_handle; 
	my $sql_buf;
	my $event_name = $_[0];
	my $user_name = $_[1];
	my $prob_space = $_[2];
	my $event_date = $_[3];
	my $duration = $_[4];
	my $event_type = $_[5];

	&debug("delete_time_record: deleting [$event_name,$user_name,$prob_space,$event_date,$duration,$event_type] from time_record_table");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });
	my $sql_fmt = "DELETE FROM time_record_table WHERE event_name = UPPER('%s'), user = UPPER('%s'), problem_space = UPPER('%s'), event_date = '%s', duration = '%d', event_type = UPPER('%s');";
	$sql_buf = sprintf($sql_fmt, $event_name, $user_name, $prob_space, $event_date, $duration, $event_type);
	&debug("delete_time_record: \$sql_buf = [$sql_buf]");
	$db_handle->do($sql_buf);
	$db_handle->disconnect;
	&debug("delete_time_record: deleted [$event_name,$user_name,$prob_space,$event_date,$duration,$event_type] from time_record_table");
}

sub add_event # (char $event_name)
###############################################################################
# ADD_EVENT:                                                                  #
# REQUIRES:                                                                   #
# MODIFIES:                                                                   #
# EFFECTS:                                                                    #
# RETURNS:                                                                    #
###############################################################################
{
	my $db_handle; 
	my $sql_buf;
	my $event_name = $_[0];

	&debug("add_event: adding [$event_name] to event_name_table");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });
	my $sql_fmt = ("INSERT INTO event_name_table VALUES(UPPER('%s'));");
	$sql_buf = sprintf($sql_fmt, $event_name);
	&debug("add_event: \$sql_buf = [$sql_buf]");
	$db_handle->do($sql_buf);
	&debug("add_event: added [$event_name] to event_name_table");
	$db_handle->disconnect;
}

sub change_event_name # (char $old_event_name, char $new_event_name)
###############################################################################
# CHANGE_EVENT_NAME:                                                          #
# REQUIRES:                                                                   #
# MODIFIES:                                                                   #
# EFFECTS:                                                                    #
# RETURNS:                                                                    #
###############################################################################
{
	my $db_handle; 
	my $sql_buf;
	my $old_event_name = $_[0];
	my $new_event_name = $_[1];

	&debug("change_event_name: changing [$old_event_name] to [$new_event_name] in event_name_table");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });
	my $sql_fmt = ("UPDATE event_name_table SET event_name = UPPER('%s') WHERE event_name = UPPER('%s');");
	$sql_buf = sprintf($sql_fmt, $new_event_name, $old_event_name);
	&debug("change_event_name: \$sql_buf = [$sql_buf]");
	$db_handle->do($sql_buf);
	&debug("change_event_name: changed [$old_event_name] to [$new_event_name] in event_name_table");
	$db_handle->disconnect;
}

sub delete_event # (char $event_name)
###############################################################################
# DELETE_EVENT:                                                               #
# REQUIRES:                                                                   #
# MODIFIES:                                                                   #
# EFFECTS:                                                                    #
# RETURNS:                                                                    #
###############################################################################
{
	my $db_handle; 
	my $sql_buf;
	my $event_name = $_[0];

	&debug("delete_event: deleting [$event_name] from event_name_table");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });
	my $sql_fmt = ("DELETE FROM event_name_table WHERE event_name = UPPER('%s');");
	$sql_buf = sprintf($sql_fmt, $event_name);
	&debug("delete_event: \$sql_buf = [$sql_buf]");
	$db_handle->do($sql_buf);
	$db_handle->disconnect;
	&debug("delete_event: deleted [$event_name] from event_name_table");
}

sub add_user # (char $user_name)
###############################################################################
# ADD_USER:                                                                   #
# REQUIRES:                                                                   #
# MODIFIES:                                                                   #
# EFFECTS:                                                                    #
# RETURNS:                                                                    #
###############################################################################
{
	my $db_handle; 
	my $sql_buf;
	my $user_name = $_[0];

	&debug("add_user: adding [$user_name] to user_table");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });
	my $sql_fmt = ("INSERT INTO user_table VALUES(UPPER('%s'));");
	$sql_buf = sprintf($sql_fmt, $user_name);
	&debug("add_user: \$sql_buf = [$sql_buf]");
	$db_handle->do($sql_buf);
	&debug("add_user: added [$user_name] to user_table");
	$db_handle->disconnect;
}

sub change_user_name # (char $old_user_name, char $new_user_name)
###############################################################################
# CHANGE_USER_NAME:                                                           #
# REQUIRES:                                                                   #
# MODIFIES:                                                                   #
# EFFECTS:                                                                    #
# RETURNS:                                                                    #
###############################################################################
{
	my $db_handle; 
	my $sql_buf;
	my $old_user_name = $_[0];
	my $new_user_name = $_[1];

	&debug("change_user_name: changing [$old_user_name] to [$new_user_name] in user_table");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });
	my $sql_fmt = ("UPDATE user_table SET user = UPPER('%s') WHERE user = UPPER('%s');");
	$sql_buf = sprintf($sql_fmt, $new_user_name, $old_user_name);
	&debug("change_user_name: \$sql_buf = [$sql_buf]");
	$db_handle->do($sql_buf);
	&debug("change_user_name: changed [$old_user_name] to [$new_user_name] in user_table");
	$db_handle->disconnect;
}

sub delete_user # (char $user_name)
###############################################################################
# DELETE_USER:                                                                #
# REQUIRES:                                                                   #
# MODIFIES:                                                                   #
# EFFECTS:                                                                    #
# RETURNS:                                                                    #
###############################################################################
{
	my $db_handle; 
	my $sql_buf;
	my $user_name = $_[0];

	&debug("delete_user: deleting [$user_name] from user_table");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });
	my $sql_fmt = ("DELETE FROM user_table WHERE user = UPPER('%s');");
	$sql_buf = sprintf($sql_fmt, $user_name);
	&debug("delete_user: \$sql_buf = [$sql_buf]");
	$db_handle->do($sql_buf);
	$db_handle->disconnect;
	&debug("delete_user: deleted [$user_name] from user_table");
}

sub dump_event_name_table
###############################################################################
# DUMP_EVENT_TABLE: dumps the contents of the event table to stdout for view  #
# REQUIRES: event_name_table exists                                           #
# MODIFIES: nothing                                                           #
# EFFECTS: nothing                                                            #
# RETURNS: nothing                                                            #
###############################################################################
{
	my $db_handle; 
	my $sql_buf;
	my @rows;

	&debug("dump_event_name_table: entered");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });
	$sql_buf = "SELECT event_name FROM event_name_table;";
	&debug ("dump_event_name_table: \$sql_buf = [$sql_buf]");
	$rows = $db_handle->selectall_arrayref($sql_buf);
	foreach my $row (@$rows)
	{
		print ("EVENT: @$row\n");
	}
	$db_handle->disconnect;
	&debug("dump_event_name_table: done");
}

sub dump_time_record_table
###############################################################################
# DUMP_USER_TABLE: dumps the contents of the event record table to stdout     #
# REQUIRES: time_record_table exists                                          #
# MODIFIES: nothing                                                           #
# EFFECTS: nothing                                                            #
# RETURNS: nothing                                                            #
###############################################################################
{
	my $db_handle; 
	my $sql_buf;
	my @rows;

	&debug("dump_time_record_table: entered");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });

	$sql_buf = "SELECT event_name, user, problem_space, event_date, duration, event_type FROM time_record_table;";
	&debug("dump_time_record_table: \$sql_buf = [$sql_buf]");
	$rows = $db_handle->selectall_arrayref($sql_buf);
	foreach my $row (@$rows)
	{
		print ("TIME_RECORD: ", join('|', @$row),"\n");


	}
	$db_handle->disconnect;
	&debug("dump_time_record_table: done");
}

sub dump_user_table
###############################################################################
# DUMP_USER_TABLE: dumps the contents of the user table to stdout for viewing #
# REQUIRES: user_table exists                                                 #
# MODIFIES: nothing                                                           #
# EFFECTS: nothing                                                            #
# RETURNS: nothing                                                            #
###############################################################################
{
	my $db_handle; 
	my $sql_buf;
	my @rows;

	&debug("dump_user_table: entered");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });
	$sql_buf = "SELECT user FROM user_table;";
	&debug ("dump_user_table: \$sql_buf = [$sql_buf]");
	$rows = $db_handle->selectall_arrayref($sql_buf);
	foreach my $row (@$rows)
	{
		print ("USER: @$row\n");
	}
	$db_handle->disconnect;
	&debug("dump_user_table: done");
}

sub debug
###############################################################################
# DEBUG: if debug_flag is set to 1 then print the contents of @_              #
# REQUIRES: $debug_flag is globally defined                                   #
# MODIFIES: nothing                                                           #
# EFFECTS: nothing                                                            #
# RETURNS: nothing                                                            #
###############################################################################
{
	if ($debug_flag)
	{
		print ("@_\n");
	}
}

sub truncate_event_name_table
###############################################################################
# TRUNCATE_EVENT_NAME_TABLE: truncates the event_name_table                   #
# REQUIRES: event_name_table exists                                           #
# MODIFIES: event_name_table                                                  #
# EFFECTS: removes all records from event_name_table and frees storage        #
# RETURNS: nothing                                                            #
###############################################################################
{
	my $db_handle; 
	my $sql_buf;

	&debug("truncate_event_name_table: entered");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });
	$sql_buf = "TRUNCATE event_name_table;";
	&debug ("truncate_event_name_table: \$sql_buf = [$sql_buf]");
	$db_handle->do($sql_buf);
	$db_handle->disconnect;
	&debug("truncate_event_name_table: done");
}

sub truncate_user_table
###############################################################################
# TRUNCATE_USER_TABLE: truncates the user_table                               #
# REQUIRES: user_table exists                                                 #
# MODIFIES: user_table                                                        #
# EFFECTS: removes all records from user_table and frees storage              #
# RETURNS: nothing                                                            #
###############################################################################
{
	my $db_handle; 
	my $sql_buf;

	&debug("truncate_user_table: entered");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });
	$sql_buf = "TRUNCATE user_table;";
	&debug ("truncate_user_table: \$sql_buf = [$sql_buf]");
	$db_handle->do($sql_buf);
	$db_handle->disconnect;
	&debug("truncate_user_table: done");
}

sub truncate_time_record_table
###############################################################################
# TRUNCATE_TIME_RECORD_TABLE: truncates the time_record_table                 #
# REQUIRES: time_record_table exists                                          #
# MODIFIES: time_record_table                                                 #
# EFFECTS: removes all records from time_record_table and frees storage       #
# RETURNS: nothing                                                            #
###############################################################################
{
	my $db_handle; 
	my $sql_buf;

	&debug("truncate_time_record_table: entered");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });
	$sql_buf = "TRUNCATE time_record_table;";
	&debug ("truncate_time_record_table: \$sql_buf = [$sql_buf]");
	$db_handle->do($sql_buf);
	$db_handle->disconnect;
	&debug("truncate_time_record_table: done");
}
                                                                                                                              "=‚ƒ!	„)ˆAL!A	‚ ‚‚	`ƒ Á0A‚$@ƒ Â`…ÄDDCU°ÛØ¡Bœ!GÕb'z¡¦©ÅÄEéÞ·q÷wßêŸëëÿÝë‚)ï½}Sê¿¯ÿ~¿ÿwwwëþþ?ˆ×Õû×Ö/Ë¤;ÇÁÿËþ]A_÷õÿ_ÿû×»ï/—Ëåòù|¿eâú	¹t§;²ê¾]Jt]A2ú8á!ð‚BBBJØ&‚J$BB&_	—ËåÂ A0š A0™| ‚„	„&A„„ Â‚ AAA/„Âa0…X@6a‚B!A( …
 ‚ ‚ ‚a0A„!( ‚0A„ Á0A‚`ƒ ÁDXA4BS„‚A#¹Ç	‚A ‘Ü$	ÐH ‚H"  ˜B° Ê8„0‚ˆøA!ˆ@ƒA!A„„„ AÂ‚AAH „ „ „ „ „ ‚D0ƒ""‚ÂbÅˆÝˆ†ÅŒcÄ „DDDDDhDhPB"""""/B8î8ÐÕxŽ"üO‹ëˆéîøÿõÿÿÝµõýUOXÿ¿ñïñe~ý?^O§ÕuUUõ×»îüã®wÎöw;Ôîw;ó¹ÜîÁçs¼Â@‚eëg{_fsjg;Îçs¹ÜîqÌ9œ$w;ÂGu;Îçs¹Üîw;ÎçpA4w;„Žá!#¸Hî;„‚AGs¸A”çpA0L0…‡:gt"&ÂaÎá#¸H „ „ „ „ „ „ „$	‚A!!! H$Aw8âSí„0A„!!!!hMÜ A‚ ‚A¾&!ËÈ „">RÄ †ÂR!öÂ ‚PH$	@‚A
 A‚a@ƒ ÁŽ8A0‚†DD!ˆ†,X$…'J…:¡q¬FÅÅéÅÅÆ«ww~«¯ªþ·÷ý¿í³Ð§ä~ïÿÿÿÿ÷ßÿãXøˆb8Õˆˆ‹ˆˆˆìŽ8ãâ#ïÿ«¿ÿÿô=ÖÙÜîw;Îöw³¹Üï#ÁÎçvG§pDxÇEùO#èC/ÂGâ=!!(saÁËáA	NqÂAÂdx&_.	—Âeð™}‚L&	„Â	„„„0A @ƒ A ‚"ø@¢‚A „ ¡„!O0‚	„ …ó ‚‚aAAH „ „ „ „ „ „ A‚ ‚`ƒB Á0A„A‚ \|03	ŽçpHîw;„Žá ‚;ÂGpHîw;Îçs&^#Äxâ<GˆðBBPá#ŽaÂJÃ„„/—ˆù|&„„	„Â‚ ˜BBBB!!!	„„„ƒ „ B‚`…‚$`„DDDDDPB"!!@„DDDDD „Dpˆ@„DDPB""""""#B8ˆÐˆ¸ˆˆ¾"+ˆ‹¸ˆÿÕÿÐÞ?T45U]t5þûûîÿÿ¯×ÿ«û¿ÿÿÿÝß÷œ~ínÕu;ÙÜîw;Ì9Üîw;ÔîaÌ=œsºÕ2 îw;œsaÌçÏgs¹ÜÌ9‡³¹Üîw;’2œîw;Îçs¹Üîw;Îçp‘Üî8æs¸Hîw;ÂGs¸ ™|¾_/—Â™Üî2‡;Â	„ËÄxð…w	s¹Ü$!!&	„!! H$!!	‚A#¸AÎ8”>ÐHîBS„„„„‚ ‘Ü$ ÁA	„&A	„ÂaAAA0„ „ „ …BBBBL!!!!AL& „ ˜H ‚„ ‚ ˜BB Á0A‚!!`ƒA Á0A‚ ‚A†DDDD0B‚!j¨D „B" Áˆ´"""""Ð‹¸ˆÐ»»¿UU×ø×ÿîâ—î.û¿ïúÿþîÿÿßÿâ¸Ž""5B=b#CNãâøÿþÿûî";ÿÿÿÿÿßw~¹ÜïgÎw;Îçs½©Üî§saÌ9Üîw;„„„Ž9‡S˜3œs8Hã˜saÌçs¹ÜîweòøL&_/—ÑÜL&	„Â	‚B	„Â‚ ‚eôAAA@‚a	C¢êA!N&	„!!Â‚‚‚aAA@ƒBB	„Â‚‚A@ƒB Â`ƒAÈ0s¸Hîw;„Žçs¹Üî	Îá AÎçp‘Ü$&/„!%BBPá! AAH$B!	„„	„&_/—Â‚a0@‚a0( A0„ „$!!!!	Ç @ƒ ‚($C$‚A
	‚A B!"B‚A A") ‚D „BDB Â‚‚ˆ …‚wÂ\F„hj„\DE4*Ð÷ßß¯¯Åßúÿ¯þ¾±ª®ú¯¯¯}÷~ÿ÷ê¿¯ÝÿÞÿßuîþîïïÿµU;ýTîª§sºªÎùžÕUTðw[TÎ=œ{;îïÌöw;©ÝTîw;Îçs¹Üîw	—Ëåô°A3}Îá#¸H$w;‚	—Ëåòð‘ÓA0…T ˜@‚a0„ ˜BPçs¹Ü$A	‚J ˜BB	Žá H „ „$	‚ ŽçJ} ‚8á ‚‚G˜H$A „A	„@‚a	„&	‚!&BBL!!!bBBBL& ‚ Á6@‚a Â 0‚ M†0A„AqÂ ‚B ‚ ‚ Â ‚`ƒH$Aa EB Á6	†0CVHA@ƒBA`„0A„!!`ƒ" ÈàÝˆˆ`†Ÿwq¤+Uø×»û‹†!>ìbîîûîþÿ×ï×ÿ_Uÿ½t8ˆÕuU}PÐ‹‹ˆîÿ¿ïÿˆ¸ûîïþïÕoýc×ÿwýÝê¾wõÕÕvïS¸$#ÿxýÿ^ìîw»!îgs¹ÞÂ@‚a	„Âeòú	+	„!Aw	A	„Â A2øL¼]‚/‚)ÁÂa0˜L&B	„Â A0‚ ‚A!Âa0˜B Â ‚ ‚‚aAH A‚ ‚#Žä	€ q!‚ˆˆˆˆˆAˆˆˆˆAˆˆˆˆˆ°B"B"""!ˆˆˆˆˆˆˆˆˆˆ`„DDDDDDDDDDDDDq§wª¡ÅèFÄ\kwwþ±¯}ßëýúÿÅñ‚Äá¸ä2Ç£ˆˆAˆA‰1Ì8ˆˆˆ B"B!!AˆAAˆAˆˆa@„DDDDDKJ|0G!G!¦9æƒ ä5Ç#Ãhr#×…†0æHƒ‰ƒ‰C‘ŽBŽ"""""""#â""""""""@°|ÃþBŽ@ðPärÇ0äc˜rr†w!\†Øä†!È`rÃ£‘ŽY`mŽA@ä2Ç0ä(ä0äc˜sAdr
!¨9‡0ä4Ç!G!¶99‘ÈeXá$Ç0æBDJ „¡Ì8“DDDDDDDDDkÄqü|q†¸ä5ÜîqÈÇ!¦9‡0ä0çrc®IÎæ†0æƒŽF9œã˜r1Ì9äc˜r1ÈG0äc˜sF9‡	—hˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆ¾!ÈaÈƒÈ±È+ŽC<‡!œwÈ5É9Üîw;Îá#¹ÜÃÎçs¹‡0æÃÌ9‡0äc˜saÌ9‡!(saÌ9‡0æsŽaÌ9
9‡0æÃ˜saÌ9‡0æÃ£â"$3Ž@¬rÃ‘ŽaÈÇ!–9‡"Žg!–9‡!¤9‡!®9±È`saÁeÀšùßÿ_õÿUUÕTðši¦ši¦šiÝöÎéªªªiªjšÏ	•9àîTÎçs¹Üîw;É9Üî;Îçs¹Üîw;Îçs¹àãÎçs¹Üîx8æs¹Ç;Ï9àîw;Êƒ¹Üîw;Îçs¹Üîw;„îw;Žw;Îçs¸”çs¹‡0æîw;œs9Ç0æÎaÂGpœp‘ÜÃÌ9‡0é$aÒAsaÌ8AA	C˜saÌ9
8¤BaÌ9‡0âSˆˆ‹á„ „R! ‚AŠ ¨DE±QUÒI-!APŠUÝRIRT©-ýWÿ_ÿÿÿÿ¥ÿ»íU?ýuW×ÿÿ×Óûÿ¿;þšiÿjšw¯çuí=SM4ÓTÓMS)Îêši¦še9ÝNêw;Ý¦©•r£;ÎåAÜîw;Îçs¹ÜC‚#ù}KåõËåû[µ/—ÐJ/—Ëåð@ƒ*}$‚UT$‘Œ¾_/„„‹åÐIBA	‚AP ˜A
¤’A$ A H ‚ ‚ ‚AaAAAAAAAA$‚	A!	4	¤‚ ‚A	H A„ Â ‚A ‚ ‚ALŠ	„‚ ‚A0ƒ ‚
’HPH$B’E!„5V"¤I E$††ê’TRJ‡ê…!ZUÿïÿÿb""""""."."""""-U5ÐPÐŽ;îô-5B/M5B#U[¾ûîïÿï½u»µOûU´ÿËëßªúùzRþ¾¥ü¿øI ‘URú©|¾¥òþ_	l¾‘x,i+<%.’0 šI2¡Õ ‘| ‚	 ‘}"ú	$A ‚ ‚ ‚ ‚ ‚ ‚ ‚ Gp`	 ¢Øˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆ „DDDDDDDDDDDDDDDDDDDDDDDDDDDDCDDEÄDDDDDDDDDDDDDDDDDDE¡¡qqªÝÞ…¬W‚rÀËrC˜r†Xä09ãd†qÈ(ƒŽC;’ƒ`äcÀäc„2äG#ƒ9dxŽÈù#Äp\Ž2<G
G
Gˆñ#ÄpÓ#Áf_Ž`¥"ŽaÄqòr
0æÎç!œsF9‡0æÃ‘ŽA¤rÇ0äîHr;’Ã˜saÌ9‡0æ†qÈÇ#ŒsBŽaÈÇ	—hØAˆˆ†\ÀŽ/3à–@˜ƒÊ‡²ã˜rÜ…øæ…†›ÈÇeÁÈàxR8ÈáHã#ƒI3‘â<Å­—6ƒÔ"'±<""9¬Hì‚þC”9œîO²ND‚ŽPâH#qÈ9˜rc˜rƒÃqÈ££™Îä2œîAÇ!œsaÈ`sBŽF9F9Ë4üpî!„à¡$ÓN,†%`’Á#±ÁAˆ‘ HàH¶"NDÕˆ’«-ÄKî6"/Žƒ¶¡þƒïÿOX†k§†’„!Ãä	–ä‡Ñòe>™Ùc˜rÃfŒrŽy“,tÌ>qÌçü˜ôaóaÌ>XäcP8Eù‡#»&:ØMp›¾pz"fÃ±«B>+b#ÿbþ8ˆïŠD‡N}Ñtôpl¡ò îBŽ™7;ÚgÃÐR+¦qÛ#‚Ùp& Ý÷	n‚÷¸øŽtÇ`)qÄY€LØØŠJ(áGtŒ9‡0í©îAÇöÆøMþµûÒ1½´zÌ.Iõ„Ûd LÁü}¼q÷$9Èƒ‘¾aòÇI³“Ã˜s™ÜãíÃæ0çsaò(æÃ˜rÇ0áçÃ˜u0û’";¤Ø"?&9‡Î:M®®U|v\‹¿íˆˆØã¸â"-ˆ¾#Ž"#ˆˆˆö#úãŽ¸â.=˜|…£“
[ö29æ…Ïÿ¯ù€iy­|ÇÿÃ/F†¯éý,\]ÆÅ)Ê5Ž""ø‘Gò(íêHruðÈîßÿkÿê¯ø¿¾£]{Ø ‡ LÁÇÇt„\·òŠ9ÁÈk{êÙÇÉŽF:¶aû-Ì?‘ŽaòÇ;iÃ„eŽaè˜ýþCë˜uþ»‰Cì¸>¹ô±ÜDk¿Çw\|GvÄTiô±UI¿HäŸHÃÖXþXùcP9ëô¼WØK~¿½Çö\úù	ôÇâáDRÄq¬lD_AÃùnaôË†#È ô7êÿÿ¥WôÜRÿà‚ñ"¸ä2`æÃ™öüÃ£çÃåg$9‡ÛÒ$9ßÌ9‡0æ ¨8A9‡É®aÁôwÉŽaõÒK0ýî!ÙpÍ‡‹øˆ ¶üGÄD^÷ñqìhk„8èâ'ZØ%_Ì?‘ŽaÌ>gû¾»ÿíÿŽr­ÜÀ«ësÂ¡è|DE »,r1üÃÙr1Ì9õŽ÷ßÿÿ·¡í®ñxp—ßkþ"—â"?,á˜=Ñc¿œr(sBŽaÕ¿$9Þò1Ì9‡ÈjaÌ8Ai^Û“Î:«i^XÿA—dq?‹¯ˆ„7â)b".þ#Xˆâ#¾»v$=øûiöH|Ïá:oÿ¯}ÿoµ¬2â´¦Á?þŽ}«X¿ˆ„^aò1Ì:GR æÁùu)Ã#»">×V?º§Òµmýi÷A/ùÁÿñ±Æ…G³ûi>Lr1ÈÇÈÇË&=ÖÈÇ0ä‡	óŽaÌ;äÞìÃ˜s¹1óŽ®qò1ÛHŒ|±Ì9‡ËS>qÄ2àMðËõm/í –8Ý"8¸Ø¨µˆ‹‹i$"7‹v"5‹Xã¨Øˆãt4$Gúµa¤à’étí…ß~é—?Ýµ×}´ú¨„“‡;±DÇC$9äo–<dn·`ÂZ¼0¹æ{!^«o¶Â^•ö—¶—âÐ‹CB#co0ûaÈÇÈƒ˜saò1Ü·b‹t"Ê,§0æÃ‘ŽaÌ8HîaÌ:‘ŽaüãÎî¥“ÃêBæÃº#
F9'ËÃÃ
qÌ=ã‰Cä	šô…TX»GÇ¸â""#Ž#B>"-ŒV#ûw÷v=âÅ~E!G^„ø0GÍ [!†@6ü5Û†¼2áÒ·ØkÒ„[§ZÄE„„†1ÄD‚ã˜s" Èà®\ˆà¦„ƒA¤rŽ[Ði§á‚Ã»»ýK¸ˆˆÉ~Èi"C‘ŽF9âF9‡8â&Œr1ÈÇ0á"C‰1Ì82ã#ŒŽ28Èù|Ã‘ÁA#ŒŽ28#ÄxŽòC‰cŽ@ÀæJeÁlÂDDDDDDDDD[__Ã. Û¡‚ÐD‡!G!Ì9xaÊƒÁ‡(r.@ürcd A‘ÀðÎG€hM×â"1ˆŽ6AdsÀæ…Œr
ã˜rƒ˜s$9
9‡0äc‘ŽaÌ9æÃƒã˜r1Ì9‡!G0ä3ŽaËŒr1ÈÇ0æÃ˜r#êBŽp&|<BDDDDDDqDDqm#ûW†\2ASˆ„$ÇÇ ¸ä8eÁXŽ†¡6ÈàÊ­/¢ã©1ÈQÈg‡HiŽaÔ†XæÃ„Ø9æŒsaÌ9‡0æ“Îæ…ŒsF9Cã˜r1ÈÇ!G!G!G#¢NF9‡„C\pË4È”r
ã‘ŽA@ä09—!¤91Ì9w0âC4q!EÇÄDDDqò1Ì>aÈÇ!œ|ÎClr1È8ä8æÃ˜rcÀä(æÃ‘ŽAÇ0æÎaÌ9aÌ9‡!Ì9Ç0æŒrŒq ÀäŽ"CTq,0
Ç0ä6Ç0æÃ‘ŽBŽF9
9‡!\ƒw!¤8A	1Ì9‡!Ä‚""%BLq
ƒˆˆˆˆˆˆˆˆˆˆ<3Žaÿ#†Xä+w0æ…ŒsC8äc˜r1ÈQÈQÌ9‡!G0äc˜saÌ9‡0çÃ‘¹‡#Ã£˜saÈgŒr(æÃ˜rÇ#Ã˜r# s%aÈg2àMñ(øþ"!&Œr…ŒrÇ  rs@œrsF9Èsâ""""""@ðjÈÇ Ò9
9Ì9±Ì9æÃ˜sC8äcÎ9‡0æƒŽ@¸æ†!G#†ÈÇ0ä(æ†„á \rp\	 ^@˜w)ÏAPS˜sÁPw;ÎåAPTÎåAÜîw;Îçs¹Üîw;Îçs¹Üîg)Îçs¹‡;Îçs¹Üîw;Îçs¹Üîw;Îçs¹ÜîaÎçs9Üîw;’sŽaÌçs¹Üã„ŽçÎqÌçÎw;„„Œ8Hîw;ÎæÃ„Žçq)Ì9‡0æÃ˜saÌ9‡0æ$BLsF9‡H „ã„ˆˆ”9âPâPâ"$ÇCˆAˆˆˆˆˆˆþ××I Á*	-ÒU¥Õ*¬÷ý÷uþ¿ÿúÿÿ÷ÿÚ_þ«ýýé÷ýëÿê·ç}U4ÕSM4Ó¾Îé©Ý;[[;g{;ìïeAÜîw;Îçu;ÎéÎçr¢Îçs¹Üîw;Îçs¹ÜÎw;Îçs¹Üîw;Îçs¹Üîw;Îçrœîw;ÎçsÁÇ3Ês¹ÜÃ™Î9‡3Î9œB	B‚A¤B	$@ƒè$A
$‚H$"øA ‚ …H ‚A@ƒ	‚$ A‚ ‚ ‚! ‚ ‚A ‚ ($‚A AAÇh$‚AAAA!AAA$A	H  „0‚	 ‚H$L $M‚(!!!‚AA„( T+¸ @ªþ‚Ikª\qÝÿÿÿÿÿëþ—ýÿ^¿¦•§÷øÓM4ÓM4î.Öîÿÿý}WUU[Uõ×_ûÿ]Õ;µïþ;¯ÿ®þ¿¥õ]oòÿ¥Õ}5½j_.¼Â­¯/åùÇ—ÕØL&w¤Â •$H$’Eð‚@Îèº A0˜AA Â ‚ ‚ ‚ ‚ ‚ ‚ ‚IAA$AA0’AAA ‚‚	 H ‚‚ ‚e@eÀšá!!¡DDEÅ¡whZhZ¡DZhiÜkÆ‚?ý4ÿÿí}?[ÿþÿëÿÿÕÿîõÿ_ýWÞ¾ïãˆˆˆˆˆˆˆˆˆˆˆâ""""""""""""""""""""""""""""""""""""""""!&[“‚ã˜rÇ!G#Ã˜saÈ`saÈ`sA@æÎCHrsaÌ9
9
9
9ã£˜s ÈàNGäpPGˆáHñ#ÄxŽÈñ#‚äp¤p¤p×H6á‘Ál¢F9âaÿÄr|GÌ>C˜rÈAÌ9æÃóaÌ9‡#îw#îaÎæÃ˜saÌ9‡0ä(æŒsXæÃ˜rÇ0ä09
9‡#ŒsqÌ9‡