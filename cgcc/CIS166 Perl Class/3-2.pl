#!/usr/bin/perl -w
#
# CIS166
# Chris Tjon
# subroutine to return the sum of all its arguements
# Week 3 Homework 2
#

my $sum = 0;

$sum = &sum(1,2,3,4,5,6);
print("Total = [", $sum, "]\n");

sub sum
{
	my $total = 0;
	foreach(@_)
	{
		$total += $_; 
	}
	return($total);
}
