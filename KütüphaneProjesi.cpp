#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

#define BOOK_MAX 100

typedef enum Authority {Admin=1, Customer=2, Guest=3} Authority;

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
NodeBook** CreateBookList(NodeBook** head,Book dataBook){
    *head = (NodeBook*)malloc(sizeof(NodeBook));
    (*head)->data = dataBook;
    (*head)->next = NULL;
    return head;
}

NodePerson** CreatePersonList(NodePerson** head,Person dataPerson){
    *head = (NodePerson*)malloc(sizeof(NodePerson));
    (*head)->data = dataPerson;
    (*head)->next = NULL;

    return head;
}

NodeBook* AddBook(NodeBook** head,Book dataBook){
	
	if((*head) == NULL) return *CreateBookList(head,dataBook);
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

NodeBook* DeleteBook(NodeBook** head,int bookId){
	if((*head) == NULL) {
		printf("\nListe bos!");
		return NULL;
	}
	else{
		
		if((*head)->data.id == bookId){
			struct NodeBook* temp = (*head)->next;
			free(*head);
			(*head) = temp;
		}
		else{
			struct NodeBook** ptr = head;
	     	while((*ptr)->next != NULL && (*ptr)->next->data.id != bookId){
	     		(*ptr) = (*ptr)->next;
			 }
			if((*ptr)->next != NULL){
				struct NodeBook** temp = &((*ptr)->next);
				(*ptr)->next = (*ptr)->next->next;
				free(*temp);
				printf("\nSilindi");
                return *head;			
			}
			else{
				printf("\nListede boyle bir kitap yok");
			}
		}
	}
	return *head;
}
//string.h kullanýlarak yazýlan fonksiyon.
NodePerson* AddPerson(NodePerson** head, Person dataPerson){
	
	if((*head) == NULL) return *CreatePersonList(head,dataPerson);
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
NodePerson* DeletePerson(NodePerson** head, int personId){
	if((*head) == NULL) {
		printf("\nListe bos!");
		return NULL;
	}
	else{
		if((*head)->data.id == personId){
			NodePerson* temp = (*head)->next;
			free(*head);
			(*head) = temp;
		}
		else{
			NodePerson* ptr = *head;
	     	while(ptr->next != NULL && ptr->next->data.id != personId){
	     		ptr = ptr->next;
			 }
			if(ptr->next != NULL){
				NodePerson* temp = ptr->next;
				ptr->next = ptr->next->next;
				free(temp);
				printf("\nSilindi");
                return *head;			
			}
			else{
				printf("\nListede boyle bir kisi yok");
			}
		}
	}
	return *head;
}

void PrintfList(NodeBook* head){
	struct NodeBook* ptr = head;
	if(ptr == NULL) printf("\nListe Bos!");
	while(ptr != NULL){
		printf("\nId :%d,\nName:%s\nType:%s\nCustomerId:%d",ptr->data.id,ptr->data.name,ptr->data.type,ptr->data.customerId);
		ptr = ptr->next;
	}
}
void PrintPersonList(NodePerson* head){
	struct NodePerson* ptr = head;
	if(ptr == NULL) printf("\nListe Bos!");
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
	
	FILE* fp = fopen(name,"w+b");
	
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
	
	FILE* fp = fopen(name,"w+b");
	
	if(fp == NULL) {
		printf("File can not open!");
		return;
	}
	fseek(fp,0,SEEK_END);
	struct NodePerson* ptr = head;
	while(ptr != NULL){
		if(fwrite(&(ptr->data), sizeof(Person), 1, fp) != 1){
			printf("File write error!\n");
		}
		ptr = ptr->next;
	}
	
	fclose(fp);
}

Authority YetkiKontrol(NodePerson* head,struct Person person){
	struct NodePerson* ptr = head;
	while(ptr != NULL && ptr->data.id != person.id){
		ptr = ptr->next;
	}
	if(ptr != NULL && ptr->data.id == person.id){
		return ptr->data.yetki;
	}
	printf("\nKayitli kullanici bulunamadi!");
	
	return Guest;
}
void CustomerKayit(NodePerson** head,Person* person){
	struct NodePerson** ptr = head;
	int i = 0;
	while((*ptr) != NULL){
		*ptr = (*ptr)->next;
	    i++;
	} 
	person->id = i+1;
	person->yetki = Customer;
	NodePerson* result = AddPerson(head,*person);
	if(result != NULL) printf("Eklendi!");
	else printf("Basarisiz islem");
}
void RentBook(struct NodeBook** head,Person person,int bookId){
	struct NodeBook** ptr = head;
	
	while((*ptr) != NULL && (*ptr)->data.id != bookId){
		*ptr = (*ptr)->next;
	}
	if((*ptr)->data.customerId != 0) printf("\nBu kitap su anda kiralik!");
	else{
		(*ptr)->data.customerId = person.id;
		printf("\nKitab basari ile kiralanmistir."); 
	}
}

void AddBookMenu(NodeBook** head){
	struct Book temp;
	
	printf("\nKitab bilgilerini doldurunuz..");
	printf("\nAdi :");
	scanf("%s",&temp.name);
	printf("\nKitabin turu :");
	fflush(stdin);
	scanf("%s",&temp.type);
	int i =0;
	struct NodeBook* ptr = *head;
	while(ptr != NULL){
		ptr = ptr->next;
		i++;
	}
	temp.id = i;
	temp.customerId = 0;
	AddBook(head,temp);
}
int main(){

	Person* person = (struct Person*)malloc(sizeof(struct Person));

	struct NodeBook* headBook = NULL;
	struct NodePerson* headPerson = NULL; 
	
	BookCache(&headBook,"Books.bin");
	PersonCache(&headPerson,"Persons.bin");
	int a = 1;
	while(a == 1){
		printf("\nWelcome! Adinizi girin :");
		scanf("%s", &(person->name));
		printf("\nSoyadinizi girin :");
		scanf("%s", &(person->surname));
		printf("\nKimlik degerinizi giriniz (Kayitli degil iseniz 0 a basin):");
		scanf("%d",&(person->id));
		Authority mevcutYetki = YetkiKontrol(headPerson,*person);
		switch(mevcutYetki){
			case Customer:{
				int secim;
				printf("\nCustomer %s tekrardan Merhaba",person->name);
				printf("\n\n1 - Kitap listesini gör\n2 - Kitap Kirala\n3 - Cikis\nSeciminizi girin: ");
				scanf("%d", &secim);
				switch(secim){
					case 1:
						PrintfList(headBook);
						break;
					case 2:
						int secim;
						printf("\nKiralamk istediginiz kitabin id'sini giriniz :'");
						scanf("%d",&secim);
						RentBook(&headBook,*person,secim);
						break;
					case 3:
						exit(0);
					default:
						printf("Geçersiz seçim!\n");
				}
				break;
			}
			case Admin:{
				int secim;
				printf("\nAdmin %s tekrardan Merhaba",person->name);
				printf("\n\n1 - Kitap listesini gör\n2 - Kitap Ekle\n3 - Kitap Sil\n4 - Cikis\nSeciminizi girin: ");
				scanf("%d", &secim);
				switch(secim){
					case 1:
						PrintfList(headBook);
						break;
					case 2:
						AddBookMenu(&headBook);
						break;
					case 3:
						int secim;
						printf("\nSilinecek kitabin id degerini giriniz :");
						scanf("%d",&secim);
						DeleteBook(&headBook,secim);
						break;
					case 4:
						exit(0);
					default:
						printf("\nGeçersiz seçim!\n");
				}
				break;
			}
			case Guest:{
				int secim;
				printf("\nHerhangi bir kaydiniz bulunmamaktadir. Kayit yaptirmak icin 1'e baisiniz :");
				scanf("%d",&secim);
				if(secim != 1) break;
				else{
					CustomerKayit(&headPerson,person);
					PrintPersonList(headPerson);
				}
				break;
			}
		}

		printf("\nDevam etmek icin 1'e basin ");
		scanf("%d",&a);
	}
	AddBookListToFile(headBook,"Books.bin");
	AddPersonListToFile(headPerson,"Persons.bin");
	return 0;
}

