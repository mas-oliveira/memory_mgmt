void swap_strings(char **a, char **b) {
  char *tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}
