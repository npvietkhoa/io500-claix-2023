#include <sys/stat.h>
#include <unistd.h>

#include <io500-phase.h>
#include <phase_mdtest.h>

typedef struct{
  opt_mdtest_generic g;
  mdtest_generic_res res;
} opt_mdtest_hard_write;

static opt_mdtest_hard_write o;

static ini_option_t option[] = {
  {"API", "The API to be used", 0, INI_STRING, "POSIX", & o.g.api},
  {"posix.odirect", "Use ODirect", 0, INI_BOOL, NULL, & o.g.odirect},
  {"noRun", "Disable running of this phase", 0, INI_BOOL, NULL, & o.g.no_run},
  {NULL} };


static void validate(void){

}

static double run(void){
  u_argv_t * argv = u_argv_create();
  mdtest_hard_add_params(argv);
  u_argv_push(argv, "-C");
  u_argv_push(argv, "-W");
  u_argv_push_printf(argv, "%d", opt.stonewall);

  opt_mdtest_hard d = mdtest_hard_o;
  mdtest_add_generic_params(argv, & d.g, & o.g);

  if(opt.dry_run || o.g.no_run  == 1 || mdtest_hard_o.g.no_run == 1){
    u_argv_free(argv);
    return 0;
  }

  FILE * out = u_res_file_prep(p_mdtest_hard_write.name);
  p_mdtest_run(argv, out, & o.res, MDTEST_FILE_CREATE_NUM);

  PRINT_PAIR("rate-stonewall", "%f\n", o.res.rate_stonewall);
  return o.res.rate;
}

u_phase_t p_mdtest_hard_write = {
  "mdtest-hard-write",
  option,
  validate,
  run,
  .verify_stonewall = 1,
  .group = IO500_SCORE_MD
};
