#include <stdio.h>

typedef enum Authority {Admin=1, Customer=2, Guest=3} Authority;

struct Person{
	int id;
    char name[20];
    char surname[20];
	Authority yetki;
};



int main(){
	
	Person person;
	FILE* fp = fopen("Persons.bin","w+b");
	if(fp == NULL) printf("File can not open");
	
	
	printf("id :");
	scanf("%d",&person.id);
	printf("Name :");
	scanf("%s",&person.name);
	printf("Surname :");
	scanf("%s",&person.surname);
	printf("Yetki :");
	scanf("%d",&person.yetki);
	fwrite(&person,sizeof(Person),1,fp);
	fclose(fp);
	
	return 0;
}
