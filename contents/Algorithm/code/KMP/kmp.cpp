#include <iostream>
#include <string.h>

using namespace std;

int failure[10];

void fail(char *pat){
	int j, n = strlen(pat);
	failure[0] = -1; // failure[0] 는 무조건 -1
	
	for(int i=1; i<n; i++){
		j = failure[i-1];
		
		while( (pat[i] != pat[j+1]) && (j>=0)){ // 일치할때까지 	 
			j = failure[j];	 
		}
		 
		if( pat[i] == pat[j+1]){ 
			failure[i] = j+1;
		}else{
			failure[i] = -1;
		}
	} 
} 

int kmp(char* str, char* pat){
	int i=0;
	int j=0;
	int lens = strlen(str);
	int lenp = strlen(pat);
	
	while(i<lens && j<lenp){
		if(str[i] == pat[j]){	// 본문과 패턴이 같다면 
			i++;	// 본문 한글자 뒤로 
			j++;	// 패턴 한글자 뒤로 
		}else if(j==0){	// 패턴 첫글자부터 다르면 
			i++;	// 본문 한글자 뒤로 
		}else{	// 같은 부분이 있다면 
			j = failure[j-1] + 1;	// failure[] 배열 값 이용 
		}
	}
	return ( j == lenp ? i-lenp : -1);
}

int main(){
	char* str = "ABCABABCABCAC";
	char* pat = "ABCABCAC"; 
	
	fail(pat);
	
	int result = kmp(str, pat);
	
	if(result == -1){
		cout << "Can't find pattern" << endl;
	}else{
		cout << "idx "<< result << " = pattern start" << endl;
	}	
	return 0;		
}