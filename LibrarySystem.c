#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Defining structures of customers, books and rented books.
typedef struct customer{
  int C_ID;
  char name[100];
  char surname[100];
  int age;
  int wallet;
}customer;

typedef struct book{
  int B_ID;
  char name[100];
  char author[100];
  int age_limit;
  int price_per_week;
  char rented[3];
}book;

typedef struct rented{
  int R_ID;
  int C_ID;
  int B_ID;
  char rented_date[100];
  int week;
}rented;

int C_ID;
int B_ID;
char chr;
//Creadting methods.
void createNewCustomer();
void createNewEntry();
void depositMoney();
void addNewBook();
void rentBook();
void deliveryBook();
void burnBook();
void updateCustomer();
void updateBook();
void listCustomerWhoRentBook();
void listCustomer();
void listBook();

//For main method, I just write main menu and method call operator.
int main(void) {
  int choose;
  int exitCode = 1;

  printf("\nWelcome to Library Booking System"); 
  while(exitCode == 1){
    
    printf("\n----- Main Menu -----\n");
    printf("1 - Create New Customer\n");
    printf("2 - Deposit Money to the Customer\n");
    printf("3 - Add New Book\n");
    printf("4 - Rent A Book\n");
    printf("5 - Delivery A Book\n");
    printf("6 - Burn Book\n");
    printf("7 - Update Customer Information\n");
    printf("8 - Update Book Information\n");
    printf("9 - List of Customers Who Rent a Book\n");
    printf("10 - List of Customers\n");
    printf("11 - List of Books\n");
    printf("12 - Exit\n");
    printf("Please choose an action (1-12): ");
    scanf("%d", &choose);
    
    
    if(choose == 1){
      createNewCustomer();
    }



    if(choose == 2){
      depositMoney();
    }



    if(choose == 3){
      addNewBook();
    }



    if(choose == 4){
      rentBook();
    }



    if(choose == 5){
      deliveryBook();
    }



    if(choose == 6){
      burnBook();
    }



    if(choose == 7){
      updateCustomer();
    }



    if(choose == 8){
      updateBook();
    }



    if(choose == 9){
      listCustomerWhoRentBook();
    }



    if(choose == 10){
      listCustomer();
    }



    if(choose == 11){
      listBook();
    }



    if(choose == 12){
      exitCode = 0;
      printf("Closing the Program...\n");
    }
  }
  return 0;
}


//---------------------- This method is creating customers ----------------------.

void createNewCustomer(){
  //I am opening customers.txt file with append (because I want to add cust. info) and read (because I want to calculate how many cust. do I have).
  FILE *fp = fopen("customers.txt","a");
  FILE *fpr = fopen("customers.txt","r");

  if ((fpr = fopen ("customers.txt", "r")) == NULL) {
    printf("No file found named '%s'!", "customers.txt");
    exit(1);
  }

  //These are the variables that I am using to find user's input is same with my data(Because it is impossible to save a customer who has the same name and surname).
  int controller = 0;
  char line[256];
  char *token;
  char *tokenName;
  char *tokenSurname;

  //I am using structer to save my data.
  struct customer customer;

  //This part is calculating how many customers do I have. Because I need to know C_ID before record the main data (cust. name, surname, age, wallet). Looking at this I can say that if I have 7 customer in text file next one's C_ID will be 8.
  C_ID = 1;
  while(!feof(fpr)){
    chr = fgetc(fpr);
    if(chr == '\n'){
      C_ID++;
    }
  }
  //Setting structer of C_ID as C_ID that I found from previous code block.
  customer.C_ID = C_ID;
  //Asking user's name, surname, age and money that he/she has.
  printf("\n------ Creating New Customer ------\n");
  printf("Name: ");
  scanf("%s", customer.name);

  printf("Surname: ");
  scanf("%s", customer.surname);
  
  printf("Age: ");
  scanf("%d", &customer.age);
  
  printf("Money: ");
  scanf("%d", &customer.wallet);
  
  //I am setting pointer to the first character of the text. I need this because I used C_ID block. If I don't use this code I will get "null" instead of name and surname.
  fseek(fpr, 0, SEEK_SET);
  //This code block is finding user's name and surname which is given by input is same or not with the previous names and surnames in the text file. To do this I am using strtok code because I am storing datas as C_ID-name-surname-age-money. So I can find name and surname via spliting "-" symbol.
  while (fgets(line, sizeof(line), fpr)) {
    char *token = strtok(line, "-"); 
    tokenName = strtok(NULL, "-");
    tokenSurname = strtok(NULL, "-");
    if (strcmp(tokenName, customer.name) == 0 && strcmp(tokenSurname, customer.surname) == 0){
      //If name and surname are the same, I am changing controller from 0 to 1.
      controller = 1;
    }
  }

  //If controller is 1 then I found same name and surname. I am printing that This user is already registered and finishing the code.
  if (controller == 1){
    printf("This user is already registered.\n");
  }
  //If controller still 0 then I couln't find any name and surname which are same with my data, I am writting user's input as C_ID-name-surname-age-money.
  else{
    fprintf(fp, "%d-%s-%s-%d-%d\n", customer.C_ID, customer.name, customer.surname, customer.age, customer.wallet);
      printf("You have been successfully registered.\n");
  }
      
  printf("-----------------------------------\n");
  //After I finished my metthod, I am closing the FILE's.
  fclose(fp);
  fclose(fpr);
}


//---------------------- This method is Depositing Money ----------------------.

void depositMoney(){
  //I am opening customers.txt file as read form.
  FILE* fpr = fopen("customers.txt", "r");
  if ((fpr = fopen ("customers.txt", "r")) == NULL) {
    printf("No file found named '%s'!", "customers.txt");
    exit(1);
  }
  //Creating variables.
  int id;
  int money;
  int i = 0;
  char line[256];
  char str[256];
  char ids;
  char wallets;
  int linectr = 0;
  char newln[256];
  char buffer[100];
  char newline[100];
  char arr[] = "";
  char *ptr[5];

  //Using structer to save data.
  struct customer customer;
  int wallet;
  
  //Asking user's id and money to deposit.
  printf("\n-------- Depositing Money --------\n");
  printf("Please Give an ID to Deposit Money: ");
  scanf("%d", &id);
  printf("How Much Do You Want to Deposit? ");
  scanf("%d", &money);
  
  //Finding money part of user in text file. So I can deposit it and save it again. T o save it I am using strncat code for adding all info's into a string. C_ID-name-surname-age-money.
  while (fgets(line, sizeof(line), fpr)) {
    i++;
    if(i == id){
      char *token = strtok(line, "-");
      for(int i = 0; i < 4; i++){
        ptr[i] = token;
        token = strtok(NULL, "-");
        strncat(arr, ptr[i], 100);
        strncat(arr, "-", 100);
        
      }
      //I got money but it is string. I am chaning it to int and I deposit money.
      wallet = atoi(token);
      wallet += money;
      
    }
  }
  //Before I add wallet data to my string (C_ID-name-surname-age-money), I need to convert it to string. I cannot add it as int.
  sprintf(&wallets, "%d", wallet);
  strncat(arr, &wallets, 100);
  strncat(arr, "\n", 100);

  //For update customers.txt file, I need to create a temporary file, add all my data in it then change its name.
  FILE* a = fopen("customers.txt", "r");
  FILE* fTemp = fopen("temp.txt", "w");

  //I am adding all my customers.txt data and updated customer money to temp.txt.
  int count = 0;
  while ((fgets(buffer, 256, a)) != NULL){
    count++;
    if (count == id)
      fputs(arr, fTemp);
    else
      fputs(buffer, fTemp);
  }

  //After all of that, I am closing FILE's and changing temp.txt's name as customers.txt.
  fclose(fpr);
  fclose(a);
  fclose(fTemp);
  remove("customers.txt");
  rename("temp.txt", "customers.txt");
  printf("\n%d dolar is successfully deopsited to ID %d Person\n", money, id);
}


//---------------------- This method is Adding Book ----------------------.

void addNewBook(){
  //Opening files.
  FILE *fp = fopen("books.txt","a");
  FILE *fpr = fopen("books.txt","r");

  if ((fpr = fopen ("books.txt", "r")) == NULL) {
    printf("No file found named '%s'!", "books.txt");
    exit(1);
  }

  //These are the variables that I am using to find books's input is same with my data(Because  it is impossible to save a book that already exists (same name and author).
  char line[256];
  int controller = 0;
  char *token;
  char *tokenName;
  char *tokenSurname;

  //Usingng structer to save data.
  struct book book;
  
  //Finding how mnay book do I have.
  B_ID = 1;
  while(!feof(fpr)){
    chr = fgetc(fpr);
    if(chr == '\n'){
      B_ID++;
    }
  }
  //Assinging B_ID as stucter of books ID.
  book.B_ID = B_ID;

  //Asking user's input.
  printf("\n----- Creating New Book -----\n");
  printf("Please use \"_\" (underscore) instead of space\n\n");
  
  printf("Name: ");
  scanf("%s", book.name);

  printf("Author: ");
  scanf("%s", book.author);
  
  printf("Age Limit: ");
  scanf("%d", &book.age_limit);
  
  printf("Price Per Week: ");
  scanf("%d", &book.price_per_week);

  printf("Rented (yes/no): ");
  scanf("%s", book.rented);

  //I am setting pointer to the first character of the text. I need this because I used B_ID block. If I don't use this code I will get "null" instead of name and author.
  fseek(fpr, 0, SEEK_SET);
  
  //I am finding name and author via strtok code and I am cheking that is it same with my data or not.
  while (fgets(line, sizeof(line), fpr)) {
    char *token = strtok(line, "-"); 
    tokenName = strtok(NULL, "-");
    tokenSurname = strtok(NULL, "-");
    if (strcmp(tokenName, book.name) == 0 && strcmp(tokenSurname, book.author) == 0){
      controller = 1;
    }
  }

  //If controller is 1 I already have thi book.
  if (controller == 1){
    printf("This book is already registered.\n");
  }
  //If it is not, I will record this book to books.txt.
  else{
    fprintf(fp, "%d-%s-%s-%d-%d-%s\n", book.B_ID, book.name, book.author, book.age_limit, book.price_per_week, book.rented);
      printf("Book has been successfully registered.\n");
  }

  printf("----------------------------------\n");

  fclose(fp);
  fclose(fpr);

}

//---------------------- This method is Renting Book ----------------------.

void rentBook(){

  //I used so much fopen becasue this method needs so many code block which is using fopen as read format.
  FILE *fpc = fopen("customers.txt", "r");
  FILE *fpc2 = fopen("customers.txt", "r");
  FILE *fpb = fopen("books.txt", "r");
  FILE *fpb2 = fopen("books.txt", "r");
  FILE *fpb3 = fopen("books.txt", "r");
  FILE *fpb4 = fopen("books.txt", "r");
  FILE *fprented = fopen("rented.txt", "r");
  FILE *fprenteda = fopen("rented.txt", "a");

  if ((fpc = fopen ("customers.txt", "r")) == NULL) {
    printf("No file found named '%s'!", "customers.txt");
    exit(1);
  }
  if ((fpb = fopen ("books.txt", "r")) == NULL) {
    printf("No file found named '%s'!", "books.txt");
    exit(1);
  }
  if ((fprented = fopen ("rented.txt", "r")) == NULL) {
    printf("No file found named '%s'!", "rented.txt");
    exit(1);
  }

  //I am using all structers.
  struct rented rented;
  struct book book;
  struct customer customer;

  //I need all of these variables too rent a book.
  char line[256];
  char lineArray[256];
  char lineC[256];
  char lineW[256];
  char lineP[256];
  char lineAL[256];
  char buffer[100];
  char bufferwall[100];
  char *ptr[6];
  char *ptr2[6];
  char wall[] = "";
  char *arr[6];
  char bookarr[] = "";
  int i = 0;
  int j = 0;
  int k = 0;
  int l = 0;
  int m = 0;
  int n = 0;
  char *token;
  char *tokenC;
  char *tokenP;
  char *tokenA;
  char *tokenAL;
  char *tokenB;
  int walletb;
  int B_ID;
  int C_ID;
  int R_ID;
  int last_wallet;
  int prices;
  int week;
  int age;
  int age_limit;

 //I am asking user's and book's info.
  printf("\n---------- Renting Book ----------\n");  

  printf("Please Give Book ID: ");
  scanf("%d", &B_ID);

  printf("Please Give Customer ID: ");
  scanf("%d", &C_ID);

  printf("How many week will you rent? ");
  scanf("%d", &week);

  printf("Please write rent date (dd/mm/yyyy): ");
  scanf("%s", rented.rented_date);

  //This code block is getting customer's money info.
  while (fgets(lineW, sizeof(lineW), fpc)) {
    j++;
    if(j == C_ID){
      char *tokenC = strtok(lineW, "-");
      for(int i = 0; i < 4; i++){
        ptr2[i] = tokenC;
        tokenC = strtok(NULL, "-");
        strncat(wall, ptr2[i], 100);
        strncat(wall, "-", 100);
      }
      walletb = atoi(tokenC);
      
    }
  }
  //This code block is getting customer's age info.
  while (fgets(lineC, sizeof(lineC), fpc2)) {
    l++;
    if(l == C_ID){
      char *tokenA = strtok(lineC, "-");
      for(int i = 0; i < 3; i++){
        ptr[i] = tokenA;
        tokenA = strtok(NULL, "-");
      
        
      }
      age = atoi(tokenA);
      
    }
  }
  //This code block is getting books's price per week info.
  while (fgets(lineP, sizeof(lineP), fpb)) {
    k++;
    if(k == B_ID){
      char *tokenP = strtok(lineP, "-");
      for(int i = 0; i < 4; i++){
        ptr[i] = tokenP;
        tokenP = strtok(NULL, "-");
      }
      prices = atoi(tokenP);
      
    }
  }
  //This code block is getting books's age limit info.
  while (fgets(lineAL, sizeof(lineAL), fpb3)) {
    m++;
    if(m == B_ID){
      char *tokenAL = strtok(lineAL, "-");
      for(int i = 0; i < 3; i++){
        ptr[i] = tokenAL;
        tokenAL = strtok(NULL, "-");
      }
      age_limit = atoi(tokenAL);
    }
  }

rented.C_ID = C_ID;
rented.B_ID = B_ID;
rented.week = week;

  //I am creating a book array to record all data and print it to the books.text.
  while (fgets(lineArray, sizeof(lineArray), fpb4)) {
    n++;
    if(n == B_ID){
      char *tokenB = strtok(lineArray, "-");
      for(int i = 0; i < 5; i++){
        arr[i] = tokenB;
        tokenB = strtok(NULL, "-");
        strncat(bookarr, arr[i], 100);
        strncat(bookarr, "-", 100);
      }
    }
  }
  //This is the main part of renting book I am looking rented info, price info, age limit info which I get from previous code blocks.
  while (fgets(line, sizeof(line), fpb2)) {
  i++;
  if(i == B_ID){
    token = strtok(line, "-");
    for(int i = 0; i < 5; i++){
      ptr[i] = token;
      token = strtok(NULL, "-");
    }
      
    if((strncmp(token, "no", 1) == 0)||(strncmp(token, "No", 1) == 0)||(strncmp(token, "nO", 1) == 0)||(strncmp(token, "NO", 1) == 0)){
      if(walletb >= prices*week){
        if(age >= age_limit){

          //This block is writing rented info to rented.txt.
          R_ID = 1;
          while(!feof(fprented)){
            chr = fgetc(fprented);
            if(chr == '\n'){
              R_ID++;
            }
          }
            
          fprintf(fprenteda, "%d-%d-%d-%s-%d\n", R_ID, rented.C_ID, rented.B_ID, rented.rented_date, rented.week);
          fclose(fprented);
          fclose(fprenteda);


          //This block is calculating customer's change and updating customer's data.
          walletb -= (prices*week);
          char walletbook[5];
          sprintf(walletbook, "%d", walletb);
          strncat(wall, walletbook, 100);
          strncat(wall, "\n", 100);

          FILE* walletb = fopen("customers.txt", "r");
          FILE* fTempwall = fopen("temp.txt", "w");
          int countwall = 0;
          while ((fgets(bufferwall, 256, walletb)) != NULL){
            countwall++;
            if (countwall == C_ID)
              fputs(wall, fTempwall);
            else
          fputs(bufferwall, fTempwall);
          }
          fclose(walletb);
          fclose(fTempwall);
          remove("customers.txt");
          rename("temp.txt", "customers.txt");


          //This block is changing rented info from "no" to "yes" in books.txt file.
          strncat(bookarr, "yes\n", 100);
          FILE* re = fopen("books.txt", "r");
          FILE* fTempre = fopen("temp.txt", "w");

          int count = 0;
          while ((fgets(buffer, 256, re)) != NULL){
            count++;
            if (count == B_ID)
              fputs(bookarr, fTempre);
            else
              fputs(buffer, fTempre);
          }
          fclose(re);
          fclose(fTempre);
          remove("books.txt");
          rename("temp.txt", "books.txt");
            

          printf("\nYou have rented book successfully\n");
          printf("---------------------------------\n");
        }
        else{
          printf("\nSorry, You don't satistfy age limit of this book.\n");
        }
      }
      else{
        printf("\nSorry, You don't have enough money.\n");
      }
    }
    else{
      printf("\nSorry, This Book is Already Rented.\n");
    }
  }
}
  fclose(fpc);
  fclose(fpc2);
  fclose(fpb);
  fclose(fpb2);
  fclose(fpb3);
  fclose(fpb4);
}


//---------------------- This method is Delivering Book ----------------------.
void deliveryBook(){
  FILE *fpc = fopen("customers.txt", "r");
  FILE *fpb = fopen("books.txt", "r");
  FILE *fpr = fopen("rented.txt", "r");
  
  int R_ID;
  int week;
  int date;
  int cust;
  int bookId;
  int bookPrice;
  int wallet;
  int i = 0;
  int j = 0;
  int k = 0;
  int l = 0;
  int m = 0;
  int n = 0;
  char buffer[100];
  char line[256];
  char lineC[256];
  char lineB[256];
  char lineP[256];
  char lineW[256];
  char lineBA[256];
  char *ptr[6];
  char *bk[6];
  char arr[] = "";
  char books[] = "";



  printf("\n------------- Delivering Book --------------\n");
  printf("Please write rented ID: ");
  scanf("%d", &R_ID);

  printf("How many week did you rent earlier(If it's on time write 0)? ");
  scanf("%d", &date);


  //This block is finding for how many week did customer rent.
  while (fgets(line, sizeof(line), fpr)) {
    i++;
    if(i == R_ID){
      char *token = strtok(line, "-");
      for(int i = 0; i < 4; i++){
        token = strtok(NULL, "-");
      }
      week = atoi(token);
    }
  }

  fseek(fpr, 0, SEEK_SET);
  //This block is finding customer id from rented.txt.
  while (fgets(lineC, sizeof(lineC), fpr)) {
    j++;
    if(j == R_ID){
      char *tokenC = strtok(lineC, "-");
      tokenC = strtok(NULL, "-");
      cust = atoi(tokenC);
    }
  }

  fseek(fpr, 0, SEEK_SET);
  //This block is finding book id from rented.txt.
  while (fgets(lineB, sizeof(lineB), fpr)) {
    k++;
    if(k == R_ID){
      char *tokenB = strtok(lineB, "-");
      for(int i = 0; i < 2; i++){
        tokenB = strtok(NULL, "-");
      }
      bookId = atoi(tokenB);
    }
  }

  //This block is finding book's price per week.
  while (fgets(lineP, sizeof(lineP), fpb)) {
    l++;
    if(l == bookId){
      char *tokenP = strtok(lineP, "-");
      for(int i = 0; i < 4; i++){
        tokenP = strtok(NULL, "-");
      }
      bookPrice = atoi(tokenP);
    }
  }




  //This block is finding customer's money and refund if he/she bring book earlier.
  while (fgets(lineW, sizeof(lineW), fpc)) {
    m++;
    if(m == cust){
      char *tokenW = strtok(lineW, "-");
      for(int i = 0; i < 4; i++){
        ptr[i] = tokenW;
        tokenW = strtok(NULL, "-");
        strncat(arr, ptr[i], 100);
        strncat(arr, "-", 100);
      }
      //I got money but it is string. I am chaning it to int and I deposit money.
      wallet = atoi(tokenW);
      wallet += (bookPrice * date);
    }
  }
  //Before I add wallet data to my string (C_ID-name-surname-age-money), I need to convert it to string. I cannot add it as int.
  char wallets[100];
  sprintf(wallets, "%d", wallet);
  strncat(arr, wallets, 100);
  strncat(arr, "\n", 100);

  //For update customers.txt file, I need to create a temporary file, add all my data in it then change its name.
  FILE* a = fopen("customers.txt", "r");
  FILE* fTemp = fopen("temp.txt", "w");

  //I am adding all my customers.txt data and updated customer money to temp.txt.
  int count = 0;
  while ((fgets(buffer, 256, a)) != NULL){
    count++;
    if (count == cust)
      fputs(arr, fTemp);
    else
      fputs(buffer, fTemp);
  }

  //After all of that, I am closing FILE's and changing temp.txt's name as customers.txt.
  fclose(a);
  fclose(fTemp);
  remove("customers.txt");
  rename("temp.txt", "customers.txt");

  //This block is founding rented info and change it to "no".
  fseek(fpb, 0, SEEK_SET);
  while (fgets(lineBA, sizeof(lineBA), fpb)) {
    n++;
    if(n == bookId){
      char *tokenBA = strtok(lineBA, "-");
      for(int i = 0; i < 5; i++){
        bk[i] = tokenBA;
        tokenBA = strtok(NULL, "-");
        strncat(books, bk[i], 100);
        strncat(books, "-", 100);
      }
    }
  }
  strncat(books, "no\n", 100);

  FILE* re = fopen("books.txt", "r");
  FILE* fTempre = fopen("temp.txt", "w");

  int countbook = 0;
  while ((fgets(buffer, 256, re)) != NULL){
    countbook++;
    if (countbook == bookId)
      fputs(books, fTempre);
    else
      fputs(buffer, fTempre);
    }
    fclose(re);
    fclose(fTempre);
    remove("books.txt");
    rename("temp.txt", "books.txt");  
    printf("\nYou have delivered book successfully\n");
}


//---------------------- This method is Burning Book ----------------------.
void burnBook(){
  //I have not finished.
  printf("Sorry but this part is not finished.\n");
}


//---------------------- This method is Updating Customer ----------------------.
void updateCustomer(){
  //I have not finished.
  printf("Sorry but this part is not finished.\n");
}


//---------------------- This method is Updating Book ----------------------.
void updateBook(){
  //I have not finished.
  printf("Sorry but this part is not finished.\n");
}


//---------------- This method is Listing Customer Who Rented Book ----------------.
void listCustomerWhoRentBook(){
  //I have not finished.
  printf("Sorry but this part is not finished.\n");
}

//---------------------- This method is Listing Customer ----------------------.
void listCustomer() {
  FILE *fpr;
  fpr = fopen("customers.txt", "r");

  if ((fpr = fopen ("customers.txt", "r")) == NULL) {
         printf("No file found named '%s'!", "customers.txt");
         exit(1);
  }

  char line[256];
  char *ptr[5]; 

  printf("\n-------------------  List of Customers  ------------------\n");
  
  printf("ID          Name        Surname     Age         Money");
  
  printf("\n----------------------------------------------------------\n");

  //Finding how many customers do I have in text file.
  int number_of_lines = 0;
  while(!feof(fpr)){
    chr = fgetc(fpr);
    if(chr == '\n'){
      number_of_lines++;
    }
  }

  //Adding every data into an array then printing it.
  fseek(fpr, 0, SEEK_SET);
  for(int i = 0; i < number_of_lines; i++) {
    fgets(line, 256, fpr);
    int i = 0;
    char *token = strtok(line, "\n-");
    do{
      ptr[i++] = token;
      token = strtok(NULL, "\n-");
    } while( token != NULL ) ;
    
    
    for (int i = 0; i < 5; i++) printf("%-10s \t", ptr[i] );
    printf("\n");
  } 
  printf("----------------------------------------------------------\n");
}


//---------------------- This method is Listing Book ----------------------.
void listBook(){
  FILE *fpr;
  fpr = fopen("books.txt", "r");

  if ((fpr = fopen ("books.txt", "r")) == NULL) {
         printf("No file found named '%s'!", "books.txt");
         exit(1);
    }

  char line[256];

  char *ptr[6]; 

  printf("\n-------------------------  List of Books  ------------------------\n");
  
  printf("ID          Name        Author     Age Limit    Price       Rented");
  
  printf("\n------------------------------------------------------------------\n");

  //Finding how many books do I have in text file.
  int number_of_lines = 0;
  while(!feof(fpr)){
    chr = fgetc(fpr);
    if(chr == '\n'){
      number_of_lines++;
    }
  }
  //Adding every data into an array then printing it.
  fseek(fpr, 0, SEEK_SET);
  for(int i = 0; i < number_of_lines; i++) {
    fgets(line, 256, fpr);
    int i = 0;
    char *token = strtok(line, "\n-");
    do{
      ptr[i++] = token;
      token = strtok(NULL, "\n-");
    } while( token != NULL ) ;
    
    
    for (int i = 0; i < 6; i++) printf("%-10s \t", ptr[i] );
    printf("\n");
  } 
  printf("------------------------------------------------------------------\n");
}