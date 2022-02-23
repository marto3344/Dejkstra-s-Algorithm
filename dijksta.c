#include <stdio.h>
/* Максимален брой върхове в графа */
#define MAXN 150
#define MAX_VALUE 10000
#define NO_PARENT (unsigned)(-1)
/* Брой върхове в графа */
const unsigned n = 10;
const unsigned s = 1;
/* Матрица на теглата на графа */
const unsigned A[MAXN][MAXN] = {
 { 0, 23, 0, 0, 0, 0, 0, 8, 0, 0 },
 {23, 0, 0, 3, 0, 0, 34, 0, 0, 0 },
 { 0, 0, 0, 6, 0, 0, 0, 25, 0, 7 },
 { 0, 3, 6, 0, 0, 0, 0, 0, 0, 0 },
 { 0, 0, 0, 0, 0, 10, 0, 0, 0, 0 },
 { 0, 0, 0, 0, 10, 0, 0, 0, 0, 0 },
 { 0, 34, 0, 0, 0, 0, 0, 0, 0, 0 },
 { 8, 0, 25, 0, 0, 0, 0, 0, 0, 30 },
 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
 { 0, 0, 7, 0, 0, 0, 0, 30, 0, 0 }
};
char T[MAXN];
unsigned d[MAXN];
int pred[MAXN];
/* Алгоритъм на Дейкстра - минимален път от s до останалите върхове */
void dijkstra(unsigned s)
{ unsigned i;
 for (i = 0; i < n; i++) /* инициализиране: d[i]=A[s][i], iV, i != s */
 if (0 == A[s][i]) {
 d[i] = MAX_VALUE;
 pred[i] = NO_PARENT;
 }
 else {
 d[i] = A[s][i];
 pred[i] = s;
 }
 for (i = 0; i < n; i++) T[i] = 1; /* T съдържа всички върхове */
 T[s] = 0;
 pred[s] = NO_PARENT; /* от графа, с изключение на s */
 while (1) { /* докато T съдържа i: d[i] < MAX_VALUE */
 /* избиране на върха j от T, за който d[j] е минимално */
 unsigned j = NO_PARENT;
 unsigned di = MAX_VALUE;
 for (i = 0; i < n; i++)
 if (T[i] && d[i] < di) {
 di = d[i];
 j = i;
 }
 if (NO_PARENT == j) break; /* d[i] = MAX_VALUE, за всички i: изход */
 T[j] = 0; /* изключваме j от T */
 /* за всяко i от T изпълняваме D[i] = min (d[i], d[j]+A[j][i]) */
 for (i = 0; i < n; i++)
 if (T[i] && A[j][i] != 0)
 if (d[i] > d[j] + A[j][i]) {
 d[i] = d[j] + A[j][i];
 pred[i] = j;
 }
 }
}
void printPath(unsigned s, unsigned j)
{ if (pred[j] != s) printPath(s, pred[j]);
 printf("%u ", j+1);
}
/* Отпечатва намерените минимални пътища */
void printResult(unsigned s)
{ unsigned i;
 for (i = 0; i < n; i++) {
 if (i != s) {
 if (d[i] == MAX_VALUE)
 printf("Няма път между върховете %u и %u\n", s+1, i+1);
 else {
 printf("Минимален път от връх %u до %u: %u ", s+1, i+1, s+1);
 printPath(s, i);
 printf(", дължина на пътя: %u\n", d[i]);
 }
 }
 }
}
int main() {
 dijkstra(s-1); printResult(s-1);
}