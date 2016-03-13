### 求灰度图的积分图
```
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
const int IMG_SIZE = 2400000;
const int IMG_WIDTH = 1500;
int main()
{
	printf("begin:\n");
	long start_seconds = time(0);
	unsigned int (*img)[IMG_WIDTH] = (unsigned int (*)[IMG_WIDTH]) new  unsigned int[IMG_WIDTH *IMG_WIDTH];

	for (int i = 0; i<IMG_WIDTH; i++) {
		for (int j = 0; j<IMG_WIDTH; j++) {
			img[i][j] = j;
		}
	}
	//求积分图
	for (int x = 1; x<IMG_WIDTH-10; x++) {
		img[0][x] += img[0][x - 1];
		img[x][0] = img[x - 1][0] + img[x][0];
	}
	for (int y = 1; y<IMG_WIDTH; y++) {
		for (int x = 1; x<IMG_WIDTH; x++) {
			int buff = 0;
			for (int i = 0; i <= x; i++) {
				buff += img[y][i];
			}
			img[y][x] = buff + img[y - 1][x];
		}
	}

	long end_seconds = time(0);

	printf("Max:%d\n , cost second:%d \n", img[IMG_WIDTH - 1][IMG_WIDTH - 1] , end_seconds - start_seconds);
	system("pause");

}
```
