#include <stdio.h>
#include <stdlib.h>
// ((( d(^.^)b )))
typedef int BOOL;
#define TRUE 1
#define FALSE 2

struct Inventory
{
	unsigned long int partNo;
	int quanity;
	float price;
	
	struct Inventory *next;
};

struct Inventory *first;

void addPartBegning();
void printList();
void findPart();
void modPart();
void removePart();
void writeListToFile();
void readFromFile();
void insert(struct Inventory *);
void menu(char[]);

int main()
{
	char menuSelect[10]	;
	BOOL running = TRUE;	
	//I noticed by setting first to NULL here you don't have to check if first is null to set first node->next = to NULL 
	//I don't know if this is a bad practice
	first = NULL;

	do
	{	
		menu(menuSelect);
		if(strncmp(menuSelect,"view") == 0) printList();
		else if(strncmp(menuSelect, "add") == 0) addPartBegning();
		else if(strncmp(menuSelect,"find") == 0) findPart();
		else if(strncmp(menuSelect,"mod") == 0) modPart();
		else if(strcmp(menuSelect,"remove") == 0) removePart();
		else if(strcmp(menuSelect,"write") == 0) writeListToFile();
		else if(strcmp(menuSelect,"file") == 0) readFromFile();
		else if(strcmp(menuSelect,"exit") == 0) running = FALSE;
		else
		{
			printf("\nInvalad entery!\n");
			continue;
		}
		
	}while(running==TRUE);
	printf("Thank you have a nice day! ");
		
	return 0;
}

void addPartBegning()
{
	struct Inventory *temp = first;
	unsigned long int partNumber;
	int quant;
	float prices;
	BOOL partAlreadExist = FALSE;
	
	/*
	insert function searches for the correct position to place node
	bassed on partNo. starting from smallest to largest
	*/	
	printf("Enter a part number number \n");
	scanf("%ld",&partNumber);		
	printf("\nenter quantity ");
	scanf("%d",&quant);
	printf("\nEnter a price");
	scanf("%f",&prices);
		
	if(partAlreadExist == FALSE)
	{	
	//alocate memory to size of struct Inventory then cast the value malloc returns to 
	//type to inventroy pointer 
		struct Inventory *curr = (struct Inventory*)malloc(sizeof(struct Inventory));	
		curr->partNo = partNumber;
		curr->quanity = quant;
		curr->price = prices;		
				
		insert(curr);					
   }
   else
   {
   		printf("\nThat part already exist in the databass\nPess m in the menu to modify part\n");
   }

}

void printList()
{
	system("cls");
	struct Inventory* curr = first;
	printf("\n");
	while(curr != NULL)
	{
		printf("\n Part Number: %d", curr->partNo);
		printf("\n Part Quantity: %d", curr->quanity);
		printf("\n Part Price: %.2f\n", curr->price);	
			
		curr = curr->next;				
	}
	printf("\n");
}

void findPart()
{
	struct Inventory *curr = first;
	unsigned long int searchPart;
	
	printf("Enter part No.: ");
	scanf("%d",&searchPart);
	
	while (curr != NULL)
	{
		
		if(curr->partNo == searchPart)
		{
			printf("\n Part Number: %d", curr->partNo);
			printf("\n Part Quantity: %d", curr->quanity);
			printf("\n Part Price: %.2f", curr->price);	
			printf("\n");

			return;
		}
		
		curr = curr->next;
	}
	system("pause");
}

void modPart()
{
	struct Inventory *curr = first;
	unsigned long int searchPart;
	char changevalue;
	BOOL partFound = FALSE;
	
	printf("Modify part No. ");
	fflush(stdin);
	scanf("%d",&searchPart);
	
	while(curr != NULL)
	{
		if(curr->partNo == searchPart)
		{	
			partFound = TRUE;
				
			printf("\nP for price\nQ for quantity\n-1 To exit");
			fflush(stdin);
			scanf("%c",&changevalue);
			if(changevalue < 96)
			{
				changevalue += 32;
			}
			switch(changevalue)
			{
				case 'p':
					printf("\nchange item %ld Prince from %.2f: ",curr->partNo,curr->price);
					scanf("%f",&curr->price);
					printf("prince of %d has been changed to %.2f\n ",curr->partNo,curr->price);
					system("pause");
					break;
				case 'q':
					printf("\nChange item %ld quantity from %d: ",curr->partNo,curr->quanity);
					scanf("%d",&curr->quanity);
					printf("\nItem %ld quantity change to %d\n",curr->partNo,curr->quanity);
					system("pause");
					break;
				default:
					printf("\nInvaled change option");
					continue;					
			}			
		}
		curr = curr->next;
	}
	if(partFound == FALSE)
	{
		printf("\nCould not find part No.");
	}
	system("cls");	
}

void removePart()
{
	struct Inventory *curr = first, *prev;
	unsigned long int remove;
	BOOL partFound = FALSE;
	
	printf("\n Enter part number to remove: ");
	
	fflush(stdin);
	scanf("%ld",&remove);
	
	while(curr != NULL)
	{
		if(curr->partNo == remove)
		{
			partFound = TRUE;
			//If list is now empty
			if((curr == first)&&(first->next == NULL))
			{
				free(curr);
				{
					first = NULL;
					break;
				}
			}
			//Removing first and making next first
			else if((curr == first)&&(first->next != NULL))	
			{
				first = curr->next;
				free(curr);				
				break;
			}	
			//If current is last prev is now last, last is now NULL	
		 	else if(curr->next == NULL)
			{
				prev->next = NULL;
				free(curr);	
				break;					
			}
			//if next current location is not NULL Previous next now == current Next
			else if(curr->next != NULL)
			{
				prev->next = curr->next;
				free(curr);	
				break;
			}
		}							
		prev = curr;
		curr = curr->next;
		
	}	
	
	if(partFound == FALSE)
	{
		printf("\nThat part can't be found.");
	}
	else
	{
		printf("\n %ld has been removed",remove);
	}
}

void menu(char menuSelect[])
{

	int i = 0;
	fflush(stdin);
	
	printf("\nview for- View part list ");
	printf("\nAdd for- Add new part ");
	printf("\nFind for- Find part ");
	printf("\nMod for- Modify part");
	printf("\nRemove for- Remove part");
	printf("\nSave for- save List to file");
	printf("\nFile for- Add list from file");
	printf("\nExit to exit\n");
	
	gets(menuSelect);
	while(menuSelect[i]!='\0')
	{
		if(menuSelect[i] < 96)
		{
		menuSelect[i] += 32;
		}
		i++;
	}
}


void insert(struct Inventory *insert)
{
	struct Inventory *curr = first, *temp;
	
	do
	{	
		if(first == NULL)
		{	
			insert->next = first;
			first = insert;
			break;
		}
		else if(insert->partNo == curr->partNo)
		{
			printf("Part number %d already exist: ",curr->partNo);
			free(insert);
			break;
		}
		else if(curr->next != NULL)
		{
			if(insert->partNo == curr->next->partNo)
			{
				printf("Part number %d already exist: ",curr->partNo);
				free(insert);
				break;		
			}
		}
		else if((insert->partNo >= curr->partNo) && (curr->next == NULL))
		{
			curr->next = insert;
			insert->next = NULL;	
			break;
		}		
		else if((insert->partNo >= curr->partNo) && (insert->partNo <= curr->next->partNo))
		{		
			temp = curr;
			insert->next = curr->next;
			curr->next = insert;
			break;	
		}
		else if((insert->partNo <= first->partNo) && (curr == first))
		{
			temp = insert;						
			insert = first;			
			first = temp;
			first->next = insert;	
			break;	
		}
		curr = curr->next;
	}while(curr != NULL);			
}

void writeListToFile()
{	
	//Oopen file from given location
	//Writing file as binarry the internet told me to...
	FILE *fp = fopen("C:/Temp/new.bin","wb");
	
	if(fp != NULL)
	{
		 struct Inventory *curr = first, *temp;
		 
		 while(curr != NULL)
		 {	 
		 	//Setting file stream offset to 0 and seeking until end of file			 	
			fseek(fp, 0, SEEK_END);	
			//This sets curr->next to NULL temp holds these values
			//Had issues with sorting without doing this
			temp = curr->next;
		 	curr->next = NULL;
			//Writing curr to file, the number of bytes = size of struct, writing one of these from pointfile or pf
		 	fwrite(curr, sizeof(struct Inventory), 1, fp);
		 	printf("\nWriting %d  to file ",curr->partNo);
		 	
		 	curr->next = temp;
		 	curr = curr->next;
		 }
		 
	fclose(fp);		 
	}
	else 
	{
		printf("file opdn error\n");
	}
}

void readFromFile()
{
	long fileSize;
	int numEnteries,i; 
		
	FILE *fp; 
	//Were reading binarry file because we wright as binarry
	fp = fopen("C:/Temp/new.bin","rb");
	
	// This block tells the computer how many total bytes are in the file
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	
	//we rewind back to the begining of the file
	rewind(fp);
	
	//we take total file bytes  devide that by are struct size and we get the size of each entery!
	numEnteries = (int)(fileSize / (sizeof(struct Inventory)));
	
	//Takes size of are struct * i which will set are seek to the correct spot to read!
	for(i=0;i<numEnteries;i++)
	{
		fseek(fp,(sizeof(struct Inventory) * i),SEEK_SET);
		
		struct Inventory *curr = (struct Inventory*)malloc(sizeof(struct Inventory));	
		
		fread(curr,sizeof(struct Inventory),1,fp);
		insert(curr);					
	}	
}

void stingToUpper(char theString[])
{
	
	int i = 0;
	while(theString[i] != '\0')
	{
		if(theString[i] > 96)
		{
			theString[i] - 32;
		}
	}
}

