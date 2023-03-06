#!/usr/bin/perl -w
#
# Week 5 Program 1 (includes exercises 1-3)
# Chris Tjon
# 1 October 2004
#
# Recognition of integers, floats and exponents
# 
use strict;

my $is_integer = '^\d+$';
my $is_float = '^\d+\.\d+$';
my $is_scientific = '^\d+(e|E)\d+$';

while (<DATA>)
{
	chomp($_);
	if (/$is_integer/)
	{
		print ("Case 1: regular integer: FOUND![$_]******************\n");
	}
	else
	{
		print ("Case 1: regular integer: [$_] does not match\n");
	}
	if (/$is_float/)
	{
		print ("Case 2: floating point: FOUND![$_]******************\n");
	}
	else
	{
		print ("Case 2: floating point: [$_] does not match\n");
	}
	if (/$is_scientific/)
	{
		print ("Case 3: scientific notation: FOUND![$_]******************\n");
	}
	else
	{
		print ("Case 3: scientific notation: [$_] does not match\n");
	}
	print ("\n");
}


__DATA__
123
abc
a12c
1b3
11 3 a b 1
5e25
4E35
3.141592654
a.b.c
aeiou
3.4.5
