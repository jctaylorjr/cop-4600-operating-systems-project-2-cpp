#ifndef ERROR_CHECK
#define ERROR_CHECK

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REQUIRED_ARG_COUNT 5
#define REQUIRED_ARG_COUNT_VMS 6

// colors from https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define argc_check_err(argc, argv)                                             \
	{                                                                      \
		required_argc_check((argc), (argv), __FILE__, __LINE__);       \
	}

#define mem_percent_check_err(p)                                               \
	{                                                                      \
		required_p_check((p), __FILE__, __LINE__);                     \
	}

#define file_check_err(infile)                                                 \
	{                                                                      \
		file_check((infile), __FILE__, __LINE__);                      \
	}

#define policy_check_err(policy)                                               \
	{                                                                      \
		policy_check((policy), __FILE__, __LINE__);                    \
	}

#define debug_mode_check_err(policy)                                           \
	{                                                                      \
		debug_mode_check((debug_mode), __FILE__, __LINE__);            \
	}

static inline void required_argc_check(int argc, const char *argv[],
				       const char *file, int line)
{
	int is_vms = 0;
	int required_arg_count = REQUIRED_ARG_COUNT;

	if (argc >= 5) {
		if (!strcmp(argv[3], "vms")) {
			required_arg_count = REQUIRED_ARG_COUNT_VMS;
			is_vms = 1;
		}
	}

	if (argc != required_arg_count) {
		fprintf(stderr,
			ANSI_COLOR_RED
			"Incorrect argument count! %s line %d\n%d args given, %d required\n" ANSI_COLOR_RESET,
			file, line, argc, required_arg_count);
		printf("Input takes the form of ");
		if (is_vms) {
			printf(ANSI_COLOR_YELLOW
			       "memsim <tracefile> <nframes> <lru|fifo|vms> <p> <debug|quiet>\n" ANSI_COLOR_RESET);
		} else {
			printf(ANSI_COLOR_YELLOW
			       "memsim <tracefile> <nframes> <lru|fifo|vms> <debug|quiet>\n" ANSI_COLOR_RESET);
		}
		printf(ANSI_COLOR_RED "Exiting process.\n" ANSI_COLOR_RESET);
		exit(EXIT_FAILURE);
	}
}

static inline void required_p_check(int p, const char *file, int line)
{
	if (p < 0 || p > 100) {
		fprintf(stderr,
			ANSI_COLOR_RED
			"Incorrect memory usage percent given! %s line %d\nvalue of %d given, acceptable range is 0-100\n" ANSI_COLOR_RESET,
			file, line, p);
		printf(ANSI_COLOR_RED "Exiting process.\n" ANSI_COLOR_RESET);
		exit(EXIT_FAILURE);
	}
}

// got perror code from https://stackoverflow.com/questions/14680232/how-to-detect-a-file-is-opened-or-not-in-c
static inline void file_check(FILE *infile, const char *file, int line)
{
	if (infile == NULL) {
		fprintf(stderr,
			ANSI_COLOR_RED
			"Trace file could not be accessed! %s line %d\n" ANSI_COLOR_RESET,
			file, line);
		perror(ANSI_COLOR_YELLOW "Failure" ANSI_COLOR_RESET);
		printf(ANSI_COLOR_RED "Exiting process.\n" ANSI_COLOR_RESET);
		exit(EXIT_FAILURE);
	}
}

static inline void policy_check(const char *policy, const char *file, int line)
{
	if (strcmp(policy, "fifo") && strcmp(policy, "lru") &&
	    strcmp(policy, "vms")) {
		fprintf(stderr,
			ANSI_COLOR_RED
			"Incorrect policy given! %s line %d\n" ANSI_COLOR_RESET,
			file, line);
		printf("Input takes the form of " ANSI_COLOR_YELLOW
		       "memsim <tracefile> <nframes> <lru|fifo|vms> <p [if vms used]> <debug|quiet>\n" ANSI_COLOR_RESET);
		printf(ANSI_COLOR_RED "Exiting process.\n" ANSI_COLOR_RESET);
		exit(EXIT_FAILURE);
	}
}

static inline void debug_mode_check(const char *debug_mode, const char *file,
				    int line)
{
	if (strcmp(debug_mode, "debug") && strcmp(debug_mode, "quiet")) {
		fprintf(stderr,
			ANSI_COLOR_RED
			"Incorrect debug mode given! %s line %d\n" ANSI_COLOR_RESET,
			file, line);
		printf("Input takes the form of " ANSI_COLOR_YELLOW
		       "memsim <tracefile> <nframes> <lru|fifo|vms> <p [if vms used]> <debug|quiet>\n" ANSI_COLOR_RESET);
		printf(ANSI_COLOR_RED "Exiting process.\n" ANSI_COLOR_RESET);
		exit(EXIT_FAILURE);
	}
}

#endif
