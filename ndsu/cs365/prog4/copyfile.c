/******************************************************************************/
/* copy_file: routine to copy the contents of file 'src' to file 'dest'.      */
/******************************************************************************/
#include <sys/fcntl.h>
void copy_file (src, dest)
char *src, *dest;
{
	int srcfd, destfd, len;
	char buf[1024];

	srcfd = open (src, O_RDONLY);
	destfd = open (dest, O_WRONLY | O_CREAT, 0666);
	while ((len = read (srcfd, buf, 1024)) > 0)
		write (destfd, buf, len);
	close (srcfd);
	close (destfd);
};
