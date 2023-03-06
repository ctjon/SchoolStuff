DELETE FROM mysql.user WHERE User='' AND Host='localhost';
DELETE FROM mysql.user WHERE User='' AND Host='apollo-rhdt';
SET PASSWORD FOR 'root'@'localhost' = PASSWORD('password');
SET PASSWORD FOR 'root'@'apollo-rhdt' = PASSWORD('password');
SELECT host,user FROM mysql.user;
