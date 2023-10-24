#include<iostream>
#include<stack>
using namespace std;
int main()
{
    int nums = 0;
    cin >> nums;
    while(nums--){
        stack<int> mystack;
        int datanum = 0;
        cin >> datanum;
        while(datanum--){
            int temp;cin >> temp;
            mystack.push(temp);
        }
        while(!mystack.empty()){
            cout << mystack.top() << " ";
            mystack.pop();
        }
        cout << endl;
    }
    return 0;
}