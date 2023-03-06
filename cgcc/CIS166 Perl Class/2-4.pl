#!/usr/bin/perl -w
# CIS166 Perl Programming
# Assignment 2, Problem 4
# Written By: Chris Tjon
# 8 Sept 2004
#
# Perform a "uniq -c" on a list of up to 20 numbers
#
use strict;
my %num_hash;
my $done = 0;
my $input = '';
my $count = 0;
my $value = '';
my $key = '';

print "Please enter up to 20 numbers one at a time\n";
print "Bad input will produce bad results!  More input checking required.\n";
while (($count < 20) && !$done)
{
	print "Please enter your number or press enter to finish -> ";
	chomp($input = <STDIN>);
	if ($input ne '')
	{
		$num_hash{$input}++;
	}
	else
	{
		$done = 1;
	} 
	$count++;
	
}
print "occurances of each input number:\n";
foreach $key (sort keys %num_hash)
{
	$value = $num_hash{$key};
	print "$key => $value\n";
}
