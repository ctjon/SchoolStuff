#!/usr/bin/perl -w
use strict;

my @twod = undef;
my @buf = undef;
my $rows = 0;
my $columns = 0;
my $maxcols = 0;

while (<DATA>)
{
	chomp($_);
	@buf = split(/\s+/,$_);
	for($columns=0 ; $columns < @buf; $columns++)
	{
		$twod[$rows][$columns] = $buf[$columns];
	}
	if ($columns > $maxcols)
	{
		$maxcols = $columns;
	}
	$rows++;
}


print("Array Before Transposition\n");
&print_2darray($rows, $columns);
@twod = &transpose_2darray($rows, $columns);
print("Array After Transposition\n");
&print_2darray($rows, $columns);


# transpose two-dimensional array 
# requires a row and column parameter
sub transpose_2darray #(array, rows, columns)
{
	if (@_ != 2)
	{
		print("error, transpose_2darray requires 2 arguments!\n");
		return(-1);
	}
	my $rows = $_[0];
	my $columns = $_[1];
	my @temp = undef;
	for (my $i=0; $i < $rows; $i++)
	{
		for(my $j=0; $j < $columns; $j++)
		{
			$temp[$j][$i] = $twod[$i][$j];
		}
	}
	return(@temp);
}

# print two-dimensional array 
# requires a row and column parameter
sub print_2darray #(rows, columns)
{
	if (@_ != 2)
	{
		print("error, print_2darray requires 2 arguments!\n");
		return(-1);
	}
	my $rows = $_[0];
	my $columns = $_[1];
	for (my $i=0; $i < $rows; $i++)
	{
		for(my $j=0; $j < $columns; $j++)
		{
			print $twod[$i][$j], " ";
		}
		print("\n");
	}
}

__DATA__
1 2 3 4 5
6 7 8 9 10
11 12 13 14 15
16 17 18 19 20
21 22 23 24 25
