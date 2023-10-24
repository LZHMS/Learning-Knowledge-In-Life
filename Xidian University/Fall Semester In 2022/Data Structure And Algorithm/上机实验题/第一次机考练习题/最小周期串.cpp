#include <iostream>
#include<cstring>
using namespace std;
int main(){
    char word[81];
    cin >> word;
    int len = strlen(word);
    for(int i=1;i<=len;i++){  //假定周期
        int ok=1;
        if(len%i == 0){
            for(int j=i;j<len;j++){
                if(word[j] != word[j%i]){
                    ok = 0;
                    break;
                }
            }
            if(ok){
                cout<<i<<endl;
                return 0;
            }
        }
    }
    return 0;
}
