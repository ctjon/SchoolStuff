#!/usr/bin/perl -w
# CIS166 Perl Programming
# Assignment 2, Problem 2
# Written By: Chris Tjon
# 8 Sept 2004
#
# Calculates gross pay of an employee with regular and overtime hours.
#
#
use strict;
my $regular_hours = 0;
my $overtime_hours = 0;
my $hourly_wage = 0;
my $overtime_rate = 1.5;
my $gross_pay = 0;

print "What is the employee's hourly wage? -> ";
chomp($hourly_wage = <STDIN>);
print "How many regular hours did the employee work -> ";
chomp($regular_hours = <STDIN>);
print "How many overtime hours did the employee work -> ";
chomp($overtime_hours = <STDIN>);

$gross_pay = ($regular_hours * $hourly_wage) + ($overtime_hours * $hourly_wage * $overtime_rate);
print "The employee will receive a gross pay of \$$gross_pay\n";

