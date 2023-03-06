###################
{
	my $db_handle; 
	my $sql_buf;
	my @rows;

	&debug("dump_event_name_table: entered");
	$db_handle = DBI->connect("dbi:mysql:$database:$db_host:$db_port", $db_user, $db_passwd, { RaiseError => 1, AutoCommit => 1 });
	$sql_buf = "SELECT event_name FROM event_name_table;";
	&debug ("dump_event_name_table: \$sql_buf = [$sql_buf]");
	$rows = $db_handle->selectall_arrayref($sql_buf);
	foreach my $row (@$rows)
	{
		print ("EVENT: @$row\n");
	}
	$db_handle->disconnect;
	&debug("dump_event_name_table: done");
}

sub dump_time_record_table
###############################################################################
# DUMP_USER_TABLE: dumps the contents of the event record table to stdout     #
# REQUIRES: time_record_table exists                                          #
