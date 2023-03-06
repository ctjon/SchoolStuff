#!/usr/bin/perl -w
#
# Week 5 Program 2
# Chris Tjon
# 1 October 2004
# Recognize and count vowels in a string
#
use strict;

my $is_vowel = '(a|e|i|o|u)';
my %vowels;
my $x;

while (<DATA>)
{
	chomp($_);
	$vowels{'a'} = 0;
	$vowels{'e'} = 0;
	$vowels{'i'} = 0;
	$vowels{'o'} = 0;
	$vowels{'u'} = 0;
	print("Checking string[$_]\n");
	while (/$is_vowel/gc)
	{
		$vowels{$1} += 1;
		#print ("Found Vowel [$1]\n");
	}
	foreach (sort keys %vowels)
	{
		print("[$_] was seen $vowels{$_} times\n");
	}
}


__DATA__
This is the winter of our discontent.
Th1s 1s th3 w1nt3r 0f 0Vr d1sc0nt3nt.
The rain in Spain falls mainly on the plain.
