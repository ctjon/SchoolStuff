#!/usr/bin/perl -w
#
# Week 6 Program 1 (includes exercises 1-3)
# Chris Tjon
# 9 October 2004
#
# Write a function that returns the list of the hash values sorted by the hash
# keys.  Write the same in one line using the map() function.
# 
use strict;

my %hash = (
	50 => "fifty",
	40 => "forty",
	30 => "thirty",
	20 => "twenty",
	10 => "ten"
	);

print("Sorting Hash with foreach loop function\n");
&sort_hash(%hash);
print("Sorting Hash with map function\n");
&map_sort_hash(%hash);
print("Sorting Hash with map function and >= 25\n");
&map_sort_hash_ge25(%hash);


sub sort_hash # (%hash)
{
	my %local_hash = @_;
	foreach my $key (sort keys %local_hash)
	{
		print("$key => $local_hash{$key}\n");
	}
}

sub map_sort_hash # (%hash)
{
	my %local_hash = @_;
	print(map{"$_ => $local_hash{$_}\n"} sort keys %local_hash);
}

sub map_sort_hash_ge25 # (%hash)
{
	my %local_hash = @_;
	print(map{("$_ => $local_hash{$_}\n") if ($_ >= 25)} sort keys %local_hash);
}
