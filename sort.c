#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void selectionSort(void *arr, size_t length, size_t nByte, int (*cmp) (void *a, void *b));
void insertionSort(void *arr, size_t length, size_t nByte, int (*cmp) (void *a, void *b));
void inPlaceHeapSort(void *arr, size_t length , size_t nByte, int (*cmp) (void *a , void *b));
void *mergeSort(void *arr, size_t length, size_t nByte , int (*cmp) (void *a, void *b) );

int intCmp(void *a, void *b);
void swap(void *a, void *b, size_t nByte);
void* merge(void *arr1, void *arr2, size_t length1, size_t length2, size_t nByte, int (*cmp)(void *a, void *b));


void printInt(void *a);
void printArr(void *arr, size_t length, size_t nByte, void (*print)(void *a));

#define L 10
#define l1 4
#define l2 7

int main( int argc , char *argv[]) {
    
    
    int arr[L] = {5,7,8,10,11,16,3,1,0,7};

    int* output = (int*) mergeSort(arr, L , sizeof(int), intCmp);

    //printArr(arr, L , sizeof(int), printInt);
    printArr(output, L , sizeof(int), printInt);
    /* 
    int arr1[l1] = {4,3,2,1};

    int* output = (int*) mergeSort(arr1, l1, sizeof(int), intCmp);
    printArr(output, l1, sizeof(int), printInt);
    free(output);
    */
}

/*
 * Sorting Functions
 */

void selectionSort(void *arr, size_t length, size_t nByte, int (*cmp) (void *a, void *b)) {

    for (int i = 0; i < length; i++) {

        void *min = (char*)arr + i*nByte;

        for (int j = i; j< length; j++) {

            if (cmp ( min , (char *)arr + j*nByte   ) > 0 ) {
                min = (char *)arr + j*nByte;
            }
        }

        swap(min, (char *)arr + i*nByte, nByte);

    }

}

void insertionSort(void *arr, size_t length, size_t nByte, int (*cmp) (void *a, void *b)) {

    for (int i = 1; i < length ; i++) {

        for (int j = i ; j> 0 ; j--) {
            if ( cmp( (char *)arr + nByte*j , (char*)arr + nByte*(j-1) ) < 0) {
                
                swap( (char*)arr + nByte*j , (char*)arr+ nByte*(j-1) , nByte);

            }
            else {
                break;
            }
        }

    }

}

void inPlaceHeapSort(void *arr, size_t length , size_t nByte, int (*cmp) (void *a , void *b)) {
        
    // Forming a heap 
    for (int i = (length + 1)/2 ; i >= 1 ; i--) {
        
        // i is in the heap order
        // length + 1 is in the heap order

        while (i <= length/2) {
    
            if ( 2*i < length + 1 && 2*i + 1 < length + 1 ) { // has 2 child
                
                void *leftChild = (char *)arr + (2*i -1)*nByte;
                void *rightChild = (char *)arr + (2*i + 1 -1)*nByte;
                void *parent = (char *)arr + (i -1)*nByte;
                
                if ( cmp(leftChild, parent) > 0 && cmp(leftChild, rightChild) >= 0 ) {
                    swap(leftChild, parent, nByte);
                    i = 2*i;
                    continue;
                }
                if ( cmp (rightChild, parent) > 0 && cmp(rightChild, leftChild) >= 0) {
                    swap(rightChild, parent, nByte);
                    i = 2*i+1;
                    continue;
                }
                break;
            }
            else if ( 2*i < length +1 && 2*i + 1 >= length +1) { // has 1 child
                
                void *leftChild = (char *)arr + (2*i -1)*nByte;
                void *parent = (char*)arr + (i-1)*nByte;

                if ( cmp(leftChild, parent) > 0) {
                    swap(leftChild, parent, nByte);
                    i = 2*i;
                    continue;
                }
                break;
            }
            else if ( 2*i >= length +1 && 2*i+1 >= length +1) {
                break;
            }

        }

    }
    /*
    printf("Printing the array\n"); 
    printArr(arr, length, nByte, printInt);
    printf("Process to sort\n"); 
    */
    // Sorting the array
    
    int heapSize = length + 1;

    for (int i = 0; i < length  ; i++) {

        void *firstElem = arr;
        void *lastElem = (char*)arr + (heapSize-2)*nByte;

        swap(firstElem, lastElem, nByte);
        
        /*
        printf("Deneme basımı: %d \n", i);
        printArr(arr, length, nByte, printInt);
        printf("******" );
        */

        // i is in the heap order
        // length + 1 is in the heap order

        heapSize--;
        int j = 1;
        while ( j <= (heapSize-1)/2 ) {
            
            if ( 2*j < heapSize && 2*j +1 < heapSize) {
                
                void *leftChild = (char*)arr+ (2*j -1)*nByte;
                void *rightChild = (char*)arr+ (2*j + 1 -1)*nByte;
                void *parent = (char*)arr + (j-1)*nByte;
                
                if ( cmp(leftChild, parent) > 0 && cmp(leftChild, rightChild) >= 0 ) {
                    swap(leftChild, parent, nByte);
                    j = 2*j;
                    continue;
                }
                if ( cmp(rightChild, parent) > 0 && cmp(rightChild, leftChild) >= 0) {
                    swap(rightChild, parent, nByte);
                    j = 2*j +1 ;
                    continue;
                }

                break;

            }
            else if (2*j < heapSize && 2*j +1 >= heapSize) {
                void *leftChild = (char*)arr + (2*j -1 )*nByte;
                void *parent = (char*)arr + (j-1)*nByte;

                if ( cmp(leftChild, parent ) > 0 ) {
                    swap(leftChild, parent, nByte);
                    j = 2*j;
                    continue;
                }
                break;
            }
            else if ( 2*j >= heapSize && 2*j+1>= heapSize) {
                break;
            }

        }
        /*
        printf("The %d'th time: \n", i );
        printArr(arr, length, nByte, printInt);
        printf("*************************************************************\n");
        */
    }
    

}

void* mergeSort(void *arr, size_t length, size_t nByte , int (*cmp) (void *a, void *b) ) {
    
    if ( length == 1 || length == 0) {
        return arr;
    }
    else {
        void* part1 = malloc( (length/2 )*nByte);
        void* part2 = malloc( (length - length/2)*nByte );

        memcpy(part1, arr, (length/2)*nByte );
        memcpy(part2, arr + (length/2)*nByte, (length -length/2)*nByte );
    
        //printArr(part1, length/2, nByte, printInt);
        //printArr(part2, length -length/2, nByte, printInt);


        void* newPart1 = mergeSort(part1, length/2, nByte, cmp);
        void* newPart2 = mergeSort(part2, length-length/2, nByte, cmp);
        
        if (length/2 != 1 && length/2 != 0)
            free(part1);
        if (length -length/2 != 1 && length- length/2 != 0)
            free(part2);
       
        void* merged= merge(newPart1, newPart2, length/2, length-length/2, nByte, cmp);
        
        //printf("Her comes the merged version: \n");
        //printArr(merged, length, nByte, printInt);
        //printf("*******************************************************************\n");

        free(newPart1);
        free(newPart2);
        

        return merged;
    }


}

/*
 * PrintArr
 */

void printArr(void *arr, size_t length, size_t nByte, void (*print)(void *a)) {
    
    for (int i = 0; i < length; i++) {
        
        print( (char*)arr + i*nByte );
    }

    printf("\n");
}

/*
 * Function Pointers
 */

int intCmp(void *a , void *b) {

    return *(int*)a - *(int*)b;

}

void printInt(void *a) {
    
    printf("%d\t", *(int*)a );

}

/*
 * Helper Functions
 */

void swap(void *a, void *b, size_t nByte) {
    
    char temp[nByte];
    
    memcpy(temp, a, nByte);
    memcpy(a, b, nByte);
    memcpy(b, temp, nByte);
    
}

void* merge(void *arr1, void *arr2, size_t length1, size_t length2, size_t nByte, int (*cmp)(void *a, void *b)) {
        
    void *output = malloc( (length1 + length2)* nByte  );
    
    int i = 0;
    int j = 0;
    int k = 0;

   while (i < length1 || j < length2 ) {

        if ( i == length1 ) {
            memcpy( (char *)output + k*nByte , (char *)arr2 + j*nByte, nByte   );
            j++;
            k++;
            continue;
        }
        if ( j == length2 ) {
            memcpy( (char *)output + k*nByte , (char *)arr1 + i *nByte, nByte );
            i++;
            k++;
            continue;
        }

        if ( cmp( (char *) arr1 + i*nByte, (char *)arr2 + j*nByte  ) > 0  ) {
            
            memcpy( (char *)output + k*nByte , (char *)arr2 + j*nByte, nByte   );
            j++;
            k++;
        }
        else if ( cmp( (char *)arr1 + i*nByte, (char *)arr2 + j*nByte ) < 0  ) {
            
            memcpy( (char *)output + k*nByte , (char *)arr1 + i*nByte, nByte );
            i++;
            k++;
        }
        else {
            
            memcpy( (char *)output + k*nByte , (char *)arr1 + i *nByte, nByte );
            i++;
            k++;
            
        }
    
    }
    
    return output;

}
