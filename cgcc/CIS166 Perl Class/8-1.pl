#/usr/bin/perl -w
#
# CIS166 
# Chris Tjon
# 5 Nov 2004
#
use strict;

my @heap;

@heap = <DATA>;
print @heap;
@heap = &heap_sort(@heap);
print @heap;


sub pushdown
{
	my $child;
	my ($heap, $i) = @_;
	my $size = $heap->[0];
	while($i <= $size/2)
	{
		if ($child < $size and $heap->[$child])
		{
			$child++;
		}
		if ($heap->[$i] > $heap->[$child])
		{
			last;
		}
		($heap->[$i], $heap->[$child]) = ($heap->[$child], $heap->[$i]);
		$i = $child;
	}
}

sub heap_sort
{
	my $heap;
	my @heap = @_;
	my $size = scalar(@_);
	print ("size = [$size]\n");
	for (my $i = int($size / 2) - 1; $i >= 0; $i--)
	{
		print ("for1\n");
		&pushdown($heap, $i);
	}
	for (my $i = ($size - 1); $i >=1; $i--)
	{
		print ("for2\n");
		($heap->[1], $heap->[$i]) = ($heap->[$i], $heap->[1]);
		$size--;
		&pushdown($heap, 1);
	}
	shift @heap;
	return @heap;
}

__DATA__
9 9 8 7 6 5 4 3 2 1
