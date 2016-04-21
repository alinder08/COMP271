#include <iostream>
#include <fstream>
#include <string>
//#include<conio.h>

#define MAX_ARRAY_SIZE 10000
#define MAX_FILES 4
#define DEBUG false

using namespace std;

void bubbleSort(int A[], int n, int &comparisions, int &exchanges)
{
    int i;
    int j;
    int temp;

    for( i = 1; i<n ; i++) // number of passes
    {
        for(j = 0; j < n-i ; j++) // j varies from 0 to n-i
        {
            comparisions++;
            if( A[j] > A[j+1] )// compare two successive numbers
            {
                exchanges++;
                temp = A[j]; // swap A[j] with A[j+1]
                A[j] = A[j+1];
                A[j+1] = temp;
            }
        }
    }
}

void insertionSort(int A[], int n, int &comparisions, int &exchanges)
{
    int i;
    int j;
    int element;

    for(i=1; i<n; i++)
    {
        element = A[i]; // insert ith element in 0 to i-1 array
        j=i;
        while((j > 0) && (A[j-1] > element))//compare if A[j-1]>element
        {
            comparisions++;
            exchanges++;
            A[j] = A[j-1]; // shift elements
            j = j-1;
        }
        A[j] = element; // place element at jth position
        exchanges++;    ////?????  is this considered an exchange?????
    }
}

void shellSort(int A[], int n, int &comparisions, int &exchanges)
{
    int temp;
    int gap;
    int i;
    int swapped;
    gap = n/2;

    do
    {
        do
        {
            swapped = 0;
            for(i = 0; i < n - gap; i++)
            {
                comparisions++;
                if(A[i] > A[i + gap])
                {
                    temp = A[i];
                    A[i] = A[i + gap];
                    A[i + gap] = temp;
                    swapped = 1;
                    exchanges++;
                }
            }
        }
        while(swapped == 1);
    }
    while((gap = gap/2) >=1);
}

void quickSort_Swap(int A[], int x, int y, int &comparisions, int &exchanges)
{
    int t;
    t = A[x];
    A[x] = A[y];
    A[y] = t;
    exchanges++;
}

int quickSort_Partiition(int A[], int low, int high, int &comparisions, int &exchanges)
{
    int pivotloc;
    int pivot;
    int i;
    int lastsmall;

    quickSort_Swap(A, low,(low+high)/2, comparisions, exchanges);
    pivot = A[low];
    lastsmall = low;
    for(i=low+1; i<=high; i++)
    {
        comparisions++;
        if(A[i] < pivot)
        {
            lastsmall = lastsmall+1;
            quickSort_Swap(A, lastsmall, i, comparisions, exchanges);
        }
    }
    quickSort_Swap(A, low, lastsmall, comparisions, exchanges);
    pivotloc = lastsmall;
    return(pivotloc);
}

void quickSort(int A[], int low, int high, int &comparisions, int &exchanges)
{
    int pivotloc;
    if(low < high)
    {
        pivotloc = quickSort_Partiition(A, low, high, comparisions, exchanges );
        quickSort(A, low, pivotloc-1, comparisions, exchanges);
        quickSort(A, pivotloc+1, high, comparisions, exchanges);
    }
}

void merge (int A[],int low, int high, int mid, int &comparisions, int &exchanges)
{
    int i;
    int j;
    int k;
    int C[MAX_ARRAY_SIZE];

    i = low; // index for first part
    j = mid + 1; // index for second part
    k = 0; // index for array C
    while((i <= mid) && (j <= high)) // changed (j <= high) to (j < high)
        // merge array A & B in array C
    {
        comparisions++;
        if(A[i] < A[j])
        {
            C[k] = A[i++];
            exchanges++;
        }
        else
        {
            C[k] = A[j++];
            exchanges++;
        }
        k++;
    }
    while(i <= mid)
    {
        C[k++] = A[i++];
        exchanges++;
    }

    while(j <= high)
    {
        C[k++] = A[j++];
        exchanges++;
    }

    for(i = low,j = 0; i <= high; i++, j++)
// copy array C contents back to array A
    {
        A[i] = C[j];
        exchanges++;
    }
}
void MergeSort(int A[], int low, int high, int &comparisions, int &exchanges)
{
    int mid;
    if(low < high)
    {
        mid = (low + high)/2;
        MergeSort(A, low, mid, comparisions, exchanges);
        MergeSort(A, mid + 1, high, comparisions, exchanges);
        merge(A, low, high, mid, comparisions, exchanges);
    }
}
/*******************************************************************************
Open the file
get the integers
*******************************************************************************/
bool loadFile ( int A[], string strFileName)
{
    int number;
    int i = 0;
    ifstream in;

    in.open(strFileName);
    if(!in.is_open())
    {
        cout << "The read file " << strFileName << " could not be opened";
        return false;
    }

    while(in.peek()!=EOF && i < MAX_ARRAY_SIZE)
    {
        in >> number;
        A[i] = number;
        i++;
    }
    in.clear();
    in.close();
    return true;
}


int main()
{
    int A[MAX_ARRAY_SIZE];
    int comparisons = 0;
    int exchanges = 0;

    string fileName[MAX_FILES] =
    {
        "FewUnique.txt",
        "NearlySorted.txt",
        "Random.txt",
        "Reversed.txt"
    };

    for (size_t i = 0; i < MAX_FILES; i++)
    {
        cout << "File name = " << fileName[i] << "\tSize = " << MAX_ARRAY_SIZE << endl;
        if (loadFile(A, fileName[i]))
        {
            if ( DEBUG )
            {
                for (size_t i = 0; i< MAX_ARRAY_SIZE; i++ )
                {
                    cout << A[i] << "; ";
                }
                cout << endl;
            }
            comparisons = 0;
            exchanges = 0;
            bubbleSort(A, MAX_ARRAY_SIZE, comparisons, exchanges);
            //       12345678901234567890
            cout << "Bubble Sort    " << "\tComparisons = " << comparisons << "\tExchanges = " << exchanges << endl;
            if ( DEBUG )
            {
                for (size_t i = 0; i< MAX_ARRAY_SIZE; i++ )
                {
                    cout << A[i] << "; ";
                }
                cout << endl <<endl;
            }
        }
        if (loadFile(A, fileName[i]))
        {
            if ( DEBUG )
            {
                for (size_t i = 0; i< MAX_ARRAY_SIZE; i++ )
                {
                    cout << A[i] << "; ";
                }
                cout << endl;
            }
            comparisons = 0;
            exchanges = 0;
            insertionSort(A, MAX_ARRAY_SIZE, comparisons, exchanges);
            //       12345678901234567890
            cout << "Insertion Sort " << "\tComparisons = " << comparisons << "\tExchanges = " << exchanges << endl;
            if ( DEBUG )
            {
                for (size_t i = 0; i< MAX_ARRAY_SIZE; i++ )
                {
                    cout << A[i] << "; ";
                }
                cout << endl << endl;
            }
        }
        if (loadFile(A, fileName[i]))
        {
            if ( DEBUG )
            {
                for (size_t i = 0; i< MAX_ARRAY_SIZE; i++ )
                {
                    cout << A[i] << "; ";
                }
                cout << endl;
            }
            comparisons = 0;
            exchanges = 0;
            shellSort(A, MAX_ARRAY_SIZE, comparisons, exchanges);
            //       12345678901234567890
            cout << "Shell Sort     " << "\tComparisons = " << comparisons << "\tExchanges = " << exchanges << endl;
            if ( DEBUG )
            {
                for (size_t i = 0; i< MAX_ARRAY_SIZE; i++ )
                {
                    cout << A[i] << "; ";
                }
                cout << endl << endl;
            }
        }
        if (loadFile(A, fileName[i]))
        {
            if ( DEBUG )
            {
                for (size_t i = 0; i< MAX_ARRAY_SIZE; i++ )
                {
                    cout << A[i] << "; ";
                }
                cout << endl;
            }
            comparisons = 0;
            exchanges = 0;
            quickSort(A, 0, MAX_ARRAY_SIZE, comparisons, exchanges);
            //       12345678901234567890
            cout << "Quick Sort     " << "\tComparisons = " << comparisons << "\tExchanges = " << exchanges << endl;
            if ( DEBUG )
            {
                for (size_t i = 0; i< MAX_ARRAY_SIZE; i++ )
                {
                    cout << A[i] << "; ";
                }
                cout << endl << endl;
            }
        }
        if (loadFile(A, fileName[i]))
        {
            if ( DEBUG )
            {
                for (size_t i = 0; i< MAX_ARRAY_SIZE; i++ )
                {
                    cout << A[i] << "; ";
                }
                cout << endl;
            }
            comparisons = 0;
            exchanges = 0;
            MergeSort(A, 0, MAX_ARRAY_SIZE, comparisons, exchanges);
            //       12345678901234567890
            cout << "Merge Sort     " << "\tComparisons = " << comparisons << "\tExchanges = " << exchanges << endl;
            if ( DEBUG )
            {
                for (size_t i = 0; i< MAX_ARRAY_SIZE; i++ )
                {
                    cout << A[i] << "; ";
                }
                cout << endl << endl;
            }
        }
        cout << endl;
    }

    cout << "All Done" << endl;
    return 1;
}

