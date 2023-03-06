#!/usr/bin/perl -w
#
# Chris Tjon
# CIS166 Program 7
# 30 October 2004
#

use Net::Ping;
use strict;

my $host = 'sunshine';
my $p = Net::Ping->new();
if ($p->ping($host))
{
	print ("Host $host is Alive\n");
}
else
{
	print ("Host $host is Dead\n");
}
