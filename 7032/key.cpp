#include<bits/stdc++.h>

int main(){
  int key[16];
  srand(114514);
  for(int i=0;i<16;i++){
   key[i] = rand()%255;
   key[i] ^= 0x17;  	
  }
  
  for(int i=0;i<16;i++){  
  	printf("%x",key[i]);
  }
  
  	return 0;	
} 
