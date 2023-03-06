#!/usr/bin/perl
# cgi-bin/ice_cream V3
use CGI qw(:standard);
my $favorite = param("flavor");
print header, start_html('Hello Ice Cream'),
    h1('Hello Ice Cream');
if ($favorite) {
    print p("Your favorite flavor is $favorite.");
} else {
    print hr, start_form;   # hr() emits a horizontal rule
    print p("Please select a flavor: ", textfield("flavor", "mint"));
    print end_form, hr;
}
print end_html;
