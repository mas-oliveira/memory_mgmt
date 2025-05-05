#include "exercise.h"

void concat_strings(char *str1, const char *str2) {
  int end_pos_str1;
  for (int i = 0; ; i++) {
    if (str1[i] == '\0') {
      end_pos_str1 = i;
      break;
    }
  }
  for (int j = 0; ; j++) {
    if (str2[j] == '\0') {
      str1[end_pos_str1 + j] = '\0';
      break;
    }
    str1[end_pos_str1 + j] = str2[j];
  }  
}
