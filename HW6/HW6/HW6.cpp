#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>

//#define MAX_ARRAY_SIZE 20011    // Array size as a prime number
#define DEBUG false
using namespace std;

// prototypes
bool    loadFile  (string strFileName, int hash_table[], int M);
int     hash3578  (int numberToHash);
int    quadratic_probing_without_replacement(int number, int hash_table[], int M);
void    writeFile (string strFileName, int hash_table[], int M);

int main()
{
    int M;
    bool bRet = false;
    if ( DEBUG )
    {
        int tmp = hash3578(123456789);
    }

    do
    {
        cout << "Enter a value for M between 1 and 450000000 primes preferred" << endl;
        cout << "Keep your memory in mind,  This will be your array size" << endl;
        cin >> M;

    }
    while (!(M > 1 && M < 450000000));

    int *hash_table=new int [M];

    //initialize the hash table to contain 0s
    for(size_t i=0; i < M; i++)
        hash_table[i]=0;

    // load the file
    bRet = loadFile ("everybodys_socials.txt", hash_table, M);

    if (bRet)
    {
        writeFile("hashed_socials.txt", hash_table, M);
    }

    delete hash_table;
    return 0;
}


/*******************************************************************************
Open the file
get the integers
*******************************************************************************/
bool loadFile (string strFileName, int hash_table[], int M)
{
    int pos;
    int number;
    char comma;
    ifstream in;
    int numberQty = 0;

    in.open(strFileName);
    if(!in.is_open())
    {
        cout << "The read file " << strFileName << " could not be opened";
        return false;
    }

    while(in.peek()!=EOF)
    {
        in >> number;
        in >> comma;
        numberQty++;
        pos = quadratic_probing_without_replacement( number, hash_table, M);
        if(pos == -1)
        {
            cout << "Table overflowed on Key " << number << endl;
            in.clear();
            in.close();
            return false;
        }
    }
    in.clear();
    in.close();
    cout << "Total numbers read " << numberQty << endl;
    return true;
}

/*******************************************************************************
parsing the number and putting in a new array
*******************************************************************************/
int hash3578 (int numberToHash)
{
    stringstream ssTemp1;
    stringstream ssTemp2;
    int ihash;
    string sTemp;
    char cTemp2[5] = {'\0'};

    ssTemp1 << numberToHash;
    ssTemp1 >> sTemp;

    cTemp2[0] = sTemp[2];
    cTemp2[1] = sTemp[4];
    cTemp2[2] = sTemp[6];
    cTemp2[3] = sTemp[7];
    cTemp2[4] = '\0';

    ssTemp2 << cTemp2;
    ssTemp2 >> ihash;

    return ihash;
}

int quadratic_probing_without_replacement(int key, int hash_table[], int M)
{
    int pos,i, newPos;
    pos=hash3578(key);

    if(hash_table[pos]==0)
    {
        hash_table[pos]=key;
        return pos;
    }
    else		//slot is not empty
    {
        for(i=1; i < ((M -1) / 2); i++)
        {
            newPos = (pos + (i^2))%M;
            if(hash_table[newPos]==0)
            {
                hash_table[newPos]=key;
                return newPos;
            }
        }
    }
    return -1;	//table overflow
}

void writeFile (string strFileName, int hash_table[], int M)
{
    ofstream out;
    out.open(strFileName);

    for(size_t i = 0; i < M; i++)
    {
        if(i < (M-1)) //if not at the end of the file
        {
            out << hash_table[i] << ',';
        }
        else
        {
            out << hash_table[i];
        }
    }
    out.clear();
    out.close();
}
