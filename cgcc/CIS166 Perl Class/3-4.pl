#!/usr/bin/perl -w
# CIS166
# Chris Tjon
# subroutines to return the maximum and minimums of their arguement lists 
# using strings instead of numbers
# Week 3 Homework 4
#

my $max = undef;
my $min = undef;

$max = &max("jack", "joe", "john");
$min = &min("jack", "joe", "john");
print("Max = [", $max, "]\n");
print("Min = [", $min, "]\n");

sub max
{
	my $max_val = shift @_;
	foreach(@_)
	{
		if ($_ gt $max_val)
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
		if ($_ lt $min_val)
		{
			$min_val = $_;
		}
	}
	return($min_val);
}
