#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  FILE *inputs = fopen("inputs.txt", "r");
  if (!inputs) {
    printf("Error opening file!\n");
    return 1;
  }

  int linec = 0;
  char **linev = NULL;

  // Collect file lines into an array
  {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, inputs)) != -1) {
      linec++;
      linev = realloc(linev, linec * sizeof(char *));
      linev[linec - 1] = line;
      line = NULL;
    }
  }

  fclose(inputs);

  // Calculate rates
  unsigned long length = strlen(linev[0]) - 1; // Ignore newline
  char *gamma_rate = calloc(sizeof(char), length + 1);
  char *epsilon_rate = calloc(sizeof(char), length + 1);
  for (int i = 0; i < length; i++) {
    int zeros = 0;
    int ones = 0;

    for (int j = 0; j < linec; j++) {
      if (linev[j][i] == '0')
        zeros++;
      else if (linev[j][i] == '1')
        ones++;
    }

    gamma_rate[i] = (ones > zeros) ? '1' : '0';
    epsilon_rate[i] = (ones < zeros) ? '1' : '0';
  }

  // Final Scores
  printf("Gamma Rate Bin: %s\n", gamma_rate);
  printf("Epsilon Rate Bin: %s\n", epsilon_rate);
  long gamma_dec = strtol(gamma_rate, NULL, 2);
  long epsilon_dec = strtol(epsilon_rate, NULL, 2);
  printf("Gamma Rate Decimal: %ld\n", gamma_dec);
  printf("Epsilon Rate Decimal: %ld\n", epsilon_dec);

  printf("Score: %ld\n", gamma_dec * epsilon_dec);

  // Cleanup
  for (int i = 0; i < linec; i++) {
    free(linev[i]);
  }
  free(linev);
  return 0;
}
