#!/usr/bin/perl -w
use 5.004;
use strict;            # enforce declarations and quoting
use CGI qw(:standard); # import shortcuts
use Fcntl qw(:flock);  # imports LOCK_EX, LOCK_SH, LOCK_NB

sub bail {             # function to handle errors gracefully
    my $error = "@_";
    print h1("Unexpected Error"), p($error), end_html;
    die $error;
}

my(
    $CHATNAME, # name of guestbook file
    $MAXSAVE,  # how many to keep
    $TITLE,    # page title and header
    $cur,      # new entry in the guestbook
    @entries,  # all cur entries
    $entry,    # one particular entry
);

$TITLE = "Simple Guestbook";
$CHATNAME = "/tmp/chatfile"; # wherever makes sense on your system
$MAXSAVE = 10;

print header, start_html($TITLE), h1($TITLE);

$cur = CGI->new();                         # current request
if ($cur->param("message")) {              # good, we got a message
    $cur->param("date", scalar localtime); # set to the current time
 @entries = ($cur);                        # save message to array
}

if ( -e $CHATNAME ) {
	# open the file for read-write (preserving old contents)
	open(CHANDLE, "+< $CHATNAME") || bail("cannot open $CHATNAME: $!");
} else {
	# open a new file for read-write
	open(CHANDLE, "+> $CHATNAME") || bail("cannot create $CHATNAME: $!");
}

# get exclusive lock on the guestbook (LOCK_EX == exclusive lock)
flock(CHANDLE, LOCK_EX) || bail("cannot flock $CHATNAME: $!");

# grab up to $MAXSAVE old entries, newest first
while (!eof(CHANDLE) && @entries < $MAXSAVE) {
    $entry = CGI->new(\*CHANDLE); # pass the filehandle by reference
    push @entries, $entry;
}
seek(CHANDLE, 0, 0) || bail("cannot rewind $CHATNAME: $!");
foreach $entry (@entries) {
    $entry->save(\*CHANDLE); # pass the filehandle by reference
}
truncate(CHANDLE, tell(CHANDLE)) || 
                                 bail("cannot truncate $CHATNAME: $!");
close(CHANDLE) || bail("cannot close $CHATNAME: $!");
print hr, start_form;         # hr() emits html horizontal rule: <HR>
print p("Name:", $cur->textfield(
    -NAME => "name"));
print p("Message:", $cur->textfield(
    -NAME => "message",
    -OVERRIDE => 1,           # clears previous message
    -SIZE => 50));
print p(submit("send"), reset("clear"));
print end_form, hr;

print h2("Prior Messages");
foreach $entry (@entries) {
    printf("%s [%s]: %s",
    $entry->param("date"),
    $entry->param("name"),
    $entry->param("message"));
    print br();
}
print end_html;