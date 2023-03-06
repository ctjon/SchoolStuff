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
                                                                                                                              "=��!	�)�AL!A	� ��	`� �0A�$@� �`��DDCU��ءB�!�G�b'z�����E�޷q�w��������)�}S꿯�~��www���?������/ˤ;�����]A_���_��׻�/�����|�e��	�t�;���]Jt]A2�8�!��BBBJ�&�J$BB&_	���� A0� A0�| ��	�&A�� �� �AAA/��a0�X@�6a�B!A( �
 � � �a0A�!( ��0A� �0A�`� �DXA4BS��A#��	�A ��$	��H �H"� �B�� �8�0���A!�@�A!A�����A��AAH � � � � � �D0�""��bň݈�Ōc� �DDDDDhDhPB"""""/B8�8��x�"�O����������ݵ��UOX�����e~�?^O��uUU�׻��㐮w��w;���w;������s��@�e�g{_fs�jg;���s���q�9�$w;��Gu;���s���w;���pA4w;���!#�H�;��AGs�A��pA0L0��:gt"&�a��#�H � � � � � � �$	�A!!! �H$Aw8�S��0A�!!!!hM� A� �A�&!�� �">R�� ��R!��� �PH$	@�A
 A�a@� ��8A0��DD!��,X$�'J�:�q�F������ƫww~���������Ч�~���������X����b8��������8��#�������=����w;���w����#���vG�pDx�E�O#�C/�G�=!!(sa���A	Nq�A�dx&_.	��e�}�L&	��	���0A��@� A��"�@��A �� ��!O0�	� �� ��aAAH � � � � � � A� �`�B �0A�A� \|�03	��p�H�w;��� �;��Gp�H�w;���s&^#�x��<G��BBP�#�a�JÄ�/���|&��	��� �BBBB!!!	���� � B�`��$`�DDDDDPB"!!@�DDDDD �Dp��@�DDPB""""""#B8�Ј�����"+������������?T45U]t5�������������������~�n�u;���w;��9��w;���a�=�s���2��w;�sa���gs���9�����w;�2��w;���s���w;���p���8�s�H�w;��Gs� �|�_/�����2�;��	���x���w	s��$!!&	�!! �H$!!	�A#�A�8�>�H�BS����� ��$ �A	�&A	��aAAA0� � � �BBBBL!!!!AL& � �H ���� �BB �0A�!!`�A �0A� �A�DDDD0B�!j�D �B" ���"""""Ћ��л��UU�������.�����������⸍�""5B=b#CN��������";������w~���g�w;���s����sa�9��w;����9�S�3�s8H�sa��s���we��L&_/���L&	��	�B	��� �e�AAA@�a	C��A!N&	�!!����aAA@�BB	�����A@�B �`�A�0s�H�w;���s���	�� �A��p��$&/�!%BBP�! AAH$B!	��	�&_/���a0�@�a0�( A0� �$!!!!	� �@� �($C$�A
	�A �B!"B�A �A")��D �BDB �������w�\F�hj�\DE4*���������������������}�~��꿯�����u�������U;��Ts�������UT�w[T�=�{;�����w;��T�w;���s���w	�����A3}��#�H$w;�	������A0�T �@�a0� �BP�s��$A	�J �BB	�� �H � �$	� ��J}��8� ���G�H$A ��A	�@�a	�&	�!&BBL!!!bBBBL& � ��6@�a��� �0� M�0A�Aq� �B � � � �`�H$Aa �EB �6	�0�CVHA@�BA`�0A�!!`�" ��݈�`��wq�+U�׻���!>�b����������_U���t8��uU�}PЋ���������������o�c��w���w���v�S�$#��x���^��w�!�gs���@�a	��e��	+	�!Aw	A	�� A2�L�]�/�)��a0�L&B	�� A0� �A!�a0�B � � ��aAH A� �#��	��q!�������A����A������B"B"""!����������`�DDDDDDDDDDDDDq�w����F��\kww���}���������ā��2����A�A�1�8��� B"B!!A�AA�A��a@�DDDDDKJ|�0G!G!�9�� �5�#Ðhr#����0�H����C��B�"""""""#�""""""""@�|��B�@�P�r�0�c�rr�w!\����!��`rÐ���Y`m�A@�2�0�(�0�c�sAdr
!�9�0�4�!G!�99��eX�$�0�BDJ ���8�DDDDDDDDDk�q�|q���5��q��!�9�0�0�rc��I���0���F9��r1�9�c�r1�G0�c�sF9�	�h������������������������!�a������+�C�<�!�w�5�9��w;���#��Ý��s��0�Ý�9�0�c�sa�9�!(sa�9�0�s�a�9
9�0�Øsa�9�0�Ð��"$3�@�rÑ�a��!�9�"�g!�9�!�9�!�9��`sa�e�����_��UU�T�i��i��i�����骪�i�j���	�9��T��s���w;��9��;���s���w;���s�����s���x8�s��;��9��w;�ʃ���w;���s���w;���w;��w;���s���s��0��w;�s9�0��a�Gp��p��Ý�9�0�$a�Asa�8AA	C�sa�9
8�Ba�9�0�S������R!��A���DE�QU�I-!AP�U�RIRT�-�W�_��������U?�uW��������;��i�j�w��u�=SM4�T�MS)��i��e9�N�w;ݦ��r�;���A��w;���s��C�#�}K�����[�/��J/����@�*}$�UT$���_/�����IBA	�AP �A
��A$ A��H � � �AaAAAAAAAA$�	A!	4	����A	H A� � �A � �AL�	�� �A0� �
�HPH$B�E!�5V"��I �E$���TRJ��!ZU����b""""""."."""""-U5ЍPЎ;��-5B/M5B#U[������u��O�U��������zR������I �UR��|����_	�l��x,i+<%.�0� �I2�� �| �	 �}"�	$�A � � � � � � � Gp�`	��؈�����������������DDDDDDDDDDDDDDDDDDDDDDDDDDDDCDDE�DDDDDDDDDDDDDDDDDDE��qq��ޅ�W�r��rC�r�X�09�d�q�(��C;��`�c���c�2�G#�9dx���#�p\�2<G
G
G��#�p�#�f_�`�"�a�q�r
0����!�sF9�0�Ñ�A�r�0��Hr;�Øsa�9�0��q��#�sB�a��	�h�A���\��/�3��@�������r܅���������e���xR8��H�#�I3��<�ŭ�6��"'�<""9�H��C�9��O�ND��P�H#q�9�rc�r��Ðqȣ�����2��A�!�sa�`sB�F9F9ˁ4�p�!����$�N,�%`��#��A���H�H�"NDՈ���-�K�6"/��������OX�k����!��	�����e�>��c�rÐf�r�y�,t�>q�����a�a�>X�c�P8E��#�&:�Mp��pz"fñ�B>+b#�b�8��D�N}�t�pl�� �B��7;�g��R+�q�#���p&�����	n�����t�`)q�Y�L�؊J(�Gt�9�0��A����M����1��z�.I���d L��}�q�$9�����a��I��Øs������0�sa�(�Ør�0��Øu0��";��"?&9��:M���U|v\���툈���"-��#�"#����#�㎸�.=�|���
[��29�������iy��|���/F����,\]��)�5�""��G�(��Hru�����k������]{� � L���t�\���9��k�{���ɎF:�a�-�?��a��;�iÄe�a���C��u���C�>����Dk��w\|Gv�Ti��UI�H��H��X�X�c�P9���W�K~����\��	����DR�q�lD_A��na���#� �7����W��R����"��2`�Ù��Ð����g$9���$9��9�0� �8A9���a��wɎa��K0��!�p͇������G�D^��q�hk�8��'Z�%_�?��a�>g�������r�����s¡�|DE��,r1���r1�9�����������xp��k�"��"?�,��=�c��r(sB�aտ$9��1�9��ja�8Ai^ۓ�:�i^X�A�dq?����7�)b".�#X��#��v$=��i�H|��:o��}�o��2⴦�?��}�X���^a�1�:GR ���u)�#�">�V?��ҵm�i�A/����ƅG��i>Lr1�����&=���0��	�a�;���Øs�1�q�1�H�|��9��S>q�2�M���m/� �8�"8�ب����i$"7�v"5��X�؈�t4$G��a����t��~�?ݵ�}������;�D�C$9�o�<dn�`�Z�0��{!^�o��^������ЋCB#co0�a��ȃ�sa�1ܷb�t"�,�0�Ñ�a�8H��a�:��a���������B�ú#
F9'���
q�=�C�	����TX�G���""#�#B>"-�V#�w�v=��~E!G^���0G͠[!�@6�5ۆ�2�ҷ�k��[�Z�E���1�D��s" ��\�঄�A�r�[�i��û��K�����~�i"C��F9�F9�8�&�r1��0�"C�1�82�#��28��|�Ñ�A#��28#�x��C�c�@��Je�l�DDDDDDDDD[__�. ۡ��D�!G!��9xaʃ��(r.@�rc�d A����G�hM��"1��6Ads�����r
�r��s$9
9�0�c��a�9�Ð���r1�9�!G0�3�a��r1��0�Ør#�B�p&�|<BDDDDDDqDDqm#�W�\2AS��$�� ��8e�X���6��ʭ/��1�Q�g�Hi�aԆX�Ä��9��sa�9�0�������sF9C��r1��!G!G!G#�NF9��C\pˁ4��r
㑎A@�09�!�91�9w0�C4q!E��DDDq�1�>a��!�|�Clr1�8�8�Ørc���(�Ñ�A�0��a�9a�9�!��9�0��r�q ���"CTq,�0
�0�6�0�Ñ�B�F9
9�!\�w!�8A	1�9�!�Ă""%BLq
�������������<3�a�#�X�+�w0���sC8�c�r1�Q�Q�9�!G0�c�sa�9�0�Ñ��#Ð��sa�g�r(�Ør�#Ør#� s%a�g2�M�(��"!�&�r��r� �rs@�rsF9��s�""""""@�j�� �9
9��9��9�ØsC8�c��9�0���@���!G#����0�(����� \rp�\	�^@��w)�APS�s�Pw;���APT��A��w;���s���w;���s���g)��s��;���s���w;���s���w;���s���a��s9��w;�s�a��s��ㄎ��q���w;���8H�w;���Ä��q)�9�0�Øsa�9�0�$BLsF9�H �����9�P�P�"$�C�A���������I��*	-�U��*����u���������_�����������}U4�SM4Ӿ���;[[;��g{;���eA��w;���u;�����r���s���w;���s���w;���s���w;���s���w;���r��w;���s��3��s��Ù�9�3��9�B	B�A�B	$@��$A
$�H$"�A � �H �A@�	�$ �A� � �! � �A � �($�A�AA�h$�AAAA!AAA$A	H � �0�	 �H$L �$M�(!!!�AA�( T+���@���Ik�\q�����������^�������M4�M4�.�����}WUU[U��_��]�;���;�������]o����}5�j_.�­�/��Ǘ��L&w�� �$H$�E��@��� A0�AA � � � � � � � �IAA$AA0�AAA ��	��H �� �e@e���!!�DDEšwhZhZ�DZhi�kƂ?�4���}?[�����������_�W޾�㈈����������""""""""""""""""""""""""""""""""""""""""!�&[���r�!G#Øsa�`sa�`sA@��CHrsa�9
9
9
9㐣�s ��NG�pPG��H�#�x���#��p�p�p�H6���l�F9�a��r|G�>C�r�A�9�Ý�a�9�#�w#�a��Øsa�9�0�(��sX�Ør�0�09
9�#�sq�9�