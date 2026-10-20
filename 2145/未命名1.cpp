#include <bits/stdc++.h>

int main(){
char a[] = "d`vxbQd";


for(int i=0;i<7;i++){ 
        a[i]=a[i]^2;
        a[i]--;
    }
printf("%s",a);
}
