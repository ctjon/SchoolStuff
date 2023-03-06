#!/usr/bin/perl -w
# sample.pl
# Written By: Chris Tjon
# sample code for using DBI
# 15 Oct 2004
#
#use strict;
use DBI;

my $database = 'tracker_db';
my $db_host = 'localhost';
my $db_port = '3306';
my $db_user = 'tracker_user';
my $db_passwd = 'password';


&select_all_users_sample;

sub select_all_users_sample
{
	my $db_handle; 
	my $sql_buf;
	my @rows;

	print ("setting up db_handle\n");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });

	
	print ("*****: TRUNCATE user_table;\n");
	$db_handle->do("TRUNCATE user_table;");

	print ("Doing: INSERT INTO users;\n");
	my $sql_fmt = ("INSERT INTO user_table VALUES('%s');");
	$sql_buf = sprintf($sql_fmt, "Chris");
	$db_handle->do($sql_buf);
	$sql_buf = sprintf($sql_fmt, "Kelly");
	$db_handle->do($sql_buf);
	$sql_buf = sprintf($sql_fmt, "James");
	$db_handle->do($sql_buf);

	print ("Doing: SELECT user FROM user_table;\n");
	$rows = $db_handle->selectall_arrayref("SELECT user FROM user_table;");
	foreach my $row (@$rows)
	{
		print ("@$row\n");
	}
	$db_handle->disconnect;
}
