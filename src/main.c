#include <prime_number_generator.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>



uint32_t _log10(uint64_t v){
	if (!v){
		return 1;
	}
	uint32_t o=1;
	size_t pw=10;
	v++;
	while (pw<v){
		o++;
		if (o==20){
			break;
		}
		pw*=10;
	}
	return o;
}



int main(int argc,const char** argv){
	LARGE_INTEGER f;
	LARGE_INTEGER s;
	LARGE_INTEGER e;
	QueryPerformanceFrequency(&f);
	uint64_t l=0;
	printf("Start...\n");
	QueryPerformanceCounter(&s);
	uint64_t* o=prime_number_generator(100/*0x727c9716*/,&l);
	QueryPerformanceCounter(&e);
	if (!l){
		printf("No Primes (%.6fs)",(e.QuadPart-s.QuadPart)*1e6/f.QuadPart*1e-6);
	}
	else if (l==1){
		printf("1 Prime (%.6fs):\n[0]: %llu",(e.QuadPart-s.QuadPart)*1e6/f.QuadPart*1e-6,*o);
	}
	else{
		printf("%llu Primes (%.6fs):\n",l,(e.QuadPart-s.QuadPart)*1e6/f.QuadPart*1e-6);
		if (l>25){
			l=25;
		}
		uint32_t w=_log10(l-1);
		for (uint64_t i=0;i<l;i++){
			printf("[%*llu]: %llu\n",w,i,*(o+i));
		}
	}
	free(o);
	return 0;
}
