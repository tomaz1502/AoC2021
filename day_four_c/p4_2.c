#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct board {
  int vals[5][5];
} board;

#define MARKED (-1)

size_t buf_size = 512;

int* strip_input(const char* input, int* len) {
  int* vals = (int*) malloc(sizeof(int) * 1);
  int capacity = 1;
  int current = 0;
  int pos = 0;
  for (int i = 0; ; i++) {
    if (input[i] < '0' || input[i] > '9') {
      if (pos >= capacity) {
        capacity *= 2;
        vals = (int*) realloc(vals, capacity * sizeof(int));
      }
      vals[pos] = current;
      pos++;
      current = 0;
      if (input[i] == '\n')
        break;
    } else {
      current *= 10;
      current += input[i] - '0';
    }
  }
  *len = pos;
  return vals;
}

board* read_board() {
  board* b = (board*) malloc(sizeof(board));

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (scanf("%d", &b->vals[i][j]) == -1)
        return NULL;
    }
  }

  return b;
}

short check_complete(board* b) {
  for (int i = 0; i < 5; i++) {
    short complete = 1;
    for (int j = 0; j < 5; j++)
      complete &= b->vals[i][j] == MARKED;
    if (complete)
      return 1;
  }

  for (int j = 0; j < 5; j++) {
    short complete = 1;
    for (int i = 0; i < 5; i++)
      complete &= b->vals[i][j] == MARKED;
    if (complete)
      return 1;
  }

  return 0;
}

int get_val(board* b) {
  int sum = 0;
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      if (b->vals[i][j] != MARKED)
        sum += b->vals[i][j];
  return sum;
}

int main() {
  char* input = (char*) malloc(sizeof(char) * buf_size);
  getline(&input, &buf_size, stdin);
  int num_vals;
  int* vals = strip_input(input, &num_vals);

  // first \n
  getchar();

  board* boards = (board*) malloc(sizeof(board) * 1);
  int capacity = 1;
  int num_boards = 0;

 while (1) {
   board* current = read_board();
   if (current == NULL)
     break;

   if (num_boards >= capacity) {
     capacity *= 2;
     boards = (board*) realloc(boards, capacity * sizeof(board));
   }

   getchar();
   boards[num_boards] = *current;
   num_boards++;
 }

  int answer = -1;
  int* gone = (int*) calloc(sizeof(int), num_boards);
  for (int iv = 0; iv < num_vals; iv++) {
    for (int ib = 0; ib < num_boards; ib++) {
      if (gone[ib])
        continue;
      for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
          if (boards[ib].vals[i][j] == vals[iv])
            boards[ib].vals[i][j] = MARKED;
        }
      }
      if (check_complete(&boards[ib]) == 1) {
        answer = get_val(&boards[ib]) * vals[iv];
        gone[ib] = 1;
      }
    }
  }

  printf("%d\n", answer);
  return 0;
}
