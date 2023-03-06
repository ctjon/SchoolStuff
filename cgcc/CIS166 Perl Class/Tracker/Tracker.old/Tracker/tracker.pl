#!/usr/bin/perl -w
# tracker.pl
# Written By: Chris Tjon
# Time Tracking System for Problem Calls
# 15 Oct 2004
#
use strict;
use CGI qw/:standard/;
use CGI::Carp;
use DBI;

my $database = 'tracker_db';
my $db_host = 'localhost';
my $db_port = '3306';
my $db_user = 'tracker_user';
my $db_passwd = 'password';
my $debug_flag = 1;

                                                                                                                   
 print header,
        start_html('A Simple Example'),
        h1('A Simple Example'),
        start_form,
        "What's your name? ",textfield('name'),p,
        "What's the combination?", p,
        checkbox_group(-name=>'words',
		       -values=>['eenie','meenie','minie','moe'],
		       -defaults=>['eenie','minie']), p,
        "What's your favorite color? ",
        popup_menu(-name=>'color',
	           -values=>['red','green','blue','chartreuse']),p,
        submit,
        end_form,
        hr;

   if (param()) {
       print "Your name is",em(param('name')),p,
	     "The keywords are: ",em(join(", ",param('words'))),p,
	     "Your favorite color is ",em(param('color')),
	     hr;
   }  

&debug("*******************************************************************************");
#&test_user_table_functions;
#&test_event_name_table_functions;
&test_time_record_table_functions;
&report_by_ind("chris", "2004-10-15", "2004-10-18");
&report_by_team("2004-10-15", "2004-10-18");
&report_by_event("lspx outage", "2004-10-15", "2004-10-19");

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
	&add_time_record("LSPA Outage", "chris", "DS", "2004-10-16", "3", "TL");
	&add_time_record("LSPx Outage", "chris", "DS", "2004-10-17", "4", "TL");
	&add_time_record("LSPy Outage", "chris", "DS", "2004-10-18", "1", "TL");
	&add_time_record("LSPz Outage", "chris", "DS", "2004-10-19", "6", "TL");
	&dump_time_record_table;
	&add_time_record("LSPB Outage", "scott", "DS", "2004-10-15", "2", "TL");
	&dump_time_record_table;
	&change_time_record("LSPA Outage", "chris", "DS", "2004-10-15", "2", "TL", "LSPX Outage", "JB", "DS", "2004-10-15", "2", "TL"
);
	&dump_time_record_table;
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
	&change_user_name("JB", "Jonathan");
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
	my $sql_fmt = "INSERT INTO time_record_table VALUES(UPPER('%s'), UPPER('%s'), UPPER('%s'), '%s', '%d', UPPER('%s'));";
	$sql_buf = sprintf($sql_fmt, $event_name, $user_name, $prob_space, $event_date, $duration, $event_type);
	&debug("add_time_record: \$sql_buf = [$sql_buf]");
	$db_handle->do($sql_buf);
	$db_handle->disconnect;
	&debug("add_time_record: added [$event_name,$user_name,$prob_space,$event_date,$duration,$event_type] to time_record_table");
}

sub change_time_record # (char $old_event_name, $new_event_name, $old_user_name, $new_user_name, $old_prob_space, $new_prob_space, $old_event_date, $new_event_date, $old_duration, $new_duration, $old_event_type, $new_event_type)
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
	my $old_event_name = $_[0];
	my $old_user_name = $_[1];
	my $old_prob_space = $_[2];
	my $old_event_date = $_[3];
	my $old_duration = $_[4];
	my $old_event_type = $_[5];
	my $new_event_name = $_[6];
	my $new_user_name = $_[7];
	my $new_prob_space = $_[8];
	my $new_event_date = $_[9];
	my $new_duration = $_[10];
	my $new_event_type = $_[11];

	&debug("change_time_record: updating [$old_event_name,$old_user_name,$old_prob_space,$old_event_date,$old_duration,$old_event_type] to [$new_event_name,$new_user_name,$new_prob_space,$new_event_date,$new_duration,$new_event_type] in time_record_table");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });
	my $sql_fmt = "UPDATE time_record_table SET event_name = UPPER('%s'), user = UPPER('%s'), problem_space = UPPER('%s'), event_date = '%s', duration = '%d', event_type = UPPER('%s') WHERE event_name = UPPER('%s') AND user = UPPER('%s') AND problem_space = UPPER('%s') AND event_date = '%s' AND duration = '%d' AND event_type = UPPER('%s');";
	$sql_buf = sprintf($sql_fmt, $new_event_name, $new_user_name, $new_prob_space, $new_event_date, $new_duration, $new_event_type, $old_event_name, $old_user_name, $old_prob_space, $old_event_date, $old_duration, $old_event_type);
	&debug("change_time_record: \$sql_buf = [$sql_buf]");
	$db_handle->do($sql_buf);
	$db_handle->disconnect;
	&debug("change_time_record: updated [$old_event_name,$old_user_name,$old_prob_space,$old_event_date,$old_duration,$old_event_type] to [$new_event_name,$new_user_name,$new_prob_space,$new_event_date,$new_duration,$new_event_type] in time_record_table");
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
	my $sql_fmt = "DELETE FROM time_record_table WHERE event_name = UPPER('%s') AND user = UPPER('%s') AND problem_space = UPPER('%s') AND event_date = '%s' AND duration = '%d' AND event_type = UPPER('%s');";
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
	my $rows;

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
	my $rows;

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

sub report_by_ind #(char user, date start_date, date end_date)
###############################################################################
# REPORT_BY_IND: report on an individuals call hours between start & end date #
# REQUIRES: time_record_table exists                                          #
# MODIFIES: nothing                                                           #
# EFFECTS: nothing                                                            #
# RETURNS: nothing                                                            #
###############################################################################
{
	my $db_handle; 
	my $sql_buf;
	my @rows;
	my $rows;
	my $total_duration = 0;
	my $event_name;
	my $user_name = $_[0];
	my $problem_space;
	my $event_date;
	my $duration;
	my $event_type;
	my $start_date = $_[1];
	my $end_date = $_[2];

	&debug("report_by_ind: entered");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });

	my $sql_fmt = ("SELECT event_name, user, problem_space, event_date, duration, event_type FROM time_record_table WHERE user = UPPER('%s') and event_date BETWEEN '%s' AND '%s';");
	$sql_buf = sprintf($sql_fmt, $user_name, $start_date, $end_date);
	&debug("report_by_ind: \$sql_buf = [$sql_buf]");
	$rows = $db_handle->selectall_arrayref($sql_buf);
	
	print ("Date Range: ", $start_date, " thru ", $end_date, "\n");
	foreach my $row (@$rows)
	{
		$event_name = @$row[0];
		$user_name = @$row[1];
		$problem_space = @$row[2];
		$event_date = @$row[3];
		$duration = @$row[4];
		$event_type = @$row[5];
		print (join(' | ', @$row),"\n");
		$total_duration += $duration;
	}
	print ("total for $user_name:  $total_duration\n");
	$db_handle->disconnect;
	&debug("report_by_ind: done");
}

sub report_by_event #(char event_name, date start_date, date end_date)
###############################################################################
# REPORT_BY_IND: report all hours for an event between start_date & end_date  #
# REQUIRES: time_record_table exists                                          #
# MODIFIES: nothing                                                           #
# EFFECTS: nothing                                                            #
# RETURNS: nothing                                                            #
###############################################################################
{
	my $db_handle; 
	my $sql_buf;
	my @rows;
	my $rows;
	my $total_duration = 0;
	my $event_name = $_[0];
	my $user_name;
	my $problem_space;
	my $event_date;
	my $duration;
	my $event_type;
	my $start_date = $_[1];
	my $end_date = $_[2];

	&debug("report_by_event: entered");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });

	my $sql_fmt = ("SELECT event_name, user, problem_space, event_date, duration, event_type FROM time_record_table WHERE event_name = UPPER('%s') and event_date BETWEEN '%s' AND '%s';");
	$sql_buf = sprintf($sql_fmt, $event_name, $start_date, $end_date);
	&debug("report_by_event: \$sql_buf = [$sql_buf]");
	$rows = $db_handle->selectall_arrayref($sql_buf);
	
	print ("Date Range: ", $start_date, " thru ", $end_date, "\n");
	foreach my $row (@$rows)
	{
		$event_name = @$row[0];
		$user_name = @$row[1];
		$problem_space = @$row[2];
		$event_date = @$row[3];
		$duration = @$row[4];
		$event_type = @$row[5];
		print (join(' | ', @$row),"\n");
		$total_duration += $duration;
	}
	print ("total for $event_name:  $total_duration\n");
	$db_handle->disconnect;
	&debug("report_by_event: done");
}

sub report_by_team #(date start_date, date end_date)
###############################################################################
# REPORT_BY_TEAM: Report on totals for team between start_date & end_date     #
# REQUIRES: time_record_table exists                                          #
# MODIFIES: nothing                                                           #
# EFFECTS: nothing                                                            #
# RETURNS: nothing                                                            #
###############################################################################
{
	my $db_handle; 
	my $sql_buf;
	my @rows;
	my $rows;
	my $total_duration = 0;
	my $event_name;
	my $user_name;
	my $problem_space;
	my $event_date;
	my $duration;
	my $event_type;
	my $start_date = $_[0];
	my $end_date = $_[1];

	&debug("report_by_team: entered");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });

	my $sql_fmt = ("SELECT event_name, user, problem_space, event_date, duration, event_type FROM time_record_table WHERE event_date BETWEEN '%s' AND '%s';");
	$sql_buf = sprintf($sql_fmt, $start_date, $end_date);
	&debug("report_by_ind: \$sql_buf = [$sql_buf]");
	$rows = $db_handle->selectall_arrayref($sql_buf);
	
	print ("Date Range: ", $start_date, " thru ", $end_date, "\n");
	foreach my $row (@$rows)
	{
		$event_name = @$row[0];
		$user_name = @$row[1];
		$problem_space = @$row[2];
		$event_date = @$row[3];
		$duration = @$row[4];
		$event_type = @$row[5];
		print (join(' | ', @$row),"\n");
		$total_duration += $duration;
	}
	print ("total:  $total_duration\n");
	$db_handle->disconnect;
	&debug("report_by_team: done");
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
	my $rows;

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
