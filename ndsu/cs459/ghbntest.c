#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
main()
{
	struct hostent *h;

	h = gethostbyname("hookie.cs.ndsu.nodak.edu");
	printf("%d %d %d %d %d %d\n", h->h_addrtype, h->h_length, x(*h->h_addr),
					x(*(h->h_addr+1)),
					x(*(h->h_addr+2)),
					x(*(h->h_addr+3)));
}

x(convert)
int convert;
{

	if (convert < 0) return (256 + convert ); else return(convert);
}
