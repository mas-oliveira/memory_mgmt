#pragma once

typedef struct SneklangVar {
  char *name;
  int value;
  int scope_level;
  char type;
  char is_constant;
} sneklang_var_t;
