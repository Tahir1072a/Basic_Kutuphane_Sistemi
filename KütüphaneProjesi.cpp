#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BOOK_MAX 100

enum Authority{
	Customer,
	Employee,
	unregistered,
};

struct Person{
	int id;
    char name[20];
    char surname[20];
	Authority yetki;
};

struct Book{
	int id;
	char name[BOOK_MAX];
	char type[30];
	int customerId;
};

struct NodeBook{
	Book data;
	struct NodeBook* next;
};
struct NodePerson{
	Person data;
	struct NodePerson* next;
};
NodeBook* CreateBookList(Book dataBook){
    NodeBook* head = (NodeBook*)malloc(sizeof(NodeBook));
    head->data = dataBook;
    head->next = NULL;
    return head;
}

NodePerson* CreatePersonList(Person dataPerson){
    NodePerson* head = (NodePerson*)malloc(sizeof(NodePerson));
    head->data = dataPerson;
    head->next = NULL;

    return head;
}

NodeBook* AddBook(NodeBook** head,Book dataBook){
	
	if((*head) == NULL) return CreateBookList(dataBook);
	else{
		for(int i = 0; i < BOOK_MAX;i++){
		   if((*head)->data.name[i] < dataBook.name[i]) break;
		   if((*head)->data.name[i] == dataBook.name[i]) continue;
		   if((*head)->data.name[i] > dataBook.name[i]){
		      struct NodeBook* ptr = *head;
			  (*head) = (NodeBook*)malloc(sizeof(NodeBook));
			  (*head)->data = dataBook;
			  (*head)->next = ptr;
			  return *head;	
		   }
	   }
	   struct NodeBook* ptr = (*head);
	   int i = 0;
	   while(ptr->next != NULL && ptr->next->data.name[i] < dataBook.name[i]){
	   	    ptr = ptr->next;
	   }
	   if(ptr->next == NULL){
	   	ptr->next = (NodeBook*)malloc(sizeof(NodeBook));
	    ptr = ptr->next;
	    ptr->data = dataBook;
	    ptr->next = NULL;
	   }
	   else{
	   	struct NodeBook* temp = ptr->next;
	   	    ptr->next = (NodeBook*)malloc(sizeof(NodeBook));
		    ptr->next->data = dataBook;
		    ptr->next->next = temp;
	   }
	}
	
	return *head;
}
//string.h kullanýlarak yazýlan fonksiyon.
NodePerson* AddPerson(NodePerson** head, Person dataPerson){
	
	if((*head) == NULL) return CreatePersonList(dataPerson);
	else{
		for(int i = 0; i < 20; i++){ // 20, isim alanýnýn boyutu. 
		   if((*head)->data.name[i] < dataPerson.name[i]) break;
		   if((*head)->data.name[i] == dataPerson.name[i]) continue;
		   if((*head)->data.name[i] > dataPerson.name[i]){
		      struct NodePerson* ptr = *head;
			  (*head) = (NodePerson*)malloc(sizeof(NodePerson));
			  (*head)->data = dataPerson;
			  (*head)->next = ptr;
			  return *head;	
		   }
	   }
	   struct NodePerson* ptr = (*head);
	   int i = 0;
	   while(ptr->next != NULL && strcmp(ptr->next->data.name, dataPerson.name) < 0){
	   	    ptr = ptr->next;
	   }
	   if(ptr->next == NULL){
	   	ptr->next = (NodePerson*)malloc(sizeof(NodePerson));
	    ptr = ptr->next;
	    ptr->data = dataPerson;
	    ptr->next = NULL;
	   }
	   else{
	   	struct NodePerson* temp = ptr->next;
	   	    ptr->next = (NodePerson*)malloc(sizeof(NodePerson));
		    ptr->next->data = dataPerson;
		    ptr->next->next = temp;
	   }
	}
	return *head;
}

void PrintfList(NodeBook* head){
	struct NodeBook* ptr = head;
	while(ptr != NULL){
		printf("\nId :%d,\nName:%s\nType:%s\nCustomerId:%d",ptr->data.id,ptr->data.name,ptr->data.type,ptr->data.customerId);
		ptr = ptr->next;
	}
}
void PrintPersonList(NodePerson* head){
	struct NodePerson* ptr = head;
	while(ptr != NULL){
		printf("\nId :%d,\nName:%s\nSurname:%s\nAuthority:%d",ptr->data.id,ptr->data.name,ptr->data.surname,ptr->data.yetki);
		ptr = ptr->next;
	}
}

void BookCache(NodeBook** head,char* name){
	
	FILE* fp = fopen(name,"r+b");
	
	if(fp == NULL) printf("File can not open!");
	else{
		Book data;
		while(fread(&data,sizeof(Book),1,fp) == 1){
			AddBook(head,data);
		}
		fclose(fp);
	}
}

void AddBookListToFile(NodeBook* head,char* name){
	
	FILE* fp = fopen(name,"a+b");
	
	if(fp == NULL) printf("File can not open!");
	else{
		fseek(fp,0,SEEK_END);
		struct NodeBook* ptr = head;
		while(&(ptr->data) != NULL && fwrite(ptr,sizeof(Book),1,fp) == 1){
			ptr= ptr->next;
		}
	}
	
	fclose(fp);
}
void PersonCache(NodePerson** head,char* name){
	
	FILE* fp = fopen(name,"r+b");
	
	if(fp == NULL) {
		printf("File can not open!");
	} else {
		Person data;
		while(fread(&data,sizeof(Person),1,fp) == 1){
			AddPerson(head,data);
		}
		fclose(fp);
	}
}

void AddPersonListToFile(NodePerson* head, char* name){
	
	FILE* fp = fopen(name,"a+b");
	
	if(fp == NULL) {
		printf("File can not open!");
		return;
	}
	
	struct NodePerson* ptr = head;
	while(ptr != NULL){
		if(fwrite(&(ptr->data), sizeof(Person), 1, fp) != 1){
			printf("File write error!\n");
		}
		ptr = ptr->next;
	}
	
	fclose(fp);
}

enum Authority YetkiKontrol(NodePerson* head,struct Person person){
	struct NodePerson* ptr = head;
	while(ptr != NULL && ptr->data.id != person.id){
		ptr = ptr->next;
	}
	if(ptr->data.id == person.id){
		return person.yetki;
	}
	printf("\nKayýtlý kullanýcý bulunamadi!");
	
	return unregistered;
}
void CustomerKayit(NodePerson** head,Person* person){
	struct NodePerson* ptr = *head;
	int i = 0;
	while(ptr != NULL){
		ptr = ptr->next;
	    i++;
	} 
	person->id = i+1;
	person->yetki = Customer;
	
	AddPerson(head,*person);
}

int main(){

	Person* person = (struct Person*)malloc(sizeof(struct Person));

	struct NodeBook* headBook = NULL;
	struct NodePerson* headPerson = NULL; 
	
	BookCache(&headBook,"Books.bin");
	PersonCache(&headPerson,"Persons.bin");
	
	while(1){
		printf("\nWelcome! Adinizi girin :");
		scanf("%s", person->name);
		printf("\nSoyadinizi girin :");
		scanf("%s", person->surname);
		
		enum Authority mevcutYetki = YetkiKontrol(headPerson,*person);
		int secim;
		switch(mevcutYetki){
			case Customer:{
				printf("\n%s %s tekrardan Merhaba",mevcutYetki,person->name);
				printf("\n\n1 - Kitap listesini gör\n2 - Kitap Kirala\n3 - Çýkýþ\nSeciminizi girin: ");
				scanf("%d", &secim);
				switch(secim){
					case 1:
						PrintfList(headBook);
						break;
					case 2:
						// RentBook fonksiyonunun tamamlanmasý gerekmekte
						break;
					case 3:
						exit(0);
					default:
						printf("Geçersiz seçim!\n");
				}
				break;
			}
			case Employee:{
				printf("\n%s %s tekrardan Merhaba",mevcutYetki,person->name);
				printf("\n\n1 - Kitap listesini gör\n2 - Kitap Ekle\n3 - Kitap Sil\n4 - Çýkýþ\nSeciminizi girin: ");
				scanf("%d", &secim);
				switch(secim){
					case 1:
						PrintfList(headBook);
						break;
					case 2:
						// AddBook fonksiyonunun tamamlanmasý gerekmekte
						break;
					case 3:
						// Bir kitap silme fonksiyonu tamamlanmalý
						break;
					case 4:
						exit(0);
					default:
						printf("Geçersiz seçim!\n");
				}
				break;
			}
			case unregistered:{
				printf("\nHerhangi bir kaydiniz bulunmamaktadir. Kayit yaptirmak icin 1'e baisiniz :");
				scanf("%d",&secim);
				if(secim != 1) break;
				else{
					CustomerKayit(&headPerson,person);
				}
				break;
			}
		}
	}
	return 0;
}

