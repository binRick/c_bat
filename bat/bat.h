#pragma once
#ifndef BAT_H
#define BAT_H
//////////////////////////////////////
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//////////////////////////////////////
const char    *hl_bat_themes[] = {
  "1337",
  "Coldark-Cold",
  "Coldark-Dark",
  "DarkNeon",
  "Dracula",
  "GitHub",
  "Monokai Extended",
  "Monokai Extended Bright",
  "Monokai Extended Light",
  "Monokai Extended Origin",
  "Nord",
  "OneHalfDark",
  "OneHalfLight",
  "Solarized (dark)",
  "Solarized (light)",
  "Sublime Snazzy",
  "TwoDark",
  "Visual Studio Dark+",
  "ansi",
  "base16",
  "base16-256",
  "gruvbox-dark",
  "gruvbox-light",
  "zenburn",
};
static size_t hl_bat_themes_qty = (sizeof(hl_bat_themes) / sizeof(hl_bat_themes[0]));
struct hl_bat_options_t {
  bool          line_numbers, plain;
  char          *theme, *language, *file_name, *bat_path, *cmd, *path, *temp_path, *out_path, *bat_cmd, *command_line[32];
  int           highlight_line, highlight_line_start, highlight_line_end,
                diff_context, width, line_range_start, line_range_end;
  unsigned long ts;
};

struct hl_bat_options_t *hl_bat_new(void);
void hl_print_themes(void);
char *hl_bat(const char *path);
char *hl_bat_options(const char *path, struct hl_bat_options_t *);
void hl_bat_free(struct hl_bat_options_t *);
#endif
