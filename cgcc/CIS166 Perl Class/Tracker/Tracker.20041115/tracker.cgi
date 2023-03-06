#!/usr/bin/perl -w
# tracker.pl
# Written By: Chris Tjon
# Time Tracking System for Problem Calls
# 15 Oct 2004
#
use strict;
use CGI;
use CGI::Carp qw(fatalsToBrowser);
use DBI;

my $database = 'tracker_db';
my $db_host = 'localhost';
my $db_port = '3306';
my $db_user = 'tracker_user';
my $db_passwd = 'password';
my $debug_flag = 1;

my $new_event;
my $event_name;
my $user;
my $problem_space;
my $event_date;
my $duration;
my $event_type;
my $q = new CGI;
&debug("main - starting");
my @users = &get_user_list;
my @events = &get_event_list;
                                                                                                                   
&do_main_page;

#&do_form;

#&test_user_table_functions;
#&test_event_name_table_functions;
#&test_time_record_table_functions;
#&report_by_ind("chris", "2004-10-15", "2004-10-18");
#&report_by_team("2004-10-15", "2004-10-18");
#&report_by_event("lspx outage", "2004-10-15", "2004-10-19");


&debug("main - done");
#
# END OF MAIN PROGRAM - SUBROUTINES FOLLOW
#


sub do_main_page
###############################################################################
# DO_FORM: Prints the form on screen and collects input                       #
# REQUIRES:                                                                   #
# MODIFIES:                                                                   #
# EFFECTS:                                                                    #
# RETURNS:                                                                    #
###############################################################################
{
	my $choice = 'none';

	if ($q->param('choice'))
	{
		&debug("do_main_page - \$q->param('choice') is set");
	}
	else
	{
		&debug("do_main_page - \$q->param('choice') is not set");
	}
	if ($q->param('choice'))
	{

		$choice = $q->param('choice');
		&debug("do_main_page  - \$choice = [$choice]", $q->p);

		if ($choice eq 'Enter Data')
		{
			&do_form;
		}
		if ($choice eq 'View Reports')
		{
			&do_reporting;
		}
	}
	else
	{
		&debug("do_main_page - printing page");
		print $q->header,
		$q->start_html('Welcome to Time Tracker'),
		$q->h1('Welcome to Time Tracker'),
		$q->start_form,
		"Would you like to 'Enter' or 'View' data?",$q->p,
		"Choice: ", $q->checkbox_group(-name=>'choice', -values=>['Enter Data','View Reports']), $q->p,
		$q->submit("Submit"),
		$q->reset("Clear"),
		$q->end_form,
		$q->hr;
		$q->end_html;
		&debug("do_main_page - page printed");
	}
}  

sub do_reporting
###############################################################################
# DO_REPORTING: allows for queries of the db through the user interface       #
# REQUIRES:                                                                   #
# MODIFIES:                                                                   #
# EFFECTS:                                                                    #
# RETURNS:                                                                    #
###############################################################################
{
	&debug("do_reporting - entered");
	&debug("do_reporting - exiting");
}

sub do_form
###############################################################################
# DO_FORM: Prints the form on screen and collects input                       #
# REQUIRES:                                                                   #
# MODIFIES:                                                                   #
# EFFECTS:                                                                    #
# RETURNS:                                                                    #
###############################################################################
{
	&debug("do_form - entered");

#	if (($q->param('event_name') || $q->param('new_event')) && $q->param('user') && $q->param('problem_space') && $q->param('event_date') && $q->param('duration') && $q->param('event_type'))
#	if ($q->param('event_name'))
	if ($q->param('user'))
	{
		&debug("do_form - \$q->param('user') is set");
	}
	else
	{
		&debug("do_form - \$q->param('user') is not set");
	}
	if ($q->param('user'))
	{
		&debug("do_form - getting parameters");

		$event_name = $q->param('event_name');
		$new_event = $q->param('new_event');
		$user = $q->param('user');
		$problem_space = $q->param('problem_space');
		$event_date = $q->param('event_date');
		$duration = $q->param('duration');
		$event_type = $q->param('event_type');

		&debug("do_form - \$event_name = [$event_name]", $q->p);
		&debug("do_form - \$new_event = [$new_event]", $q->p);
		&debug("do_form - \$user = [$user]", $q->p);
		&debug("do_form - \$problem_space = [$problem_space]", $q->p);
		&debug("do_form - \$event_date = [$event_date]", $q->p);
		&debug("do_form - \$duration = [$duration]", $q->p);
		&debug("do_form - \$event_type = [$event_type]", $q->p);

		if ($problem_space eq 'Distributed') { $problem_space = 'DS'; }
		if ($problem_space eq 'MainFrame') { $problem_space = 'MF'; }
		if ($problem_space eq 'Network') { $problem_space = 'NW'; }
		if ($problem_space eq 'Other') { $problem_space = 'OT'; }
		if ($event_type  eq 'Techline') { $event_type = 'TL'; }
		if ($event_type  eq 'ProbMgmt') { $event_type = 'PM'; }
		if ($event_type  eq 'Other') { $event_type = 'OT'; }
		if (($new_event ne '') && ($event_name eq ''))
		{
			&debug("do_form - assigning \$event_name = [$new_event]");
			$event_name = $new_event;
		}
		if (!(&event_exists($event_name)))
		{
			&add_event($event_name);
		}
		if (!(&time_record_exists($event_name, $user, $problem_space, $event_date, $duration, $event_type)))
		{
			&add_time_record($event_name, $user, $problem_space, $event_date, $duration, $event_type);
			print $q->header,
			$q->start_html('Thank You!'),
			$q->h1('Record Accepted!'), $q->p,
			"Event Name = [$event_name]", $q->p,
			"User = [$user]", $q->p,
			"Problem Space =  [$problem_space]", $q->p,
			"Event Date =  [$event_date]", $q->p,
			"Duration = [$duration]", $q->p,
			"Event Type = [$event_type]", $q->p,
			$q->hr,
			$q->end_html;
		}
		else
		{
			print $q->header,
			$q->start_html('Duplicate!'),
			$q->h1('Duplicate Record Not Accepted!'), $q->p,
			"Event Name = [$event_name]", $q->p,
			"User = [$user]", $q->p,
			"Problem Space =  [$problem_space]", $q->p,
			"Event Date =  [$event_date]", $q->p,
			"Duration = [$duration]", $q->p,
			"Event Type = [$event_type]", $q->p,
			$q->hr,
			$q->end_html;
		}
		$q->delete('event_name');
		$q->delete('new_event');
		$q->delete('user');
		$q->delete('problem_space');
		$q->delete('event_date');
		$q->delete('duration');
		$q->delete('event_type');
	}
	else
	{
		&debug("do_form - printing form");
		print $q->header,
		$q->start_html('Time Tracker Data Entry'),
		$q->h1('Time Tracker Data Entry'),
		$q->start_form,
		"Please Enter your Information",$q->p,
		"User Name: ", $q->popup_menu(-name=>'user', -values=>['', sort(@users)]),$q->p,
		"Existing Event: ", $q->popup_menu(-name=>'event_name', -values=>['', sort(@events)]),
		" OR New Event: ", $q->textfield('new_event'),$q->p,
		"Problem Space: ", $q->checkbox_group(-name=>'problem_space', -values=>['Distributed','MainFrame','Network','Other']), $q->p,
		"Event Date(YYYY-MM-DD): ",$q->textfield('event_date'),$q->p,
		"Duration(Hrs): ",$q->textfield('duration'),$q->p,
		"Event Type: ", $q->checkbox_group(-name=>'event_type', -values=>['Techline','ProbMgmt','Other']), $q->p,
		$q->submit("Submit"),
		$q->reset("Clear"),
		$q->end_form,
		$q->hr;
		$q->end_html;
		&debug("do_form - form printed");
	}
	&debug("do_form - exiting");
}  

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
	if (!($db_handle->do($sql_buf)))
	{
		print ("error in add_time_record SQL\n");
	}
	&log_sql($sql_buf);
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
	&log_sql($sql_buf);
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
	&log_sql($sql_buf);
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
	&log_sql($sql_buf);
	&debug("add_event: added [$event_name] to event_name_table");
	$db_handle->disconnect;
}

sub event_exists # (char $event_name)
###############################################################################
# event_exists: checks to see if an event already exists in the event table   #
# REQUIRES:                                                                   #
# MODIFIES:                                                                   #
# EFFECTS:                                                                    #
# RETURNS:                                                                    #
###############################################################################
{
	my $db_handle; 
	my $sql_buf;
	my $event_name = $_[0];
	my @event_list;
	my @rows;
	my $rows;

	&debug("event_exists: entered");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });
	my $sql_fmt = ("SELECT event_name FROM event_name_table WHERE UPPER(event_name) = UPPER('%s');");
	$sql_buf = sprintf($sql_fmt, $event_name);
	&debug ("event_exists: \$sql_buf = [$sql_buf]");
	$rows = $db_handle->selectall_arrayref($sql_buf);
	$db_handle->disconnect;
	if (@$rows)
	{
		&debug("event_exists: [$event_name] exists in event_name_table");
		return(1);
	}
	else
	{
		&debug("event_exists: [$event_name] does not exist in event_name_table");
		return(0);
	}
}

sub time_record_exists # (char $event_name, $user_name, $prob_space, $event_date, $duration, $event_type)
###############################################################################
# TIME_RECORD_EXISTS: checks to see if an record already exists in the        #
#                     time_record_table                                       #
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
	my @event_list;
	my @rows;
	my $rows;

	&debug("time_record_exists: entered");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });
	my $sql_fmt = ("SELECT event_name, user, problem_space, event_date, duration, event_type FROM time_record_table WHERE UPPER(event_name) = UPPER('%s') AND UPPER(user) = UPPER('%s') AND UPPER(problem_space) = UPPER('%s') AND event_date = '%s' AND duration = '%d' AND UPPER(event_type) = UPPER('%s');");
	$sql_buf = sprintf($sql_fmt, $event_name, $user_name, $prob_space, $event_date, $duration, $event_type);
	&debug ("time_record_exists: \$sql_buf = [$sql_buf]");
	$rows = $db_handle->selectall_arrayref($sql_buf);
	$db_handle->disconnect;
	if (@$rows)
	{
		&debug("time_record_exists: [$event_name, $user_name, $prob_space, $event_date, $duration, $event_type] exists in time_record_table");
		return(1);
	}
	else
	{
		&debug("time_record_exists: [$event_name, $user_name, $prob_space, $event_date, $duration, $event_type] does not exist in time_record_table");
		return(0);
	}
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
	&log_sql($sql_buf);
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
	&log_sql($sql_buf);
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
	&log_sql($sql_buf);
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
	&log_sql($sql_buf);
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
	&log_sql($sql_buf);
	$db_handle->disconnect;
	&debug("delete_user: deleted [$user_name] from user_table");
}

sub get_user_list
###############################################################################
# GET_USER_LIST: returns a list of all users from the user_table              #
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
	my @return_list;

	&debug("get_user_list: entered");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });
	$sql_buf = "SELECT user FROM user_table ORDER BY user;";
	&debug ("get_user_list: \$sql_buf = [$sql_buf]");
	$rows = $db_handle->selectall_arrayref($sql_buf);
	foreach my $row (@$rows)
	{
		unshift(@return_list, @$row);
	}
	$db_handle->disconnect;
	&debug("get_user_list: returning \@return_list");
	return @return_list;
}

sub get_event_list
###############################################################################
# GET_EVENT_LIST: returns a list of all the events in the event_name_table    #
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
	my @return_list;

	&debug("get_event_list: entered");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });
	$sql_buf = "SELECT event_name FROM event_name_table ORDER BY event_name;";
	&debug ("get_event_list: \$sql_buf = [$sql_buf]");
	$rows = $db_handle->selectall_arrayref($sql_buf);
	foreach my $row (@$rows)
	{
		unshift(@return_list, @$row);
	}
	$db_handle->disconnect;
	&debug("get_event_list: returning \@return_list");
	return @return_list;
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

sub log_sql
###############################################################################
# LOG_SQL: log all sql statements to /var/log/tracker/sql_log.YYYYMMDD        #
# REQUIRES: /var/log/tracker is writeable                                     #
# MODIFIES: /var/log/tracker/sql_log.YYYYMMDD                                 #
# EFFECTS: logs SQL statment into log file                                    #
# RETURNS: nothing                                                            #
###############################################################################
{
	my $logdir = "/var/log/tracker";
	my @buf = @_;
	my $year = `date +%Y`;
	my $month = `date +%m`;
	my $day = `date +%d`;
	my $logfile;

	$logfile = sprintf("%s/sqllog.%4.4d%2.2d%2.2d", $logdir, $year, $month, $day);
	
	unless (open SQLLOG, ">>$logfile")
	{
		die("log_sql - cannot open \$logfile=[$logfile]\n");
	}
	printf (SQLLOG "%s\n", @buf);
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
		my $logdir = "/var/log/tracker/debug";
		my @buf = @_;
		my $year = `date +%Y`;
		my $month = `date +%m`;
		my $day = `date +%d`;
		my $hour = `date +%H`;
		my $min = `date +%M`;
		my $sec = `date +%S`;
		my $logfile;

		$logfile = sprintf("%s/debug.%4.4d%2.2d%2.2d%2.2d%2.2d", $logdir, $year, $month, $day, $hour, $min);

		unless (open DEBUGLOG, ">>$logfile")
		{
			die("debug - cannot open \$logfile=[$logfile]\n");
		}
		printf (DEBUGLOG "%s\n", @buf);
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
	&log_sql($sql_buf);
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
	&log_sql($sql_buf);
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
	&log_sql($sql_buf);
	$db_handle->disconnect;
	&debug("truncate_time_record_table: done");
}

=head1 tracker

=head1 SYNOPSIS

Web-Based Time Tracking Program

=head1 DESCRIPTION 

This program will be a web based time tracking program.  A user will simply direct his or her web browser to a URL to use the program.  The user will be authenticated in order to gain access to the system.  Then the user will be allowed to enter a new record into the system, edit an existing record, or create a report for time records for themselves.

This program will require a web front end and a SQL Database on the backend.  My plan is to use the PerlLWP and Perl DBI modules to build a CGI that can be loaded to do this work.  For the database, I plan to use MySQL although I suspect the program could be easily adapted to use Oracle or SQL Server 2000.  I will include the create table SQL and the sample start data in the documentation for the program.

There will also need to be a manager role.  The manager role will have the ability to create a report for the whole group as well as each individual.  Further, the manager will have the ability to add and delete users from the system.

This system will require 3 database tables to work correctly:
	1) a user table:  this table will be a simple list of users of the system to be managed by the manager
	participant varchar(32);	# names of people on the team - Primary Key
	2) an event name table: this table will be a simple list of event names which represent things that may have occurred.  The field will be 
	event_name varchar2(32);	# names of events that occur - Primary Key
	3) a time records table:  this table will be a list of records which represent the detail data submitted by the users.  Each record will contain the following fields:  
	event_name varchar2(32);	# Foreign Key which much exist in the event table
	participant varchar(32);	# Foreign Key will will tie back to the user table
	problem_space char(2);	# one of [MF, NW, DS] which mean, Mainframe, Network, or distributed systems
	event_date date;	# date of event
	duration number(2)	# duration in hours
	event_type char2(2);	# type of event, TL=techline, TIR=tech incident review, OT=Other

The following subroutines will be required:

	validate_user(participant);
	logoff_user(participant);
	add_user(participant)*
	change_user(participant)*
	delete_user(participant)*
	add_event(event_name)
	change_event(event_name)
	delete_event(event_name)
	add_record(event_name, participant, problem_space, event_date, duration, event_type)
	change_record (event_name, participant, problem_space, event_date, duration, event_type)
	delete_record (event_name, participant, problem_space, event_date, duration, event_type)
	show_record(record_id)
	report_by_individual(participant, start_date, end_date)
	report_by_team(start_date, end_date)
	report_by_event(event_name, start_date, end_date)

	subroutines denoted by (*) will only be allowed to be performed by the manager.

The program will use the following logic to accomplish its work:

	startup
	validate_user(participant);
	prompt user for what they would like to do:
	if prompt = add_user then adduser(participant)
	if prompt = change_user then change_user(participant)*
	if prompt = delelte_user then delete_user(participant)*
	if prompt = add_event then  add_event(event_name)
	if prompt = change_event then change_event(event_name)
	if prompt = delete_event then delete_event(event_name)
	if prompt = add_record then add_record(event_name, participant, problem_space, event_date, duration, event_type)
	if prompt = change_record then change_record (event_name, participant, problem_space, event_date, duration, event_type)
	if prompt = delete_record then delete_record (event_name, participant, problem_space, event_date, duration, event_type)
	if prompt = show_record then show_record(record_id)
	if prompt = report_by_individual then report_by_individual(participant, start_date, end_date)
	if prompt = report_by_team then report_by_team(start_date, end_date)
	if prompt = report_by event then report_by_event(event_name, start_date, end_date)
	if prompt = logoff then logoff_user(participant);
	prompt again

=head1 OPTIONS

Optional upgrades may include the use of stylesheets, pull down menus, and active directory authentication

=head1 FILES

tracker.pl

=head1 AUTHOR

Chris Tjon

