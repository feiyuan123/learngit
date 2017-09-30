#include <iostream>

using namespace std;

int main()
{

    int a[5]={1,2,3,4,5};
    int *ptr=(int*)(&a+1);
    cout<<*(a+1)<<*(ptr-1)<<endl;
    return 0;
}
