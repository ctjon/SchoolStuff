USE tracker_db;
CREATE TABLE user_table(user VARCHAR(32) NOT NULL PRIMARY KEY);
DESCRIBE user_table;
SHOW TABLES;
CREATE TABLE event_name_table(event_name VARCHAR(32) NOT NULL PRIMARY KEY);
SHOW TABLES;
DESCRIBE event_name_table;
CREATE TABLE time_record_table (
	event_name VARCHAR(32) NOT NULL,
	user VARCHAR(32) NOT NULL,
	problem_space CHAR(2) NOT NULL,
	event_date DATE NOT NULL,
	duration TINYINT(2) NOT NULL,
	event_type CHAR(2) NOT NULL);
ALTER TABLE time_record_table
	ADD CONSTRAINT event_name_constraint
	FOREIGN KEY event_name_fk(event_name)
	REFERENCES event_name_table(event_name)
	ON DELETE RESTRICT
	ON UPDATE CASCADE;
ALTER TABLE time_record_table
	ADD CONSTRAINT user_constraint
	FOREIGN KEY user_fk(user)
	REFERENCES user_table(user)
	ON DELETE RESTRICT
	ON UPDATE CASCADE;

