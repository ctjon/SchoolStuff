#!/usr/bin/perl
my $time = localtime(time);
print "Content-type: text/html\n\n";
print <<end_of_block
<HTML>
    <HEAD>
        <TITLE>Hello World</TITLE>
    </HEAD>
    <BODY>
    <H1>Greetings, Terrans!</H1>
    <P>The Time is $time
    </BODY>
</HTML>
end_of_block
