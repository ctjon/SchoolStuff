#!/usr/bin/perl -w
#
# Midterm Program
# Chris Tjon
# 16 October 2004
#
use strict;
my %user_hash;

while (<DATA>)
{
	chomp;
	my ($user, $time) = split /:/;
	$user_hash{$user}[0] += $time;
	push (@{$user_hash{$user}}, $time);
}

foreach my $user (sort { $user_hash{$b}[0] <=> $user_hash{$a}[0] } keys %user_hash)
{
	my $total = shift(@{$user_hash{$user}});
	my @values = @{$user_hash{$user}};
	print ("$user - Total=$total Each: ", join(', ', @values), "\n");
}

#sub by_value { $user_hash{$user}} <=> $user_hash{$user}} }


__DATA__
Tiffany:10
Mark:30
Bryce:20
Tiffany:30
Fran:50
Mark:20
Tiffany:20
Bryce:5
Bryce:30
