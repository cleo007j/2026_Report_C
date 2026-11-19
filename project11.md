# 1번 문제
### 버퍼 오버플로 방지
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
# 2번 문제
