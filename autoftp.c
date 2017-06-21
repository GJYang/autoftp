#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>


#define TRUE		1
#define FALSE		0

/* globals */
int verbose = FALSE;
int exec 	= FALSE;
int ls 		= FALSE;

char *cd = "";
char *cmd = "put";
char *userid = "root";
char *passwd = "root";
char *ipaddr = "127.0.0.1";
char *filename = "";

void check_args(int argc, char * const argv[], char **envp);

void print_usage(int argc, char * const argv[], char **envp) {
	fprintf(stderr, "Usage error\n");
	fprintf(stderr, "%s [-c|--cmd] [-i|--ip] [-u|--userid] [-p|--passwd] [-f|--filename] [-t|--targetdir] [-x|--execfile] [-l|--ls] [-v|--verbose] \n", argv[0]);
	fprintf(stderr, "where :\n");
	fprintf(stderr, "\t-c\t\"put\" or\"get\" [filename]\n");
	fprintf(stderr, "\t-t\tchange directory to [targetdir]\n");
	fprintf(stderr, "\t-x\tchmod +x [filename], to make executable file\n");
	fprintf(stderr, "\t-l\tlist\n");
	fprintf(stderr, "\tdefault: [-u|--userid] \t\"%s\"\n", userid);
	fprintf(stderr, "\t       \t [-p|--passwd]\t\"%s\"\n", passwd);
	fprintf(stderr, "\t       \t [-c|--cmd]\t\"%s\"\n", cmd);
	fprintf(stderr, "\t       \t [-i|--ipaddr]\t\"%s\"\n", ipaddr);
	fprintf(stderr, "\n");
	exit(1);
}

int main(int argc, char** argv, char **envp) {

	FILE* lftp;
	char lftp_open[256];

	check_args(argc, argv, envp);

	sprintf(lftp_open, "lftp -u %s,%s ftp://%s", userid, passwd, ipaddr);
	lftp = popen(lftp_open, "w");
	if(!lftp) {
		fprintf(stderr, "\033[%dm%s\033[0m\n", 91, "FTP : Failed to establish connection\n");
		return -1;
	} else {
		if(verbose) {
			fprintf(stderr, "FTP : Connection established\n");
		}
	}

	fprintf(lftp, "cd %s\n", cd);
	if(verbose) {
		fprintf(stderr, "cd %s\n", cd);
	}

	fprintf(lftp, "%s %s\n", cmd, filename);
	if(verbose) {
		fprintf(stderr, "%s %s\n", cmd, filename);
	}
	
	if(exec) {
		fprintf(lftp, "chmod +x %s\n", filename);
		if(verbose) {
			fprintf(stderr, "chmod +x %s\n", filename);
		}
	}
	if(ls) {
		fprintf(lftp, "ls \n");
	}


	pclose(lftp);
	if(verbose) {
		fprintf(stderr, "FTP : Closed\n");
	}
	return 0;
}

void check_args(int argc, char * const argv[], char **envp) {

	int opt;
	int index = 0;

	/* command line options */
	struct option options[] = {
		{"cmd"		, 1, 0 , 'c' },
		{"ip"		, 1, 0 , 'i' },
		{"userid"	, 1, 0 , 'u' },
		{"passwd"	, 1, 0 , 'p' },
		{"filename"	, 1, 0 , 'f' },
		{"targetdir", 1, 0 , 't' },
		{"execfile"	, 0, 0 , 'x' },
		{"ls"		, 0, 0 , 'l' },
		{"verbose"	, 0, 0 , 'v' },
		{0, 0, 0, 0}
	};

	if(argc < 4) {
		print_usage(argc, argv, envp);
	}

	while (1) {
		opt = getopt_long(argc, argv, "c:f:t:i:u:p:xlv", options, &index);

		if(opt == -1) break;

		switch (opt) {
		case 'c':
			if( NULL != optarg) {
				cmd = malloc( strlen( optarg)+1);
				memcpy( cmd, optarg, strlen(optarg)+1);
			}
			break;
		case 'i':
			if( NULL != optarg) {
			    ipaddr = malloc( strlen( optarg)+1);
			    memcpy( ipaddr, optarg, strlen(optarg)+1);
			}
			break;
		case 'u':
			if( NULL != optarg) {
			    userid = malloc( strlen( optarg)+1);
			    memcpy( userid, optarg, strlen(optarg)+1);
			}
			break;
		case 'p':
			if( NULL != optarg) {
			    passwd = malloc( strlen( optarg)+1);
			    memcpy( passwd, optarg, strlen(optarg)+1);
			}
			break;
		case 'f':
			if(NULL != optarg) {
				filename = malloc( strlen( optarg)+1);
				memcpy( filename, optarg, strlen(optarg)+1);
			}
			break;
		case 't':
			if(NULL != optarg) {
			    cd = malloc( strlen( optarg)+1);
			    memcpy( cd, optarg, strlen(optarg)+1);
			}
			break;
		case 'x':
			exec = TRUE;
			break;
		case 'l':
			ls = TRUE;
			break;
		case 'v':
			verbose = TRUE;
			break;
		default: 
			print_usage(argc, argv, envp);
			break;
		} /* end of switch (opt) */
	} /* end of while */
}
