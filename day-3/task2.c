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

  unsigned long length = strlen(linev[0]) - 1; // Ignore newline

  // Oxygen Rating
  int ox_linec = linec;
  char **ox_linev = malloc(linec * sizeof(char *));
  memcpy(ox_linev, linev, linec * sizeof(char *));

  for (int i = 0; i < length; i++) {
    int zeros = 0;
    int ones = 0;

    for (int j = 0; j < ox_linec; j++) {
      if (ox_linev[j][i] == '0')
        zeros++;
      else if (ox_linev[j][i] == '1')
        ones++;
    }

    char ox_bit_criteria = (ones >= zeros) ? '1' : '0';

    for (int j = 0; j < ox_linec; j++) {
      if (ox_linev[j][i] != ox_bit_criteria) {
        memcpy(ox_linev + j, ox_linev + j + 1,
               (ox_linec - j - 1) * sizeof(char *));
        ox_linec--;
        j--;
      }
    }

    if (ox_linec == 1)
      break;
  }

  // CO2 Scrubber Rating
  int co2_linec = linec;
  char **co2_linev = malloc(linec * sizeof(char *));
  memcpy(co2_linev, linev, linec * sizeof(char *));

  for (int i = 0; i < length; i++) {
    int zeros = 0;
    int ones = 0;

    for (int j = 0; j < co2_linec; j++) {
      if (co2_linev[j][i] == '0')
        zeros++;
      else if (co2_linev[j][i] == '1')
        ones++;
    }

    char co2_bit_criteria = (ones < zeros) ? '1' : '0';

    for (int j = 0; j < co2_linec; j++) {
      if (co2_linev[j][i] != co2_bit_criteria) {
        memcpy(co2_linev + j, co2_linev + j + 1,
               (co2_linec - j - 1) * sizeof(char *));
        co2_linec--;
        j--;
      }
    }

    if (co2_linec == 1)
      break;
  }

  // Remove newlines
  ox_linev[0][length] = '\0';
  co2_linev[0][length] = '\0';

  // Final Scores
  printf("Oxygen Rating Bin: %s\n", ox_linev[0]);
  printf("CO2 Scrubber Rating Bin: %s\n", co2_linev[0]);
  long ox_dec = strtol(ox_linev[0], NULL, 2);
  long co2_dec = strtol(co2_linev[0], NULL, 2);
  printf("Oxygen Rating Decimal: %ld\n", ox_dec);
  printf("CO2 Scrubber Rating Decimal: %ld\n", co2_dec);

  printf("Life Support Rating: %ld\n", ox_dec * co2_dec);

  // Cleanup
  for (int i = 0; i < linec; i++) {
    free(linev[i]);
  }
  free(linev);
  return 0;
}
