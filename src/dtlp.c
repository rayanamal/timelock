/* See COPYING file for copyright and license details. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <gmp.h>

#define BASE10 10

static void
usage(void)
{
	puts("Decrypts time-locked data encrypted with etlp.\n");
	puts("Usage: dtlp [-h] [-v] [-i input_encrypted_data_file] [-o output_decrypted_data_file]");
	exit(EX_USAGE);
}

/* Decrypt the key resolving the time lock puzzle */
int
main (int argc, char *argv[])
{
	FILE *input_file = NULL;
	FILE *output_file = NULL;
	mpz_t Ck, a, t, n, message;
	int hours = 0;
	int mins = 0;
	int secs = 0;

	/* process input */
	for (int i = 0; i < argc; i++)
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

	/* setup */
	mpz_init(Ck);
	mpz_init(a);
	mpz_init(t);
	mpz_init(n);
	mpz_init(message);


	if (input_file)
	{
		gmp_fscanf(input_file, "%Zd-%Zd-%Zd-%Zd-%d-%d-%d", Ck, a, t, n, &hours, &mins, &secs);
	}
	else
	{
		puts("Enter encrypted message to decrypt:");
		gmp_scanf("%Zd-%Zd-%Zd-%Zd-%d-%d-%d", Ck, a, t, n, &hours, &mins, &secs);
	}

	printf("Required time to decrypt: approximately %d hours, %d minutes and %d seconds.\n\nStarted decrypting. Please don't close this terminal window, and don't suspend, sleep or shutdown your computer.\n", hours, mins, secs);

	/* resolve time lock puzzle */
	while (mpz_cmp_ui(t, 0UL)) {
		mpz_powm_ui(a, a, 2UL, n);
		mpz_sub_ui(t, t, 1UL);
	}

	/* decrypt */
	mpz_sub(message, Ck, a);

	if (output_file)
	{		
		gmp_fprintf(output_file, "%Zd", message);
	}
	else
	{	
		printf("\nDecrypted message:\n\n");
		gmp_printf("%Zd\n\n", message);
	}

	/* unsetup */
	mpz_clear(Ck);
	mpz_clear(a);
	mpz_clear(t);
	mpz_clear(n);
	mpz_clear(message);

	if (input_file)
	{
		fclose(input_file);
	}

	if (output_file)
	{
		fclose(output_file);
	}

	return 0;
}
