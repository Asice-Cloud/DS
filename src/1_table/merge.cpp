//
// Created by asice on 2024/5/19.
//
#include<iostream>
#include<algorithm>
#include <vector>
using namespace std;

void merge(int* arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = new int[n1];
    int* R = new int[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void merge_sort_pointer(int* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        merge_sort_pointer(arr, l, m);
        merge_sort_pointer(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void merge_sort_time(int *arr,int n){
    for(int seg=1;seg<n;seg<<=1){
        for(int start=0;start<n;start+=seg+seg){
            int low=start,mid=min(start+seg,n),high=min(start+seg+seg,n);
            merge(arr,low,mid-1,high-1);
        }
    }
}

template<typename T>
void Merge_T(vector<T>&vec,vector<T>&v1,vector<T>&v2){
    auto size1=v1.size();
    auto size2=v2.size();
    size_t p1=0,p2=0;
    while(p1<size1&&p2<size2){
        if(v1.at(p1)>v2.at(p2))
            vec.push_back(v2.at(p2++));
        else
            vec.push_back(v1.at(p1++));
    }
    while(p1<size1) vec.push_back(v1.at(p1++));
    while(p2<size2) vec.push_back(v2.at(p2++));
}

template<typename T>
void merge_sort_T_type(vector<T>&vec){
    if(vec.size()<=1) return;
    auto iter=vec.begin()+vec.size()/2;
    vector<T> v1(vec.begin(),iter);
    vector<T> v2(iter,vec.end());

    merge_sort_T_type(v1);
    merge_sort_T_type(v2);
    vec.clear();
    Merge_T(vec,v1,v2);
}


template<typename T>
void Print(T* arr,int count){
    for (T i = 0; i < count; ++i) {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}
template<typename T>
void Print(const vector<T>&vec){
    for (auto &i:vec) {
        cout<<i<<" ";
    }
    cout<<endl;
}

int main(){
    vector<int> vec1={8,7,8,9,1,2,3,5,2,0};
    merge_sort_T_type(vec1);
    Print(vec1);

    int arr2[10]={4,8,9,4,3,5,1,3,7,6};
    merge_sort_time(arr2,10);
    Print(arr2,10);

    int arr3[10]={4,8,9,4,3,5,1,3,7,6};
    merge_sort_pointer(arr3,0,9);
    Print(arr3,10);

    return 0;
}