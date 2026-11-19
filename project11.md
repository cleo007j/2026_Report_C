# 1번 문제 scanf 보안
### 버퍼 오버플로 방지 기존 %[^\n]은 입력 길이를 제한하지 않아 100바이트를 넘는 문장이 들어오면 메모리 침범(오류/크래시)이 발생할 수 있습니다. %99[^\n]으로 널 문자(\0) 공간을 남기고 최대 입력 길이를 제한했습니다.
```
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(void) {
    char str[100];

    printf("문장 입력: ");
    // 배열 크기(100)를 넘지 않도록 최대 99글자까지만 입력받도록 폭 지정
    if (scanf("%99[^\n]", str) != 1) {
        printf("\n");
        return 0;
    }

    // 문자열 끝에서부터 거꾸로 한 글자씩 출력
    for (int i = (int)strlen(str) - 1; i >= 0; i--) {
        printf("%c", str[i]);
    }
    printf("\n");

    return 0;
}
```
# 2번 문제 함수의 포인터 
### void main() 대신 표준 C 규격인 int main(void)를 사용하고 return 0;을 추가해 컴파일러 경고를 줄였습니다.
```
#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int main(void) {
    int a = 11;
    int b = 22;
    int (*sum)(int, int) = add;

    printf("%d\n", sum(a, b));

    return 0;
}
```
# 3번 문제 2차원 배열
### 중첩 for문 중괄호 명시: 블록 범위를 명확히 해 실수 가능성을 줄였습니다.
```
#include <stdio.h>

int main(void) {
    int a[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    int s = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            s += a[i][j];
        }
    }

    printf("%d\n", s);

    return 0;
}
```
# 4번 문제  구조체로 2명의 3과목 성적을 생성해서 바이너리 형태로 my.bin에 저장해 줘
### 쓰기 결과 확인:요청한 구조체 2개가 정상적으로 기록되었는지 확인합니다.
### 파일 포인터 NULL 검사: fopen 실패 시 NULL 포인터를 fwrite에 넘기면 프로그램이 비정상 종료될 수 있으므로 예외 처리를 추가했습니다.
```
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct S {
    int k, e, m;
};

int main(void) {
    struct S a[2] = { {80, 90, 85}, {70, 75, 95} };
    FILE *p = fopen("my.bin", "wb");

    if (p == NULL) {
        perror("파일 열기 실패");
        return 1;
    }

    size_t written = fwrite(a, sizeof(struct S), 2, p);
    if (written != 2) {
        perror("파일 쓰기 실패");
        fclose(p);
        return 1;
    }

    fclose(p);
    return 0;
}
```
# 5번 문제 이 파일을 읽고 개인 평균, 과목 평균을 출력해 줘
### 표준 main 함수(int main(void)): void main() 대신 표준 int main(void)를 사용했고 return 0;을 추가했습니다.
```
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct S {
    int k, e, m;
};

int main(void) {
    struct S a[2];
    FILE *p = fopen("my.bin", "rb");
    fread(a, sizeof(struct S), 2, p);
    fclose(p);

    printf("개인1: %.2f, 개인2: %.2f\n", (a[0].k + a[0].e + a[0].m) / 3.0, (a[1].k + a[1].e + a[1].m) / 3.0);
    printf("과목1: %.2f, 과목2: %.2f, 과목3: %.2f\n", (a[0].k + a[1].k) / 2.0, (a[0].e + a[1].e) / 2.0, (a[0].m + a[1].m) / 2.0);

    return 0;
}
```
# 6번 문제 {2,4,1,5,3}을 버블 쇼팅해줘
### 배열 길이 변수 n 사용해서 고정 숫자(4, 5) 대신 sizeof(a) / sizeof(a[0])로 배열 길이를 계산해 반복문에 적용했습니다.
```
#include <stdio.h>

void main() {

int a[] = { 2, 4, 1, 5, 3 }, i, j, t;
int n = sizeof(a) / sizeof(a[0]);

for (i = 0; i < n - 1; i++)

for (j = 0; j < n - 1 - i; j++)

if (a[j] > a[j + 1]) {

t = a[j];

a[j] = a[j + 1];

a[j + 1] = t;

}

for (i = 0; i < n; i++)

printf("%d ", a[i]);

}
```
# 7번 문제 정수형 변수 2개에 각각 22와 33을 저장하고, 두 수의 합을 계산하여 화면에 출력하는 C언어 코드를 작성하시오.
### 합을 변수 대신 printf에서 바로 계산
```
#include <stdio.h>

int main(void) {
    int a = 22, b = 33;
    printf("%d\n", a + b);
    return 0;
}
```
# 8번 문제 명령행 인자(Command Line Arguments)로 두 정수를 입력받아 합을 출력하는 프로그램을 작성하시오.
### atoi 대신 strtol로 문자열을 정수로 변환
```
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("사용법: %s <정수1> <정수2>\n", argv[0]);
        return 1;
    }
    long a = strtol(argv[1], NULL, 10);
    long b = strtol(argv[2], NULL, 10);
    printf("%ld\n", a + b);
    return 0;
}
```
# 9번 문제 반복문(for 또는 while)을 사용하여 5부터 10까지의 정수를 모두 더한 결과를 화면에 출력하는 C언어 코드를 작성하시오.
### for문 대신 while문 사용
```
#include <stdio.h>

int main(void) {
    int sum = 0;
    int i = 5;
    while (i <= 10) {
        sum += i;
        i++;
    }
    printf("%d\n", sum);
    return 0;
}
```
# 10번 문제 동적 메모리 할당(malloc)을 활용하여 정수 3개 공간을 할당받은 뒤, {11, 33, 55}를 저장하고 이들의 합을 출력(해제 포함)하는 C언어 코드를 작성하시오
### sizeof(int) * 3 대신 calloc(3, sizeof(int))로 할당
```
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *p = (int *)calloc(3, sizeof(int));
    if (p == NULL) {
        return 1;
    }
    p[0] = 11;
    p[1] = 33;
    p[2] = 55;

    int sum = p[0] + p[1] + p[2];
    printf("%d\n", sum);

    free(p);
    return 0;
}
```
# 11번 문제 다음 3명의 성적(국어 kr, 영어 en)을 구조체로 초기화하고 개인별 평균을 구하시오. 대상:J.C. Shim, G.D. Hong, J.Y. Ko 
### 평균 계산을 별도 함수 get_avg로 분리
```
#include <stdio.h>

struct Score {
    const char *name;
    int kr;
    int en;
};

double get_avg(struct Score item) {
    return (item.kr + item.en) / 2.0;
}

int main(void) {
    struct Score s[3] = {
        {"J.C. Shim", 90, 80},
        {"G.D. Hong", 85, 95},
        {"J.Y. Ko", 100, 90}
    };

    for (int i = 0; i < 3; i++) {
        printf("%s: %.2f\n", s[i].name, get_avg(s[i]));
    }
    return 0;
}
```
