#include <stdio.h>
int add(int a, int b) {
	return a + b;
}
void main() {
	int result = add(5, 10);
	printf("%d\n", result);
}