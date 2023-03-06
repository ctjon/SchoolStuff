#!/usr/bin/perl -w
# CIS166 Perl Programming
# Assignment 2, Problem 3
# Written By: Chris Tjon
# 8 Sept 2004
#
# Reverse a list of up to 20 numbers
#
use strict;
my @num_list;
my @reverse_list;
my $done = 0;
my $input = '';
my $number = '';

print "Please enter up to 20 numbers one at a time\n";
print "Bad input will produce bad results!  More input checking required.\n";
while ((($#num_list +1) < 20) && !$done)
{
	print "Please enter your number or press enter to finish -> ";
	chomp($input = <STDIN>);
	if ($input ne '')
	{
		@num_list = (@num_list, $input);
	}
	else
	{
		$done = 1;
	}
	
}
@reverse_list = reverse(@num_list);
print "current number list is -> (@num_list)\n";
print "reversed number list is -> (@reverse_list)\n";

