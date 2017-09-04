#include <stdio.h>

void test2(){
	if(1)
		test3();
}

int main(){

	int i;

	if(1){
		test1();
	}

	if(1)
		if(2){
			if(3)
				test1();
		}

	if(1)
		test1();
	else if(1)
		test1();

	while(1){
		test1();
	}

	do{
		test1();
	}while(1);

	for(i = 0; i < 10; i++){
		test1();
	}

	test2();

	return 0;

}
