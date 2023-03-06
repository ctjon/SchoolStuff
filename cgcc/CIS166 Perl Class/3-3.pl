#!/usr/bin/perl -w
#
# CIS166
# Chris Tjon
# subroutines to return the maximum and minimums of their arguement lists
# Week 3 Homework 3
#

my $max = undef;
my $min = undef;

$max = &max(1,2,3,4,5,6);
$min = &min(1,2,3,4,5,6);
print("Max = [", $max, "]\n");
print("Min = [", $min, "]\n");

sub max
{
	my $max_val = shift @_;
	foreach(@_)
	{
		if ($_ > $max_val)
		{
			$max_val = $_;
		}
	}
	return($max_val);
}

sub min
{
	my $min_val = shift @_;
	foreach(@_)
	{
		if ($_ < $min_val)
		{
			$min_val = $_;
		}
	}
	return($min_val);
}
