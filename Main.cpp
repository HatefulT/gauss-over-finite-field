#include <stdio.h>

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void inputA(int A[][3]) {
  for(int i=0; i<3; i++)
    for(int j=0; j<3; j++)
      scanf("%d", &A[i][j]);
}
void inputB(int B[]) {
  for(int i=0; i<3; i++)
    scanf("%d", &B[i]);
}


// Какое число является решением уравнения n = mx (mod k)
int F(int n, int m, int k) {
  for(int i=1; i<k; i++)
    if((m*i) % k == n)
      return i;
  return 0;
}

void tmpPrint(int A[][3], int B[]) {
  for(int i=0; i<3; i++) {
    for(int j=0; j<3; j++)
      printf("%d ", A[i][j]);
    printf("%d\n", B[i]);
  }    
}

void gauss(int A[][3], int B[], int k) {
  int l;
  if(A[0][0] != 1) {
    printf("Домножаем первую строку чтобы получилась 1 в первом столбце\n");
    int l = F(1, A[0][0], k);
    A[0][0] = (A[0][0] * l) % k;
    A[0][1] = (A[0][1] * l) % k;
    A[0][2] = (A[0][2] * l) % k;
    B[0] = (B[0] * l) % k;
    tmpPrint(A, B);
  }
  printf("Терь вычитаем из 2 и 3 строки первую:\n");
  if(A[1][0] != 0) {
    int tmp = A[1][0];
    A[1][0] = (A[1][0] - tmp * A[0][0] + tmp*k) % k;
    A[1][1] = (A[1][1] - tmp * A[0][1] + tmp*k) % k;
    A[1][2] = (A[1][2] - tmp * A[0][2] + tmp*k) % k;
    B[1] = (B[1] - B[0]*tmp + tmp * k) % k;
  }
  if(A[2][0] != 0) {
    int tmp = A[2][0];
    A[2][0] = (A[2][0] - tmp * A[0][0] + tmp*k) % k;
    A[2][1] = (A[2][1] - tmp * A[0][1] + tmp*k) % k;
    A[2][2] = (A[2][2] - tmp * A[0][2] + tmp*k) % k;
    B[2] = (B[2] - B[0]*tmp + tmp * k) % k;
  }
  tmpPrint(A, B);

  if(A[1][1] == 0) {
    printf("Поменяем строки 2 3:\n");
    swap(&A[1][0], &A[2][0]);
    swap(&A[1][1], &A[2][1]);
    swap(&A[1][2], &A[2][2]);
    swap(&B[1], &B[2]);
    tmpPrint(A, B);
  }

  if(A[1][1] != 1) {
    printf("Домножим вторую строку чтобы получилась 1:\n");
    l = F(1, A[1][1], k);
    A[1][0] = (A[1][0] * l) % k;
    A[1][1] = (A[1][1] * l) % k;
    A[1][2] = (A[1][2] * l) % k;
    B[1] = (B[1] * l) % k;
    tmpPrint(A, B);
  }
  if(A[2][1] != 0) {
    printf("Вычитаем из 3 вторую:\n");
    int tmp = A[2][1];
    A[2][0] = (A[2][0] + tmp*(-A[1][0] +k)) % k;
    A[2][1] = (A[2][1] + tmp*(-A[1][1] +k)) % k;
    A[2][2] = (A[2][2] + tmp*(-A[1][2] +k)) % k;
    B[2] = (B[2] - tmp*B[1] + tmp*k) % k;
    tmpPrint(A, B);
  }
  
  if(A[2][2] != 1) {
    printf("Домножаем 3: \n");
    l = F(1, A[2][2], k);
    A[2][0] = (A[2][0]*l) % k;
    A[2][1] = (A[2][1]*l) % k;
    A[2][2] = (A[2][2]*l) % k;
    B[2] = (B[2] * l) % k;
    tmpPrint(A, B);
  }

  printf("Вычитаем чото из чегото: \n");
  int tmp = A[1][2];
  A[1][2] = 0;
  B[1] = (B[1] - tmp*B[2] + tmp * k) % k;
  tmp = A[0][2];
  A[0][2] = 0;
  B[0] = (B[0] - tmp*B[2] + tmp*k) % k;
  tmpPrint(A, B);

  printf("Еще чото:\n");
  tmp = A[0][1];
  A[0][1] = 0;
  B[0] = (B[0] - tmp * B[1] + tmp * k) % k;
  tmpPrint(A, B);
}

int main() {
  int A[3][3];
  int B[3];  
  int k;
  printf("Введите основую матрицу системы: ");
  inputA(A);
  tmpPrint(A, B);
  printf("Введите вектор свободных членов: ");
  inputB(B);
  tmpPrint(A, B);

  printf("Введите порядок поля Zk: ");
  scanf("%d", &k);
  gauss(A, B, k);
}
