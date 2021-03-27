
#include <iostream>

void quickSort(int[], int, int);//function prototyping


int main()
{
    int array[10] = { 5, 8, 3, 4, 8, 9, 2, 10, 1, 6 };
    quickSort(array, 0, 9);
    for (int i = 0; i <= 9; i++)
    {
        std::cout << array[i]<<"\n";
    }
}

void quickSort(int array[], int low, int high)
{
    if (high < low)
    {
        return;
    }
    int pivot = array[high];
    int jump = low;
    for (int i = low; i < high; i++)
    {
        if (array[i] <= pivot)
        {
            int temp;
            temp = array[i];
            array[i] = array[jump];
            array[jump] = temp;
            jump++;
        }
    }
    array[high] = array[jump];
    array[jump] = pivot;
    
  

    quickSort(array, low, jump - 1);
    quickSort(array, jump + 1, high);
}d


