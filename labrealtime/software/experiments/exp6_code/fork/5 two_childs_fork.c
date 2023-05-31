 #include  <stdio.h>
#include  <unistd.h>

int print1toN(int n) {
	int j;
	for (j = 0; j < n; j++) {
		printf("%d\n", j);
	}
	//printf("\n");
}
int main() {
	printf("Please Enter two numbers\n");
	int N, M;
	scanf("%d%d", &N, &M);
	int i;

	if (fork() == 0) {  // The fork will return 0 for the child, and will return the child id for the parent 
		printf("In  the  chile1  process\n");
		int j;
		for (j = 0; j < N; j++) {
			printf("%d\n", j);
		}
		while (1)
			;
	} else { // parent
		if (fork() == 0) {
			printf("In  the  chile2  process\n");
			int j;
			for (j = 0; j < M; j++) {
				printf("%d\n", j);
			}
			while (1)
				;
		} else {
			printf("In  the  PARENT  process\n");
			while (1)
				;
		}

	}

	return 0;
}
