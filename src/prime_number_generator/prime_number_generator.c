#include <prime_number_generator.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>



#define MAX_NUM_NO_OVERFLOW 0x727c9716



uint64_t* prime_number_generator(uint64_t n,uint64_t* l){
	if (n>MAX_NUM_NO_OVERFLOW){
		printf("Warning: Integer Overflow with n = %#llx\n",n);
		n=MAX_NUM_NO_OVERFLOW;
	}
	*l=0;
	if (n<2){
		return NULL;
	}
	(*l)++;
	if (n<3){
		uint64_t* o=malloc(sizeof(uint64_t));
		*o=2;
		return o;
	}
	(*l)++;
	uint64_t* s=calloc((n+63)>>6,sizeof(uint64_t));
	for (uint64_t i=1,j=1;j<n;j+=(i<<1)+1,i++){
		for (uint64_t k=1,l=1;l<n;l+=(k<<1)+1,k++){
			uint64_t m=3*j;
			if (i<=k){
				m+=l;
				goto _skip;
			}
			m-=l;
			if (m<=n){
				if (i>k&&m%12==11){
					*(s+(m>>6))^=(uint64_t)1<<(m&0x3f);
				}
				m+=l*2;
_skip:
				if (m<=n){
					if (m%12==7){
						*(s+(m>>6))^=(uint64_t)1<<(m&0x3f);
					}
					m+=j;
					if (m<=n&&(m%12==1||m%12==5)){
						*(s+(m>>6))^=(uint64_t)1<<(m&0x3f);
					}
				}
			}
		}
	}
	uint64_t e=0;
	for (uint64_t i=5,j=25;i<n;i++){
		if (*(s+(i>>6))&((uint64_t)1<<(i&0x3f))){
			if (j){
				for (uint64_t k=j;k<n;k+=j){
					*(s+(k>>6))&=~((uint64_t)1<<(k&0x3f));
				}
			}
			(*l)++;
			e=i+1;
		}
		if (j){
			j+=(i<<1)+1;
			if (j>=n){
				j=0;
			}
		}
	}
	uint64_t* o=malloc(*l*sizeof(uint64_t));
	*o=2;
	*(o+1)=3;
	uint64_t j=2;
	for (uint64_t i=5;i<e;i++){
		if (*(s+(i>>6))&((uint64_t)1<<(i&0x3f))){
			*(o+j)=i;
			j++;
			if (j==*l){
				break;
			}
		}
	}
	free(s);
	return o;
}
