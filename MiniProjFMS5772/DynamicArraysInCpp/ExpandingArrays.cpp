Example: Expanding an Array
A central problem in programming is the fixed size of arrays. This problem can be avoided by dynamically allocating arrays. The following shows a simple problem: read integers then print them. But you don't know how many integers there will be.
Fixed Allocation Example
This program fragment will break if more than 1000 integers are entered.

const int MAX = 1000;
int a[MAX];            // allocated on call stack
int n = 0;

//--- Read into the array
while (cin >> a[n]) {  // can overflow array
    n++;
}

//--- Write out the array
for (int i=0; i<n; i++) {
    cout << a[i] << endl;
}

You can check to see if MAX has been exceeded in the input loop, but then what should you do? Giving an error message and stopping doesn't solve anyone's problem. Continuing with only part of the data is worse because it will give the wrong answer. The way to handle this is to make the array bigger!
Dynamic Allocation Example
This program is only limited by the amount of memory. It starts with a small array and expands it only if necessary.

int max = 10;           // no longer const
int* a = new int[max];  // allocated on heap
int n = 0;

//--- Read into the array
while (cin >> a[n]) {
    n++;
    if (n >= max) {
        max = max * 2;            // double the previous size
        int* temp = new int[max]; // create new bigger array.
        for (int i=0; i<n; i++) {
            temp[i] = a[i];       // copy values to new array.
        }
        delete [] a;              // free old array memory.
        a = temp;                 // now a points to new array.
    }         
}
//--- Write out the array etc.

