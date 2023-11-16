#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define ROW 3
#define COL 4

void printMat(int array[3][4]);
void printRow(int array[3][4]);
void printCol(int array[3][4]);
void reverseRow(int array[3][4]);
void printMenu();
void findRowPrimes(int arr[3][4]);
bool is_prime(int number);




int main() {

    char value[10];  
    int option;
    int array[ROW][COL];

    for (int i=0;i<ROW;i++){
        for (int j=0;j<COL;j++){
            printf("Enter:");
            scanf("%d",&array[i][j]); // for adding values to the matrix
        }
        printf("\n");
    }
    do {
       
    

       printMenu();
       printf("Enter which option to choose as int (1-6): ");
       scanf("%d",&option); //scan
       printf("\n");

       switch (option){// switch based on the option chosen by the user
            case 1:
                printMat(array); // function 1
                break;

            case 2:
                printRow(array);// function 2
                break;

            case 3:
                printCol(array);// function 3
                break;
            case 4:
                reverseRow(array);// function 4
                break;
            case 5:
                findRowPrimes(array);// function 5
                break;
            case 6:
                break; // Quit..
            default: // default 
                printf("WRONG INPUT!!!");
                break;
            }       
        printf("Do you want to continue? (enter \"N\"to quit.): ");
        scanf("%s",value); // used to continue or break.
        printf("\n");
        
        } while (strcmp(value, "N") != 0);  // compared the value entered with "N" if strcmp(value, "N") == 0 loop breaks
        
    return 0;
}


void printMat(int array[3][4]){ 
     for(int i=0;i<3;i++){
       printf("\n");
      for(int j=0;j<4;j++){
        
        printf("%d \t",array[i][j]); // prints the 3X4 matrix.
        }
          printf("\n"); //newline
    }
        printf("\n");
}

void printMenu(){ // print menu
    printf("This program provides the following matrix manipulation services:\n");
    printf("\n");
    printf("1. Print the matrix in tabular form. \n");
    printf("2. Print a specific row or a number of rows in sequence (using a function printRow()). \n");
    printf("3. Print a specific column or a number of columns in sequence (using a function printCol()). \n");
    printf("4. Get the elements of a specific row reversed (using a function reverseRow()), then print the matrix to check.\n");
    printf("5. Find the number of prime numbers in a specific row (using a function findRowPrimes()). \n");
    printf("6. Quit. \n");
}

void printRow(int array[3][4]){
    int row;
    int no;
    printf("Enter the number of rows to print: ");
    scanf("%d",&no); // used to get the number of rows to print.


    int n=0;

    while (n<no){ 
    // if var contains more than 1 value then more rows will be printed 
    printf("Enter row to print (Maximum = 2): ");
    scanf("%d",&row);
    printf("\n");
    
    int i;
    for (i=0;i<COL;i++){
    printf("%d\t ",array[row][i]);// prints every element in the row.

    }
    printf("\n\n");
    n++;
    }
}

void printCol(int array[3][4]){
    int col;
    int no;
    printf("Enter the number of columns to print: ");
    scanf("%d",&no);
    int n=0;

    while (n<no){// same functionality as printRow().
    printf("Enter the column to print (Maximum = 3): ");
    scanf("%d",&col);
    printf("\n");
    
    int i;
    for (i=0;i<ROW;i++){
    printf("%d\t ",array[i][col]);// prints every element in the column.

    }
    printf("\n\n");
    n++;
    }
}

void reverseRow(int array[3][4]){
    // reverses a row in the matrix
    int row;
    
    printf("Enter row to reverse: ");
    scanf("%d",&row);
    printf("\n");
    
    int i;
    for (i=0;i<(4/2);i++){ 
    /* this will swap col/2 times.
       as two elements are being swapped in one loop 
       so we need to run the loop half of the length of the column.
    */ 
    int temp = array[row][i]; //store first value in temporary variable
    array[row][i]=array[row][COL-i-1]; // swap first element with the last
    array[row][COL-i-1]=temp; // swap last element with the first using temp variable.
    
    }

    for (int k=0;k<ROW;k++){
        for (int l=0;l<COL;l++){
            printf("%d\t",array[k][l]); // for printing the matrix
        }
        printf("\n");
    }
    
    printf("\n\n");
}

void findRowPrimes(int arr[3][4]){
    int row;
    printf("Enter the row to count prime numbers: ");
    scanf("%d",&row); // to check which row to count prime numbers
    
    int count=0;

    for (int i=0;i<4;i++){
        if (is_prime(arr[row][i])==1){ 
            /* if the passed number is a prime number
            then count increments b 1 */
            count+=1;
        }
    }
    // prints the number of prime numbers in the row.
    printf("There are %d prime numbers in the row %d.\n",count,row); 
}

bool is_prime(int number){ // returns the boolean value if the number is prime.
    if (number <=1 ) return false;
    /*  loop starts from 2 because any number mod 0 is not possible.
      and any number mod 1 = always 0 (every number is divisible by 1)
      */
    for (int i=2; i<number; i++) {
        if (number % i ==0) return false;
    }
         /* if there is a number between 2 and the argument number,
         then return false
         */
    
    return true;// otherwise return True.
}
