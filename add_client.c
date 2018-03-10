#include "add.h"

void
add_prog_1(char *host)
{
        int *result;
	CLIENT *clnt;
	intpair  add_1_arg;
        int a, b;
        printf("Enter first number: ");
        scanf("%d", &a);
        printf("Enter second number: ");
        scanf("%d", &b);
	add_1_arg.a = a;
	add_1_arg.b = b;


#ifndef	DEBUG
	clnt = clnt_create (host, ADD_PROG, ADD_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	result = add_1(&add_1_arg, clnt);
        printf("Result from executable: %d\n", *result);
	if (result == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	add_prog_1 (host);
exit (0);
}
