// See COPYING file for copyright and license details.
// Algorithm: https://www.cs.tufts.edu/comp/116/archive/fall2013/wclarkson.pdf

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sysexits.h>
#include <sys/wait.h>
#include <gmp.h>

#define DEF_TESTIME 1 /* seconds */
#define SQUARES_PER_CICLE 1000UL /* squares to do each cicle */
#define PRIME_LEN 512 /* prime bit length */
#define BASE10 10
#define BASE16 16

static FILE *input_file = NULL;
static FILE *output_file = NULL;
static unsigned long int time_enc, test_time = DEF_TESTIME;
static unsigned long int S;
static gmp_randstate_t random_gen;
static mpz_t n, fi_n;
static mpz_t Ck, b, a, e, t;

static void
usage(void)
{
	puts("Encrypts base 10 numerical data with time-lock algorithm.\n");
	puts("Usage: ./etlp [-h] [-v] [-t test_time] [-i input_data_file] [-o output_encrypted_data_file] solving_time");
	exit(EX_USAGE);
}

static void
setup(void)
{
	/* Initialize mpz_t global variables */
	mpz_init(n);
	mpz_init(fi_n);
	mpz_init(Ck);
	mpz_init(a);
	mpz_init(b);
	mpz_init(e);
	mpz_init(t);

	/* Setup gmp random generator */
	FILE *fp;
	unsigned long int random_seed;

	fp = fopen("/dev/urandom", "r");
	fscanf(fp, "%lu", &random_seed);
	fclose(fp);

	gmp_randinit_default(random_gen);
	gmp_randseed_ui(random_gen, random_seed);
}

// Obtain the modulus n and fi(n) by creating two big random prime numbers
// (p, q) and multiply them.
//
// n = p * q
// fi(n) = (p - 1) * (q - 1)
static void
gen_modulos(void)
{
	mpz_t p, q;
	mpz_init(p);
	mpz_init(q);

	mpz_urandomb(p, random_gen, PRIME_LEN);
	mpz_urandomb(q, random_gen, PRIME_LEN);

	mpz_nextprime(p, p);
	mpz_nextprime(q, q);

	mpz_mul(n, p, q);

	mpz_sub_ui(p, p, 1UL);
	mpz_sub_ui(q, q, 1UL);

	mpz_mul(fi_n, p, q);

	mpz_clear(p);
	mpz_clear(q);
}

/* Random base given this condition 1 < a < n */
static void
gen_base(void)
{
	mpz_urandomb(a, random_gen, PRIME_LEN*2);

	mpz_sub_ui(n, n, 2UL);
	mpz_mod(a, a, n);
	mpz_add_ui(n, n, 2UL);
	mpz_add_ui(a, a, 2UL);
}

/* Test performance to obtain squaring modulo n per second (S) */
static void
test_perf(void)
{
	unsigned long cicles = 0;
	clock_t t0, ticks, t_test;

	mpz_set(b, a);
	ticks = CLOCKS_PER_SEC * test_time;
	t0 = clock();
	t_test = t0 + ticks;
	do {
		mpz_set_ui(t, SQUARES_PER_CICLE);
		while(mpz_cmp_ui(t, 0) > 0) {
			mpz_powm_ui(b, b, 2UL, n);
			mpz_sub_ui(t, t, 1UL);
		}
		cicles++;
	} while(clock() < t_test);
	S = (unsigned long)((SQUARES_PER_CICLE * cicles)/test_time);
}

/* Encrypt efficiently by solving: Ck = k + b
 * b = a ^ e mod n
 * e = 2 ^ t mod fi_n */
static void
encrypt(void)
{
	mpz_t T, two, message;
	mpz_init(T);
	mpz_init(two);
	mpz_init(message);
	/* calculate challenge to reach desired time */
	mpz_set_ui(T, time_enc);
	mpz_mul_ui(t, T, S);

	/* calculate b */
	mpz_set_ui(two, 2UL);
	mpz_powm(e, two, t, fi_n);
	mpz_powm(b, a, e, n);

	/* get key from user */
	if(input_file) {
		gmp_fscanf(input_file, "%Zd", message);
	} else {
		puts("Enter data to encrypt (should be base 10 number):");
		gmp_scanf("%Zd", message);
	}

	/* encrypt key with b */
	mpz_add(Ck, b, message);
	
	mpz_clear(T);
	mpz_clear(two);
	mpz_clear(message);
}

static void
unsetup(void)
{
	if(input_file)
		fclose(input_file);
	if(output_file)
		fclose(output_file);
	mpz_clear(n);
	mpz_clear(fi_n);
	mpz_clear(Ck);
	mpz_clear(t);
	mpz_clear(a);
	mpz_clear(e);
	gmp_randclear(random_gen);
}

int
main (int argc, char *argv[])
{
	/* process input */
	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "-h"))
		{
			usage();
		}
		else if (!strcmp(argv[i], "-v")) 
		{
			puts("timelock v0.3");
			exit(EX_OK);
		} 
		else if (!strcmp(argv[i], "-t"))
		{
			test_time = strtoul(argv[++i], NULL, BASE10);
		}
		else if (!strcmp(argv[i], "-i")) 
		{
			input_file = fopen(argv[++i], "r");
			if (!input_file) {
				fprintf(stderr, "Error opening %s\n", argv[i]);
				exit(EX_NOINPUT);
			}
		}
		else if (!strcmp(argv[i], "-o")) 
		{
			output_file = fopen(argv[++i], "w");
			if (!output_file) {
				fprintf(stderr, "Error creating %s\n", argv[i]);
				exit(1);
			}
		}
		
	}

	time_enc = strtoul(argv[argc-1], NULL, BASE10);

	int hours = time_enc / 3600;
	int mins = (time_enc % 3600) / 60;
	int secs = (time_enc % 3600) % 60;

	setup();
	gen_modulos();
	gen_base();
	test_perf();

	printf("\nDecryption process is expected to take %i hours, %i minutes and %i seconds on this machine.\n", hours, mins, secs);

	encrypt();

//  Print Ck, a, t, n to stdout or output_file
	if (output_file)
	{		
		gmp_fprintf(output_file, "%Zd-%Zd-%Zd-%Zd-%d-%d-%d", Ck, a, t, n, hours, mins, secs);
	}
	else
	{
		printf("\nEncrypted message:\n\n");
		gmp_printf("%Zd-%Zd-%Zd-%Zd-%d-%d-%d\n\n", Ck, a, t, n, hours, mins, secs);
	}
	printf("You may want to consider deleting the original file containing now encrypted data (if one exists), your terminal history, your ClipIt history (if you use ClipIt and copied the data before its encryption) and emptying your Trash directory (Recycle Bin), if you want to ensure security of the encrypted data, in case someone with an intent to access original data has access to your computer.\n\n");

	unsetup();

	return 0;
}
