#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#define SIZE1 500
#define SIZE2 100
struct date{
	int year;
    int month;
    int day;
}today;
struct Book_info{
	 char ISBN[11];//No change in text,shape, binding, does not cause a new ISBN.For the ISBN, 10 digits are considered.
     char bookname[30];
     char authorname[30];
     char author_familyname[30];
     int Available_in_the_library;//Number of books available in the library and not lented to anyone.
     int Total_number;//The total number of books by counting the books that were borrowed .
}book[SIZE1]={0};
struct borrow_book{
    char bookname[30];
    char authorname[30]; 
	char author_familyname[30];
    char ISBN[11];
	struct date Lend_date;
	struct date Return_date	;
};
struct Library_member_information{
	char name[30];
	char last_name[30];
	int membership_number;
	int birthyear;
	struct borrow_book  my_books[5];	
}member[SIZE2]={0};
int menu();
void init_list(),load(),print(),enter_member(),enter_book(),lenting(),list_of_books(), show_borrowed_books(),taking_back(),show_members(),show_books(),save();
void gotoxy(int x, int y);
char give_key();

//*********************************************************************************************************************************************
int main(){

	printf("Enter today's date: \n");//To display the date at the top of each page
	printf("\n");
	printf("year:");
	scanf("%d",&today.year);
	printf("\nmonth:");
	scanf("%d",&today.month);
	printf("\nday:");
	scanf("%d",&today.day);
	
	
	load();//To loading file information
	
	
	for(;;){  
	
	print();//To display information including today's date and number of books and the number of members at the top of each page
	
	switch(menu()){
		case 1:enter_member();break;
		case 2:enter_book();break;
		case 3:lenting();break;
		case 4:show_borrowed_books();break;
		case 5:taking_back();break;
		case 6:show_members();break;
		case 7:show_books();break;
		case 8:save();break;
		case 9:save();/*This function is for saving program information in  files*/system("cls");gotoxy(1,1);printf("<<<<\a\a\aData saved>>>>");exit(0);
		case 10:system("cls");exit(0);
		default:gotoxy(1,25);printf("!!!invaliad key!!!press a key to continue...");getch();break;
			
	    }//end of switch
	
	}//end of infinite loop

	return 0;
	
}

//*********************************************************************************************************************************************
//To empty variables before loading file information
 void init_list(){
 	register int i;
 	for(i=0;i<SIZE1;i++)
 		book[i].bookname[0]='\0';
 	for(i=0;i<SIZE2;i++)
 	    member[i].name[0]='\0';
 }
 //********************************************************************************************************************************************
void load(){
	
 	FILE *fm,*fb;//fm:File to save members information//fb:File to save book information
 	register int i,j;
 	
 	fb=fopen("C:book.dat","r+b");
 	if(!fb){
 		printf("\ncannot open file press a key...");
 		getch();
	 }
	 
 	fm=fopen("C:member.dat","r+b");
 	if(!fm){
 		printf("\ncannot open file press a key...");
 		getch();
	 }
	 	 
	 init_list();
	 for(i=0;i<SIZE1;i++){
	 	fread(&book[i],sizeof(struct Book_info),1,fb);
		 }
		 for(j=0;j<SIZE2;j++){
		 	fread(&member[j],sizeof(struct Library_member_information),1,fm);
		 }
		 fclose(fb);
		 fclose(fm);
 }
  //********************************************************************************************************************************************
void print(){
	register int i,j;
	int booknum=0,membernum=0;
	
	system("cls");
	
	for(i=0;i<SIZE1;i++)
	 	if(book[i].bookname[0]){
	 		booknum+=book[i].Available_in_the_library;
		 }
	 	
    for(j=0;j<SIZE2;j++)
		if(member[j].name[0])
		membernum++;
    printf("number of books:%d       number of members:%d     today date:%d/%d/%d",booknum,membernum,today.year,today.month,today.day);
    printf("\n----------------------------------------------------------------------");
}
 //********************************************************************************************************************************************
char give_key(){ 
    char ch;
  	
	ch=getch();	
	while(ch!='1' && ch!='2'){
	    printf("\n\n invaliad key!!!!");
	    ch=getch();
	    }
	    return ch;
}
//*********************************************************************************************************************************************
void enter_member(){
	register int i;
	char ch='1';
	while(ch=='1'){
	
    print();
    
	for(i=0;i<SIZE2;i++)//To find the first blank space
	 if(member[i].name[0]=='\0')
	 break;
	 
	 if(i==SIZE2){
	 	gotoxy(34,2);
	 	printf("Full!press a key...\n");	
	 }
	 else{
     printf("\n\nfirst name:");
     scanf("%s",member[i].name);
     printf("\nLast name:");
     scanf("%s",member[i].last_name);
     printf("\nbirthyear:");
     scanf("%d",&member[i].birthyear);
	 member[i].membership_number=i+9710;		
	 }
	 
	 print();
	 
	 gotoxy(1,2);
	 printf("his/her membership number:%d\n\n",member[i].membership_number);  
	 
	 printf("\n press a key :  1)Continue  2)Return to main page");
	 
     ch=give_key();
     
     }//end of while
}
//*******************************************************************************************************************************************************
void enter_book(){
	register int i;
	char isbn[11],ch='1';
	int check=0;//to determine whether the program has been entered into a loop and if or not
	
	while(ch=='1'){
		
	print();
	check=0;
	
	printf("\n\nEnter ISBN:");
	scanf("%s",isbn);
	
	for(i=0;book[i].bookname[0]!='\0'&& i<SIZE1;i++)
	
	   {
	      if(strcmp(book[i].ISBN,isbn)==0)
	       {check=1;
	        if(book[i].Total_number==5)
	           printf("\n\n!!!ERROR!The maximum number of a samebook is five.!!!\n");
	   
	        else{
	         book[i].Total_number++;
	         book[i].Available_in_the_library++;
	         printf("\n\nThe book information is already saved with this ISBN.\n\nThe number of books in the library increased.\n");
	         }
	   
	      break;
	     
	       } 
		}//end of for
		
	if(i==SIZE1)
	{ printf("\n\nFull!!press a key to continue...\n");
	  getch();
	  break;//Exit from infinite loop
	}
	
	if(check==0){//When check is equal to zero, this book information is not previously saved.

	strcpy(book[i].ISBN,isbn);
	
	printf("\nBook name:");
    scanf("%s",book[i].bookname);
    
    printf("\nAuthor firstname:");
    scanf("%s",book[i].authorname);
    
    printf("\nAuthor familyname:");
    scanf("%s",book[i].author_familyname);
    
    book[i].Total_number++;
	book[i].Available_in_the_library++;
	
	}
	 printf("\npress a key :  1)Continue  2)Return to main page");
     ch=give_key(); 
 
  }//end of while
   
 }
//************************************************************************************************************************************************
void lenting(){
	register int i,j;
	int id,check=0,num=0;//num is number of books borrowed by a member
	char isbn,ch='1',name[30],fname[30],bname[30];//name:first name of author//fname:family name of author//bname:name of book
	print();
	
	gotoxy(1,2);
	printf("Enter your membership number:");
	scanf("%d",&id);
	
	    for(i=0; member[i].name[0]!='\0';i++){
		  if(id==member[i].membership_number){
			check=1;//if check==1 means that exist a member with this id
	        break;
			}	
		}
		
		if(check==0)
		printf("\nMember with this membership number is not exist!!!!press a key to continue...\n");
		
		else{
		 	
		 while(ch=='1'){
			
			for(j=0;j<5;j++)
		      if(member[i].my_books[j].bookname[0]!='\0')
		       num++;
		    	
		
		    if(num==5)
		    {printf("\nShe/He can not borrows books more than five!press a key to continue...\n");
		     break;//Geting out of the while
			 }
		    else
	       {
		    list_of_books();//To display available books in the library
		    
	
		    printf("\n\n\nEnter name of book you want: ");
		    scanf("%s",bname);
		    printf("\n*********************************************************\n");
		    printf("\n\nEnter  firstname of author of book you want:");
		    scanf("%s",name);
		    printf("\n*********************************************************\n");
		    printf("\n\nEnter  familyname of author of book:"); 
		    scanf("%s",fname);  
		    printf("\n*********************************************************\n");  
		    
		  //printf("\nEnter ISBN:");
		  // scanf("%s",member[i].my_books[num].ISBN);
          //printf("\n********************************\n");  

          check=0;//check:check==1 means book with this information is available in the lib/check==2:exist in lib but available in the lib==0//
          //check==0 book with this information is not existed in lib may be incorrect when entering information.
		  for(j=0;book[j].bookname[0]!='\0' && j<SIZE1;j++){
				if(strcmp(book[j].bookname,bname)==0 && strcmp(book[j].authorname,name)==0 && strcmp(book[j].author_familyname,fname)==0)
				{   if(book[j].Available_in_the_library!=0)
					{book[j].Available_in_the_library--;
					 check=1;
					}
					else
					{printf("\n!!!!!!!!!!Available_in_the_library=0!!!!!!!!!!!!!\n");
					 check=2;
					}
					
					break;//Geting out of the for
				}
			} 
			
			if(check==0)
			printf("\nThere is no book in the library with this specification entered!!!\n "); 
			
			else if(check==1){
			//Copy the information in the section for members books
			strcpy(member[i].my_books[num].bookname,bname);
			strcpy(member[i].my_books[num].authorname,name);
			strcpy(member[i].my_books[num].author_familyname,fname);
			strcpy(member[i].my_books[num].ISBN,book[j].ISBN);
			
			
			//Specify the date of the borrowing and returning 
		    member[i].my_books[num].Lend_date.year=today.year;
		    member[i].my_books[num].Lend_date.month=today.month;
		    member[i].my_books[num].Lend_date.day=today.day;
		   
		   if(today.day>=25 && today.month<=6){
		   	member[i].my_books[num].Return_date.year=today.year;
		   	member[i].my_books[num].Return_date.month=today.month+1;
		   	member[i].my_books[num].Return_date.day=7-(31-today.day);
		   }
		   else if(today.day>=24 && 11>=today.month && today.month>=7){
		   	member[i].my_books[num].Return_date.year=today.year;
		   	member[i].my_books[num].Return_date.month=today.month+1;
		   	member[i].my_books[num].Return_date.day=7-(30-today.day);
		   }
		   else if(today.month==12&& today.day>=23){
		   	member[i].my_books[num].Return_date.year=today.year+1;
		   	member[i].my_books[num].Return_date.month=1;
		   	member[i].my_books[num].Return_date.day=7-(29-today.day);
		   }
		  else{
		  	member[i].my_books[num].Return_date.year=today.year;
		  	member[i].my_books[num].Return_date.month=today.month;
		  	member[i].my_books[num].Return_date.day=today.day+7;
		  }
		  
		  printf("\n\n*****Return date book****\n%d/%d/%d",member[i].my_books[num].Return_date.year,member[i].my_books[num].Return_date.month,member[i].my_books[num].Return_date.day);
		   }
		  
		 }		
		 
		 printf("\n press a key :  1)Continue  2)Return to main page");
         ch=give_key();
		
		}//end of while	
	}//end of else
    getch();

}
//*************************************************************************************************************************************************
void list_of_books(){
	register int i;
	int *m;
	m=(int *)malloc(sizeof(int));
	*m=0;
	print();
	printf("\n\n<<<list of available books>>>\n");
	printf("\n Name                   authorname/familyname        ISBN          available ");
	printf("\n ----                   ---------------------        ----          --------- ");
	for(i=0;book[i].Total_number!=0 ;i++){
		if(book[i].Available_in_the_library!=0){
		
			gotoxy(1,*m+7);
			printf("%s",book[i].bookname);
			
			gotoxy(25,*m+7);
			printf("%s/%s",book[i].authorname,book[i].author_familyname);
			
			gotoxy(50,*m+7);
			printf("%s",book[i].ISBN);
			
			gotoxy(71,*m+7);
			printf("%d",book[i].Available_in_the_library);
			gotoxy(0,*m+8);
		printf("____________________________________________________________________________");
			(*m)+=2;
		
	}
	}
	free(m);
	
}
//********************************************************************************************************************************************************
void show_borrowed_books(){
	int i,*m;
	int id,check=0,k;
	char ch='1';
	m=(int *)malloc(sizeof(int));
	
	while(ch=='1')
	{*m=0;
	 check=0;
	 print();
	 gotoxy(1,2);
	 printf("Enter your membership number:");
	 scanf("%d",&id);
	 for(i=0; member[i].name[0]!='\0';i++){
		if(id==member[i].membership_number){
			check=1;
	        break;
			}	
		}
		if(check==0)
		printf("\nMember with this membership number is not exist!!!!\n");
		else{
			k=i;//To keep the member number
			printf(" \n\n<<<List of her/his books>>>\n");
			printf("\n Name          authorname               ISBN          lendingdate   return date ");
			printf("\n ------------------------------------------------------------------------------");
			for(i=0;i<5;i++){
			if(member[k].my_books[i].bookname[0]!='\0'){
			gotoxy(1,*m+10);
			printf("%s",member[k].my_books[i].bookname);
			
			gotoxy(15,*m+10);
			printf("%1.1s.%s",member[k].my_books[i].authorname,member[k].my_books[i].author_familyname);
			
			gotoxy(38,*m+10);
			printf("%s",member[k].my_books[i].ISBN);
			
			gotoxy(55,*m+10);
			printf("%d/%d/%d",member[k].my_books[i].Lend_date.year,member[k].my_books[i].Lend_date.month,member[k].my_books[i].Lend_date.day);
			
			gotoxy(68,*m+10);
			printf("%d/%d/%d",member[k].my_books[i].Return_date.year,member[k].my_books[i].Return_date.month,member[k].my_books[i].Return_date.day);
			gotoxy(0,*m+11);
			printf("_______________________________________________________________________________");
			(*m)+=2;
		   	}	
				
		  }
		}
		
		 printf("\n press a key :  1)Continue with other member  2)Return to main page");
         ch=give_key();
		 }free(m);
}

//***********************************************************************************************************************************************************
void taking_back(){
	int i,*m,num=0;
	int id,check=0,k;
	char ch='1',isbn[11];
	m=(int *)malloc(sizeof(int));
	*m=0;
	while(ch=='1')
	{
	 print();check=0;
     gotoxy(0,2);
	 printf("Enter your membership number:");
	 scanf("%d",&id);
	 for(i=0; member[i].name[0]!='\0';i++){
		if(id==member[i].membership_number){
			check=1;
	        break;
			}	
		}
		k=i;//To keep the member number
		if(check==0)
		printf("\nMember with this membership number is not exist\n");
		
		else{
			num=0;
			for(i=0;i<5;i++)
				if(member[k].my_books[i].bookname[0]!='\0')
				num++;
			
			if(num==0)
			{printf("\n\n!!!She/He  has not borrowed any books!!!\n");
			 ch='2';}	
			

			
			while(ch=='1'){
			(*m)=0;print();
			
			printf("\n\n<<<List of her/his books>>>\n");
			printf("\n Name               authorname                  ISBN               return_date");
			printf("\n---------------------------------------------------------------------------------");
			for(i=0;i<5;i++){
			if(member[k].my_books[i].bookname[0]!='\0'){
			gotoxy(1,*m+7);
			printf("%s",member[k].my_books[i].bookname);
			
			gotoxy(20,*m+7);
			printf("%1.1s.%s",member[k].my_books[i].authorname,member[k].my_books[i].author_familyname);
			
			gotoxy(45,*m+7);
			printf("%s",member[k].my_books[i].ISBN);
			
			gotoxy(68,*m+7);
			printf("%d/%d/%d",member[k].my_books[i].Return_date.year,member[k].my_books[i].Return_date.month,member[k].my_books[i].Return_date.day);
			gotoxy(0,*m+8);
			printf("______________________________________________________________________________");
			(*m)+=2;}
			}//end of for
			
            
			check=1;//check==1 means ISBN that entered is not for books that he or she borrrowed.
			while(1){
			printf("\n\nEnter ISBN of book you want take it back:");
			scanf("%s",isbn);
			for(i=0;i<5;i++){
				if(strcmp(isbn,member[k].my_books[i].ISBN)==0 && member[k].my_books[i].bookname[0]!='\0' ){//baraye inke momkene ghablan esmesho \0 karde basham
					check=0;break;
				}
			   }
			   if(check)
			   printf("\nThe ISBN you entered is of no book that he borrowed!!\n");//it does not get out of the infinite loop	Unless you enter the code correctly. 	
			   else
			   break;
			}

			//taking back the book
			for(i=0;book[i].bookname[0]!='\0' && i<SIZE1;i++){
				if(strcmp(isbn,book[i].ISBN)==0)
				{   printf("\n<<<successfully returned!>>>");
					book[i].Available_in_the_library++;
					break;
				}
			}
			
			//Checking return date with today's date
			for(i=0;i<5;i++){
				if(member[k].my_books[i].bookname[0]!='\0'&& strcmp(member[k].my_books[i].ISBN,isbn)==0)
				{
				  if(member[k].my_books[i].Return_date.day<today.day  || member[k].my_books[i].Return_date.month<today.month || member[k].my_books[i].Return_date.year<today.year){
					printf("\n\n!!!He/She returned the book later than the specified date of return!!!\n");	
					}
					member[k].my_books[i].bookname[0]='\0';
					break;//ta baghiyeh ham shklaro pak nakone chon momkene az ye ketab chand ta bashe va bekhad yeki ro bar gardoone
				}
			}
			//gotoxy(0,2*i+8);
			//printf("_________________________________________________________________");
				
		 printf("\n\n press a key :  1)Continue 2)Get out of this member's page");
         ch=give_key();
		 }//end of while
		}//end of else
		 printf("\n \npress a key :  1)Continue with other member 2)Return to main page");//
         ch=give_key(); 
		 
		 }//end of while
		 free(m);
}

//*********************************************************************************************************************************************************   
void  show_members(){
	register int i;
	char ch;
	
	
	print();
	gotoxy(1,3);
	printf("membership              name                    lastname ");
	printf("\n------------------------------------------------------------");
	for(i=0;i<SIZE2 && member[i].name[0]!='\0';i++){
	        gotoxy(1,2*i+5);
			printf("%d",member[i].membership_number);
			
			gotoxy(25,2*i+5);
			printf("%s",member[i].name);
			
			gotoxy(50,2*i+5);
			printf("%s",member[i].last_name);
			gotoxy(0,2*i+6);
			printf("____________________________________________________________");
	}printf("\n\n\nif you want to leave this page press enter");ch=getch();
	
	while(ch!='\r'){
		
         printf("\n\ninvaliad key!if you want to leave this page press enter");	
	     ch=getch();
	}
	
}
//***********************************************************************************************************************************************************
void  show_books(){
	register int i;
	char ch;
	
	print();
	gotoxy(1,3);
	printf("ISBN             name            author       Available in lib    Total num    ");
	printf("\n-----------------------------------------------------------------------------");
	for(i=0;i<SIZE1 && book[i].bookname[0]!='\0';i++){
	        gotoxy(1,2*i+6);
			printf("%s",book[i].ISBN);
			
			gotoxy(17,2*i+6);
			printf("%1.13s",book[i].bookname);
			
			gotoxy(32,2*i+6);
			printf("%1.1s",book[i].authorname);printf(".%s",book[i].author_familyname);
			gotoxy(50,2*i+6);
			printf("%d",book[i].Available_in_the_library);
			gotoxy(68,2*i+6);
			printf("%d",book[i].Total_number);	
			printf("\n_____________________________________________________________________________");
	}
	 printf("\n\n\nif you want to leave this page press enter");ch=getch();
	 
	 while(ch!='\r'){
	 	 
         printf("\n\ninvaliad key!if you want to leave this page press enter");
	     ch=getch();
	    }
	 
}
//*********************************************************************************************************************************************************
void save(){
	FILE *fb,*fm;
 	register int i,j;
 	fb=fopen("C:book.dat","r+b");
 	if(!fb){
 		printf("\ncannot open file press a key...");
 		getch();
	 }
	 fm=fopen("C:member.dat","r+b");
	  	if(!fm){
 		printf("\ncannot open file press a key...");
 		getch();
	 }
	 for(i=0;i<SIZE1;i++){
	 	if(book[i].bookname[0])
	 	fwrite(&book[i],sizeof(struct Book_info),1,fb);
	 	}
		 for(j=0;j<SIZE2;j++){
		 	if(member[j].name[0])
		 	fwrite(&member[j],sizeof(struct Library_member_information),1,fm);
		 	}	 	
         fclose(fb);
		 fclose(fm);
}

//*********************************************************************************************************************************************************

 int menu(){
 	int key;
 	gotoxy(2,5);
 	printf("1)Add new member");
 	gotoxy(2,7);
 	printf("2)Add new book");
 	gotoxy(2,9);
 	printf("3)Lend book to library member");
 	gotoxy(2,11);
 	printf("4)Show books that are borrowed to a library member");
 	gotoxy(2,13);
    printf("5)Take a book that was lent back");
 	gotoxy(2,15);
 	printf("6)Display the members of library list");
 	gotoxy(2,17);
 	printf("7)Display the list of books\n");
 	gotoxy(2,19);
 	printf("8)Save data");
 	gotoxy(2,21);
 	printf("9)Exit and Save new data");
 	gotoxy(1,23);
 	printf("10)Exit without saving new data");
 	gotoxy(2,3);
	printf("Enter your choice:");
	scanf("%d",&key);
 	return key;
 }
 
 //********************************************************************************************************************************************************
 void gotoxy(int x, int y)
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
}//
