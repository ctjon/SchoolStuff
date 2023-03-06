#!/usr/bin/perl -w
#
# CIS166
# Chris Tjon
# Program to create a report of the amount of time a users spend logged into a system
# Week 3 Homework 1
#
# Note that this program was designed on RedHat Linux.  It may not work on other platforms
# due to the system dependent nature of the output of the last command
#
# Sample output of the "last" command:
# chris    pts/0        server Wed Sep  1 14:59 - 22:45  (07:46) 
#
use strict;

my $inputfile = "/tmp/inputfile";
my $last_command = "/usr/bin/last";
my $system_cmd = "$last_command> $inputfile";

my @lines = undef;
my $line = undef;
my @fields;
my $username = undef;
my $session_time = undef;
my $time_in_sec = 0;
my %user_data;
my $min = 0;
my $sec = 0;

system('$system_cmd');

open INPUT_FILE, $inputfile or die "Cannot open input file [$inputfile]";
@lines = <INPUT_FILE>;
close INPUT_FILE;
chomp(@lines);


foreach $line (@lines)
{
	@fields = split(/\s+/, $line);
	# Eliminate lines regarding "Still logged in", "reboot", "wtmp begins..." or blanks
	if (($line ne "") and ($fields[0] ne "reboot") and ($fields[0] ne "wtmp") and ($fields[$#fields] ne "in"))
	{
		$username = $fields[0];
		$session_time = substr($fields[$#fields], -6, 5, ""); # grab the actual time value in hh:mm format

		$min = substr($session_time, 0, 2, "");
		$sec = substr($session_time, -2, 2, "");
		$time_in_sec = ($min * 60) + $sec;
		$user_data{$username} += $time_in_sec;
		$time_in_sec = 0;
	}
}

#
# Now that we have built the hash, print it out nicely!
#
foreach $username (sort keys %user_data)
{
	$min = $user_data{$username} / 60;
	$sec = $user_data{$username} % 60;
	printf("%s, %d:%2.2d\n", $username, $min, $sec);
}
