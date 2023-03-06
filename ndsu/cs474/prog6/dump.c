/*
 * DUMP.C Written By: Chris Tjon NAID: 110975-8 For: CS474 Due: 30 October
 * 1992
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

char *get_modes(long inbuf);

void main(int argc, char *argv[])
{

    struct stat buf;
    if (argc != 2) printf("%s %s %s\n", "usage:", argv[0], "filename"), exit(1);

    if (lstat(argv[1], &buf) == -1) perror("stat"), exit(1);
    else
    {
	printf("Filename: [%s]\n", argv[1]);
	printf("device inode resides on: %d\n", buf.st_dev);
	printf("this inode's number: %d\n", buf.st_ino);
	printf("mode: %s\n", get_modes(buf.st_mode));
	printf("number of hard links to file: %d\n", buf.st_nlink);
	printf("UID of Owner: %d\n", buf.st_uid);
	printf("GID of Owner: %d\n", buf.st_gid);
	printf("Device Type: %d\n", buf.st_rdev);
	printf("Size of File in bytes: %d\n", buf.st_size);
	printf("Last accessed: %d\n", asctime(localtime(&buf.st_atime)));
	printf("Last modified: %s", asctime(localtime(&buf.st_mtime)));
	printf("Last stat change: %s", asctime(localtime(&buf.st_ctime)));
	printf("Optimal blocksize for fs i/o ops: %d\n", buf.st_blksize);
	printf("Actual number of blocks allowed: %d\n", buf.st_blocks);
    }
}

char *get_modes(long inbuf)
{
    long value;
    register int i;
    static char outbuf[200];
    static char *values[] = {"S_OEXEC", "S_OWRITE", "S_OREAD", "S_GEXEC",
                             "S_GWRITE", "S_GREAD", "S_IEXEC", "S_IWRITE",
                             "S_IREAD", "S_ISVTX", "S_ISGID", "S_ISUID"};

    outbuf[0] = 0;
    value = inbuf & 0xFFF;
    for (i = 0; value; i++)
    {
	if (value & 0x01) strcat(outbuf, values[i]), strcat(outbuf, "  ");
	value = value >> 1;
    }
    value = inbuf & 0x1F000;
    switch (value)
    {
    case S_IFMT:		/* 0170000 = type of file */
	strcat(outbuf, "S_IFMT"), break;
    case S_IFIFO:		/* 0010000 = fifo special */
	strcat(outbuf, "S_IFIFO"), break;
    case S_IFCHR:		/* 0020000 = character special */
	strcat(outbuf, "S_IFCHR"), break;
    case S_IFDIR:		/* 0040000 = directory */
	strcat(outbuf, "S_IFDIR"), break;
    case S_IFBLK:		/* 0060000 = block special */
	strcat(outbuf, "S_IFBLK"), break;
    case S_IFREG:		/* 0100000 = regular file */
	strcat(outbuf, "S_IFREG"), break;
    case S_IFLNK:		/* 0120000 = symbolic link */
	strcat(outbuf, "S_IFLNK"), break;
    case S_IFSOCK:		/* 0140000 = socket */
	strcat(outbuf, "S_IFSOCK"), break;
    default:			/* 0140000 = socket */
	strcat(outbuf, "UNDEFINED");
    }
    strcat(outbuf, "  ");
    return (outbuf);
}

