#!/usr/bin/perl -w
# cgi-bin/ice_cream V2
use CGI qw(:standard);
print header, start_html('Hello World'), h1('Hello, World!');
my $favorite = param("flavor");
print p("Your favorite flavor is $favorite.");
print end_html;
