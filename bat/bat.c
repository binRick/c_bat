#pragma once
#ifndef BAT_C
#define BAT_C
#define LOCAL_DEBUG_MODE    BAT_DEBUG_MODE
////////////////////////////////////////////
#include "bat/bat.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "reproc/export.h"
#include "reproc/reproc.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
#include "which/src/which.h"
static char *hl_reproc_bat(const char *cmd);
////////////////////////////////////////////
static bool       BAT_DEBUG_MODE = false;
///////////////////////////////////////////////////////////////////////
static const char *BAT_FIND_PATH = "/usr/local/bin:/usr/bin";

void hl_print_themes(void){
  for (size_t i = 0; i < hl_bat_themes_qty; i++)
    fprintf(stdout, "%s\n", hl_bat_themes[i]);
  exit(EXIT_SUCCESS);
}

char *hl_bat_options(const char *path, struct hl_bat_options_t *o){
  return(hl_reproc_bat(o->bat_cmd));
}

void hl_bat_free(struct hl_bat_options_t *o){
  if (o->bat_path)
    free(o->bat_path);
  if (o)
    free(o);
  return;
}

struct hl_bat_options_t *hl_bat_new(void){
  struct hl_bat_options_t *o = calloc(1, sizeof(struct hl_bat_options_t));

  o->temp_path = gettempdir();
  o->ts        = timestamp();
  char *PATH = getenv("PATH");

  setenv("PATH", BAT_FIND_PATH, 1);
  o->bat_path = which("bat");
  setenv("PATH", PATH, 1);
  if (!o->bat_path || !fsio_file_exists(o->bat_path)) {
    log_error("Unable to find bat in path %s", BAT_FIND_PATH);
    exit(EXIT_FAILURE);
  }
  asprintf(&o->out_path, "%s%ld", o->temp_path, o->ts);
  o->theme = hl_bat_themes[0];
  asprintf(&o->bat_cmd, "%s --color=always --decorations=always --italic-text=always --paging=never --theme=%s \"%s\"",
           o->bat_path,
           o->theme,
           o->path
           );
  return(o);
}

static char *hl_reproc_bat(const char *cmd){
  char *outfile, *out;

  asprintf(&outfile, "%s%lld", gettempdir(), timestamp());
  const char *command_line[] = { "/bin/sh", "--norc", "--noprofile", "-c", cmd, NULL };
  reproc_t   *process        = NULL;
  int        r               = REPROC_ENOMEM;
  int        ec              = 0;

  errno = 0;
  if (!(process = reproc_new())) {
    ec = 100;
    goto finish;
  }
  errno = 0;
  if ((r = reproc_start(process, command_line, (reproc_options){
    .redirect.parent = false,
    .deadline = 5000,
    .redirect.path = outfile,
  })) < 0) {
    ec = 200;
    goto finish;
  }
  errno = 0;
  if ((r = reproc_wait(process, REPROC_INFINITE)) < 0) {
    ec = 300;
    goto finish;
  }
finish:
  reproc_destroy(process);
  if (r != 0) {
    log_error(AC_RED "Error Code: %d" AC_RESETALL "\n", ec);
    log_error(AC_RED "%d" AC_RESETALL "\n", r);
    log_error(AC_RED "%s" AC_RESETALL "\n", reproc_strerror(r));
  }else{
    out = fsio_read_text_file(outfile);
    fsio_remove(outfile);
    free(outfile);
    return(out);
  }
} /* hl_reproc_bat */

char *hl_bat(const char *path){
  char *out;
  char *outfile;

  asprintf(&outfile, "%s%lld", gettempdir(), timestamp());
  char *PATH = getenv("PATH");

  setenv("PATH", BAT_FIND_PATH, 1);
  char *bat_path = which("bat");

  setenv("PATH", PATH, 1);
  if (!bat_path || !fsio_file_exists(bat_path)) {
    log_error("Unable to find bat in path %s", BAT_FIND_PATH);
    exit(EXIT_FAILURE);
  }
  if (!fsio_file_exists(path)) {
    log_error("File '%s' does not exist", path);
    exit(EXIT_FAILURE);
  }
  const
  char *c, *theme = hl_bat_themes[0];

  asprintf(&c, "%s --color=always --decorations=always --italic-text=always --paging=never --theme=%s \"%s\"",
           bat_path,
           theme,
           path
           );
  const char *command_line[] = { "/bin/sh", "--norc", "--noprofile", "-c", c, NULL };
  reproc_t   *process        = NULL;
  int        r               = REPROC_ENOMEM;
  int        ec              = 0;

  errno = 0;
  if (!(process = reproc_new())) {
    ec = 100;
    goto finish;
  }
  errno = 0;
  if ((r = reproc_start(process, command_line, (reproc_options){
    .redirect.parent = false,
    .deadline = 5000,
    .redirect.path = outfile,
  })
       ) < 0) {
    ec = 200;
    goto finish;
  }
  errno = 0;
  if ((r = reproc_wait(process, REPROC_INFINITE)) < 0) {
    ec = 300;
    goto finish;
  }
finish:
  reproc_destroy(process);
  if (r != 0) {
    log_error(AC_RED "Error Code: %d" AC_RESETALL "\n", ec);
    log_error(AC_RED "%d" AC_RESETALL "\n", r);
    log_error(AC_RED "%s" AC_RESETALL "\n", reproc_strerror(r));
  }else{
    out = fsio_read_text_file(outfile);
    size_t len = fsio_file_size(outfile);
    fsio_remove(outfile);
    return(out);
  }
} /* hl_bat */
static void __attribute__((constructor)) __constructor__bat(void){
  if (getenv("DEBUG") != NULL || getenv("DEBUG_bat") != NULL) {
    log_debug("Enabling bat Debug Mode");
    BAT_DEBUG_MODE = true;
  }
}
////////////////////////////////////////////
#undef LOCAL_DEBUG_MODE
#endif
