#!/usr/bin/perl -w
# CIS166 Perl Programming
# Assignment 2, Problem 1
# Written By: Chris Tjon
# 8 Sept 2004
#
# Convert pounds to kilograms.
#
use strict;
my $lbs = 0;
my $kgs = 0;

print "Please enter weight in pounds -> ";
chomp($lbs = <STDIN>);
$kgs = $lbs/2.2;
print "$lbs pounds is equivalent to $kgs kilograms\n";

