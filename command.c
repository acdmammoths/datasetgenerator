//
// command line help  & get arguments
//
#include <cstdlib>
#include <cstring>
#include "glob.h"
#include "gen.h"

extern char data_file[];
extern char pat_file[];
extern char tax_file[];

static bool userfile = false;

void exit_fail_with_msg(const char *str)
{
  cerr << str << endl;
  exit(EXIT_FAILURE);
}

void command_line(TaxPar &par)
{
  par.calc_values();

  cerr << "Command Line Options:" << endl;
  cerr << "  -ntrans number_of_transactions_in_000s (default: "
       << par.ntrans/1000 << ")" << endl;
  cerr << "  -tlen avg_items_per_transaction (default: " << par.tlen << ")" << endl;
  cerr << "  -nitems number_of_different_items_in_000s (default: "
       << par.nitems/1000 << ")" << endl;
  cerr << "  -nroots number_of_roots (default: " << par.nroots << ")" << endl;
  cerr << "  -nlevels number_of_different_levels (default: " << par.nlevels
       << ")" << endl;
  cerr << "  -fanout average_fanout (default: " << par.fanout << ")" << endl;
  cerr << "  -depth affects_average_depth_of_items_in_itemsets (default: "
    << par.depth_ratio << ")" << endl;
  cerr << endl;

  cerr << "  -npats number_of_patterns (default: " << par.lits.npats << ")" << endl;
  cerr << "  -patlen avg_length_of_maximal_pattern (default: "
       << par.lits.patlen << ")" << endl;
  cerr << "  -corr correlation_between_patterns (default: " << par.lits.corr
       << ")" << endl;
  cerr << "  -conf avg_confidence_in_a_rule (default: " << par.lits.conf
       << ")" << endl;
  cerr << endl;

  cerr << "  -fname <filename> (write to filename.data and filename.pat)" << endl;
  cerr << "  -ascii (Write data in ASCII format; default: " << (par.ascii? "True": "False") << ")" << endl;
  cerr << "  -randseed # (reset seed used generate to x-acts; must be negative)" << endl;
  cerr << "  -version (to print out version info)" << endl;
  exit(EXIT_FAILURE);
}


void command_line(TransPar &par)
{
  cerr << "Command Line Options:" << endl;
  cerr << "  -ntrans number_of_transactions_in_000s (default: "
       << par.ntrans/1000 << ")" << endl;
  cerr << "  -tlen avg_items_per_transaction (default: " << par.tlen << ")" << endl;
  cerr << "  -nitems number_of_different_items_in_000s) (default: "
       << par.nitems/1000 << ")" << endl;
  cerr << endl;

  cerr << "  -npats number_of_patterns (default: " << par.lits.npats << ")" << endl;
  cerr << "  -patlen avg_length_of_maximal_pattern (default: "
       << par.lits.patlen << ")" << endl;
  cerr << "  -corr correlation_between_patterns (default: " << par.lits.corr
       << ")" << endl;
  cerr << "  -conf avg_confidence_in_a_rule (default: " << par.lits.conf
       << ")" << endl;
  cerr << endl;

  cerr << "  -fname <filename> (write to filename.data and filename.pat)" << endl;
  cerr << "  -ascii (default: " << (par.ascii? "True": "False") << ")" << endl;
  cerr << "  -randseed # (reset seed used generate to x-acts; must be negative)" << endl;
  cerr << "  -version (to print out version info)" << endl;
  exit(EXIT_FAILURE);
}


void command_line(SeqPar &par)
{
  cerr << "Command Line Options:" << endl;
  cerr << "  -ncust number_of_customers_in_000s (default: "
       << par.ncust/1000 << ")" << endl;
  cerr << "  -slen avg_trans_per_customer (default: " << par.slen << ")" << endl;
  cerr << "  -tlen avg_items_per_transaction (default: " << par.tlen << ")" << endl;
  cerr << "  -nitems number_of_different_items_in_000s (default: "
       << par.nitems/1000 << ")" << endl;
  cerr << "  -rept repetition-level (default: " << par.rept << ")" << endl;
  cerr << endl;

  cerr << "  -seq.npats number_of_seq_patterns (default: " << par.lseq.npats
       << ")" << endl;
  cerr << "  -seq.patlen avg_length_of_maximal_pattern (default: "
       << par.lseq.patlen << ")" << endl;
  cerr << "  -seq.corr correlation_between_patterns (default: "
       << par.lseq.corr << ")" << endl;
  cerr << "  -seq.conf avg_confidence_in_a_rule (default: " << par.lseq.conf
       << ")" << endl;
  cerr << endl;

  cerr << "  -lit.npats number_of_patterns (default: " << par.lits.npats
       << ")" << endl;
  cerr << "  -lit.patlen avg_length_of_maximal_pattern (default: "
       << par.lits.patlen << ")" << endl;
  cerr << "  -lit.corr correlation_between_patterns (default: "
       << par.lits.corr << ")" << endl;
  cerr << "  -lit.conf avg_confidence_in_a_rule (default: " << par.lits.conf
       << ")" << endl;
  cerr << endl;

  cerr << "  -fname <filename> (write to filename.data and filename.pat)" << endl;
  cerr << "  -ascii (Write data in ASCII format; default: " << (par.ascii? "True": "False") << ")" << endl;
  cerr << "  -version (to print out version info)" << endl;
  exit(EXIT_FAILURE);
}


void cat_fname(const char *str1, const char *str2)
{
  if (userfile) return;
  
  ::strcat(data_file, str1);
  ::strcat(pat_file, str1);
  ::strcat(tax_file, str1);
  ::strcat(data_file, str2);
  ::strcat(pat_file, str2);
  ::strcat(tax_file, str2);
}


void get_args(TransPar &par, int argc, char **argv)
{
  LINT arg_pos = 2;
  
  strcpy(data_file, "data");
  strcpy(pat_file, "pat");
  strcpy(tax_file, "tax");
  while (arg_pos < argc)
    {
      if (strcmp(argv[arg_pos], "-ntrans") == 0) {
	// g++ lint !
	par.ntrans = LINT (1000 * atof(argv[++arg_pos]));
	cat_fname(".ntrans_", argv[arg_pos]);
	arg_pos++;
	if (par.ntrans < 1) exit_fail_with_msg("ntrans must be >= 1");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-tlen") == 0) {
	par.tlen = atof(argv[++arg_pos]);
	cat_fname(".tlen_", argv[arg_pos]);
	arg_pos++;
	if (par.tlen < 1) exit_fail_with_msg("tlen must be >= 1");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-nitems") == 0) {
	// g++ LINT I love you!!
	par.nitems = LINT (1000 * atof(argv[++arg_pos]));
	cat_fname(".nitems_", argv[arg_pos]);
	arg_pos++;
	if (par.nitems < 1) exit_fail_with_msg("nitems must be >= 1");
	continue;
      }

      else if (strcmp(argv[arg_pos], "-npats") == 0) {
	par.lits.npats = atoi(argv[++arg_pos]);
	cat_fname(".npats_", argv[arg_pos]);
	arg_pos++;
	if (par.lits.npats < 1) exit_fail_with_msg("npats must be >= 1");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-patlen") == 0) {
	par.lits.patlen = atof(argv[++arg_pos]);
	cat_fname(".patlen_", argv[arg_pos]);
	arg_pos++;
	if (par.lits.patlen <= 0) exit_fail_with_msg("patlen must be > 0");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-corr") == 0) {
	par.lits.corr = atof(argv[++arg_pos]);
	cat_fname(".corr_", argv[arg_pos]);
	arg_pos++;
	continue;
      }
      else if (strcmp(argv[arg_pos], "-conf") == 0) {
	par.lits.conf = atof(argv[++arg_pos]);
	cat_fname(".conf_", argv[arg_pos]);
	arg_pos++;
	if (par.lits.conf > 1 || par.lits.conf < 0) 
	  exit_fail_with_msg("conf must be between 0 and 1");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-fname") == 0) {
        strcpy(data_file, argv[++arg_pos]);
        strcat(data_file, ".data");
        strcpy(pat_file, argv[arg_pos++]);
        strcat(pat_file, ".pat");
        userfile = true;
	continue;
      }
      else if (strcmp(argv[arg_pos], "-ascii") == 0) {
	par.ascii = true;
	cat_fname(".ascii", "");
	arg_pos++;
	continue;
      }
      else if (strcmp(argv[arg_pos], "-randseed") == 0) {
	par.seed = atoi(argv[++arg_pos]);
	arg_pos++;
	if (par.seed >= 0)
	  exit_fail_with_msg("randseed must be negative");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-version") == 0) {
	cout << VERSION << endl;
	exit(EXIT_SUCCESS);
      }
      else {
	command_line(par);
      }
    }  // end while
}


void get_args(TaxPar &par, int argc, char **argv)
{
  LINT arg_pos = 2;
  
  strcpy(data_file, "data");
  strcpy(pat_file, "pat");
  strcpy(tax_file, "tax");
  while (arg_pos < argc)
    {
      if (strcmp(argv[arg_pos], "-ntrans") == 0) {
	// g++ LINT !!
	par.ntrans = LINT (1000 * atof(argv[++arg_pos]));
	cat_fname(".ntrans_", argv[arg_pos]);
	arg_pos++;
	if (par.ntrans < 1) exit_fail_with_msg("ntrans must be >= 1");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-tlen") == 0) {
	par.tlen = atof(argv[++arg_pos]);
	cat_fname(".tlen_", argv[arg_pos]);
	arg_pos++;
	if (par.tlen < 1) exit_fail_with_msg("tlen must be >= 1");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-nitems") == 0) {
	// g++ the LINT worm is back again! 
	par.nitems = LINT (1000 * atof(argv[++arg_pos]));
	cat_fname(".nitems_", argv[arg_pos]);
	arg_pos++;
	if (par.nitems < 1) exit_fail_with_msg("nitems must be >= 1");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-nroots") == 0) {
	par.nroots = atoi(argv[++arg_pos]);
	cat_fname(".nroots_", argv[arg_pos]);
	arg_pos++;
	if (par.nroots < 1) exit_fail_with_msg("nroots must be >= 1");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-nlevels") == 0) {
	par.nlevels = atof(argv[++arg_pos]);
	cat_fname(".nlevels_", argv[arg_pos]);
	arg_pos++;
	if (par.nlevels < 1) exit_fail_with_msg("nlevels must be >= 1");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-fanout") == 0) {
	par.fanout = atof(argv[++arg_pos]);
	cat_fname(".fanout_", argv[arg_pos]);
	arg_pos++;
	if (par.fanout < 1) exit_fail_with_msg("fanout must be >= 1");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-depth") == 0) {
	par.depth_ratio = atof(argv[++arg_pos]);
	cat_fname(".depth_", argv[arg_pos]);
	arg_pos++;
	if (par.depth_ratio <= 0) exit_fail_with_msg("fanout must be > 0");
	continue;
      }

      else if (strcmp(argv[arg_pos], "-npats") == 0) {
	par.lits.npats = atoi(argv[++arg_pos]);
	cat_fname(".npats_", argv[arg_pos]);
	arg_pos++;
	if (par.lits.npats < 1) exit_fail_with_msg("npats must be >= 1");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-patlen") == 0) {
	par.lits.patlen = atof(argv[++arg_pos]);
	cat_fname(".patlen_", argv[arg_pos]);
	arg_pos++;
	if (par.lits.patlen <= 0) exit_fail_with_msg("patlen must be > 0");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-corr") == 0) {
	par.lits.corr = atof(argv[++arg_pos]);
	cat_fname(".corr_", argv[arg_pos]);
	arg_pos++;
	continue;
      }
      else if (strcmp(argv[arg_pos], "-conf") == 0) {
	par.lits.conf = atof(argv[++arg_pos]);
	cat_fname(".conf_", argv[arg_pos]);
	arg_pos++;
	if (par.lits.conf > 1 || par.lits.conf < 0) 
	  exit_fail_with_msg("conf must be between 0 and 1");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-fname") == 0) {
        strcpy(data_file, argv[++arg_pos]);
        strcat(data_file, ".data");
        strcpy(pat_file, argv[arg_pos]);
        strcat(pat_file, ".pat");
        strcpy(tax_file, argv[arg_pos++]);
        strcat(tax_file, ".tax");
        userfile = true;
	continue;
      }
      else if (strcmp(argv[arg_pos], "-ascii") == 0) {
	par.ascii = true;
	cat_fname(".ascii", "");
	arg_pos++;
	continue;
      }
      else if (strcmp(argv[arg_pos], "-randseed") == 0) {
	par.seed = atoi(argv[++arg_pos]);
	arg_pos++;
	if (par.seed >= 0)
	  exit_fail_with_msg("randseed must be negative");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-version") == 0) {
	cout << VERSION << endl;
	exit(EXIT_SUCCESS);
      }
      else {
	command_line(par);
      }
    }  // end while

  par.calc_values();
}


void get_args(SeqPar &par, int argc, char **argv)
{
  LINT arg_pos = 2;
  
  strcpy(data_file, "data");
  strcpy(pat_file, "pat");
  strcpy(tax_file, "tax");
  while (arg_pos < argc)
    {
      if (strcmp(argv[arg_pos], "-ncust") == 0) {
	// g++ LINT LINT 
	par.ncust = LINT (1000 * atof(argv[++arg_pos]));
	cat_fname(".ncust_", argv[arg_pos]);
	arg_pos++;
	if (par.ncust < 1) exit_fail_with_msg("ntrans must be >= 1");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-slen") == 0) {
	par.slen = atof(argv[++arg_pos]);
	cat_fname(".slen_", argv[arg_pos]);
	arg_pos++;
	if (par.slen < 1) exit_fail_with_msg("slen must be >= 1");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-tlen") == 0) {
	par.tlen = atof(argv[++arg_pos]);
	cat_fname(".tlen_", argv[arg_pos]);
	arg_pos++;
	if (par.tlen < 1) exit_fail_with_msg("tlen must be >= 1");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-nitems") == 0) {
	// g++ LINT 
	par.nitems = LINT (1000 * atof(argv[++arg_pos]));
	cat_fname(".nitems_", argv[arg_pos]);
	arg_pos++;
	if (par.nitems < 1) exit_fail_with_msg("nitems must be >= 1");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-rept") == 0) {
	par.rept = atof(argv[++arg_pos]);
	cat_fname(".rept_", argv[arg_pos]);
	arg_pos++;
	if (par.rept < 0 || par.rept > 1) 
	  exit_fail_with_msg("repetition-level must be between 0 and 1");
	continue;
      }

      else if (strcmp(argv[arg_pos], "-seq.npats") == 0) {
	par.lseq.npats = atoi(argv[++arg_pos]);
	cat_fname(".seq.npats_", argv[arg_pos]);
	arg_pos++;
	if (par.lseq.npats < 1) exit_fail_with_msg("npats must be >= 1");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-seq.patlen") == 0) {
	par.lseq.patlen = atof(argv[++arg_pos]);
	cat_fname(".seq.patlen_", argv[arg_pos]);
	arg_pos++;
	if (par.lseq.patlen <= 0) exit_fail_with_msg("patlen must be > 0");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-seq.corr") == 0) {
	par.lseq.corr = atof(argv[++arg_pos]);
	cat_fname(".seq.corr_", argv[arg_pos]);
	arg_pos++;
	continue;
      }
      else if (strcmp(argv[arg_pos], "-seq.conf") == 0) {
	par.lseq.conf = atof(argv[++arg_pos]);
	cat_fname(".seq.conf_", argv[arg_pos]);
	arg_pos++;
	if (par.lseq.conf > 1 || par.lseq.conf < 0) 
	  exit_fail_with_msg("conf must be between 0 and 1");
	continue;
      }

      else if (strcmp(argv[arg_pos], "-lit.npats") == 0) {
	par.lits.npats = atoi(argv[++arg_pos]);
	cat_fname(".lit.npats_", argv[arg_pos]);
	arg_pos++;
	if (par.lits.npats < 1) exit_fail_with_msg("npats must be >= 1");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-lit.patlen") == 0) {
	par.lits.patlen = atof(argv[++arg_pos]);
	cat_fname(".lit.patlen_", argv[arg_pos]);
	arg_pos++;
	if (par.lits.patlen <= 0) exit_fail_with_msg("patlen must be > 0");
	continue;
      }
      else if (strcmp(argv[arg_pos], "-lit.corr") == 0) {
	par.lits.corr = atof(argv[++arg_pos]);
	cat_fname(".lit.corr_", argv[arg_pos]);
	arg_pos++;
	continue;
      }
      else if (strcmp(argv[arg_pos], "-lit.conf") == 0) {
	par.lits.conf = atof(argv[++arg_pos]);
	cat_fname(".lit.conf_", argv[arg_pos]);
	arg_pos++;
	if (par.lits.conf > 1 || par.lits.conf < 0) 
	  exit_fail_with_msg("conf must be between 0 and 1");
	continue;
      }

      else if (strcmp(argv[arg_pos], "-fname") == 0) {
        strcpy(data_file, argv[++arg_pos]);
        strcat(data_file, ".data");
        strcpy(pat_file, argv[arg_pos]);
        strcat(pat_file, ".pat");
        strcpy(tax_file, argv[arg_pos++]);
        strcat(tax_file, ".tax");
        userfile = true;
	continue;
      }
      else if (strcmp(argv[arg_pos], "-ascii") == 0) {
	par.ascii = true;
	cat_fname(".ascii", "");
	arg_pos++;
	continue;
      }
      else if (strcmp(argv[arg_pos], "-version") == 0) {
	cout << VERSION << endl;
	exit(EXIT_SUCCESS);
      }
      else {
	command_line(par);
      }
    }  // end while
}
