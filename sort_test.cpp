#include<iostream>
#include<vector>

void BubbleSort(int array[],int n)
{
    int i,j,temp;

    for (i = 0;i < n - 1;i++) {
        for (j = 0;j < n - 1;j++) {
            if (array[j + 1] < array[j]) {
                temp = array[j];array[j] = array[j + 1];array[j + 1] = temp;
            }
        }
    }
}

int main(void){
	int ar[10] = {2,5,1,9,6,0,7,6,4,3};
	int i = 0;

	BubbleSort(ar,10);


	while(i < 10){
		std::cout << ar[i] << " ";
		i++;
	}

	return 0;
}
