CREATE DATABASE tracker_db;
GRANT ALL ON tracker_db.* TO 'tracker_user'@'localhost';
GRANT ALL ON tracker_db.* TO 'tracker_user'@'apollo-rhdt';
SET PASSWORD FOR 'tracker_user'@'localhost' = PASSWORD('password');
SET PASSWORD FOR 'tracker_user'@'apollo-rhdt' = PASSWORD('password');
SELECT host,user FROM mysql.user;
