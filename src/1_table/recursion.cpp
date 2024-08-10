//
// Created by asice on 2024/5/27.
//

//iteration
#include <iostream>

using namespace std;

int main(){
    int x;
	cout<<"please input a number: "<<endl;
    cin>>x;
    int y = 0;
    int arr[]={1,234,5,8,2,3,4,55,6,6,12};
    for(int i = 0;i<10;i++){
        y = arr[i]+x*y; //O(n)=n
    }
    cout<<y;
    return 0;
}