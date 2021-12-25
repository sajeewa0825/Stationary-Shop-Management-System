#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

//declare functions
void addItems();
void readItemdata();
void searchItem();
void appendItems();
void updateItem();
void deleteItem();
void Buy();
void calculaterBill();
void updatequntity(int number, int quntity );
void billCreater(int number,int qun);
void displaybilldata();
int itemsIdChecker(int id);
int checkItemQuantity(int id, int qun);

//items data store struct
struct items{
    char itemName[20];
    int quantity;
    int itemsPrice;
    int itemNumber;
};

//buy items data store struct
struct buy{
    char itemName[20];
    int itemNumber;
    int itemsPrice;
    int quantity;
    int itembill;
    int date;
    int month;
    int year;
};

//temporarily buy id and quantity store struct
struct tempbuy{
    int quantity;
    int itemNumber;
};

// total bill price store, Global variables
int totalBill=0;


/**
 * main menu and selections functions
 * */
int main() {
    int n,n1;
    printf("\n\n");
    printf("                             === WELCOME TO THE ABC ===                                       \n");
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("1. Buy \n");
    printf("2. Admin Panel\n");
    printf("0. Exit Program\n");
    printf("----------------------------------------------------------------------------------------------------\n\n");
    printf("Enter your choice :");
    scanf("%d",&n);
    if(n==1){
        Buy();
    } else if ( n == 2){
        printf("1. Add Items\n");
        printf("2. Items List\n");
        printf("3. Search Items\n");
        printf("4. Delete Items\n");
        printf("5. Update Items\n");
        printf("6. Delete All Items And Create New List\n");
        printf("7. Sold List\n");
        printf("0. Return main menu\n");
        printf("\nEnter your choice :");
        scanf("%d",&n1);
        switch (n1) {
            case 1:
                appendItems();
                break;
            case 2:
                readItemdata();
                break;
            case 3:
                searchItem();
                break;
            case 4:
                deleteItem();
                break;
            case 5:
                updateItem();
                break;
            case 6:
                addItems();
                break;
            case 7:
                displaybilldata();
                break;
            case 0:
                main();
            default:
                main();
        }
        } else if(n==0){
            EXIT_FAILURE;
        } else{
        main();
    }


    return 0;
}


/**
 * delete all items data and add new items
 * */
void addItems(){
    FILE *file;
    int number = 0;
    struct items structitems;
    file= fopen("itemdata.dat","w");

    if(file==NULL){
        printf("open fail\n");
    } else{
        printf("How much item you add:");
        scanf("%d",&number);
        for (int i=0;i<number;++i){
            printf("Enter item number:");
            scanf(" %d",&structitems.itemNumber);
            printf("Enter item name:");
            scanf(" %s",&structitems.itemName);
            printf("Enter item price:");
            scanf(" %d",&structitems.itemsPrice);
            printf("Enter item quantity:");
            scanf(" %d",&structitems.quantity);
            fwrite( &structitems,sizeof(structitems),1,file );
        }

    }

    fclose(file);
    main();
}

/**
 * add items for database
 * append mode
 * */
void appendItems(){
    FILE *file;
    int number = 0;
    struct items structitems;
    file= fopen("itemdata.dat","a");

    if(file==NULL){
        printf("open fail\n");
    } else{
        printf("--------------------------------------------------------------------\n");
        printf("\nHow many items need to be added:");
        scanf("%d",&number);
        for (int i=0;i<number;++i){
            LOOP: printf("Enter item number:");
            scanf(" %d",&structitems.itemNumber);
            int check =itemsIdChecker(structitems.itemNumber);
            if(check == 0){
                printf("Enter item name:");
                scanf(" %s",&structitems.itemName);
                printf("Enter item price:");
                scanf(" %d",&structitems.itemsPrice);
                printf("Enter item quantity:");
                scanf(" %d",&structitems.quantity);
                fwrite( &structitems,sizeof(structitems),1,file );
                printf("\n-----Data Add successfully-----\n");
            } else{
                printf("\n---Item number is Already used please add another number and try again--\n\n");
                goto LOOP;
            }
        }

    }

    fclose(file);
    main();
}

/**
 * check the items number already store or not
 * if items found return 1
 * if items not found return 0
 * used itemdata.dat file
 * */
int itemsIdChecker(int id){
    FILE *file;
    struct items s;
    int found=0;
    file= fopen("itemdata.dat","r");
    if(file==NULL){
        printf("open fail\n");
    } else{
        while (fread(&s,sizeof (s),1,file)){
            if(s.itemNumber == id){
                found = 1;
            }
        }
    }
    fclose(file);
    return found;
}


/**
 * display items table
 * */
void readItemdata(){
    FILE *file;
    struct items s;
    int items=0,qunticount=0,pri=0;
    file= fopen("itemdata.dat","r");
    if(file==NULL){
        printf("open fail\n");
    } else{
        printf("----------------------------------------------------------------------------------------------------\n");
        printf("ItemNumber\t\tName\t\t\tPrice\t\t\tquantity\n");
        printf("----------------------------------------------------------------------------------------------------");
        while (fread(&s,sizeof (s),1,file)){
            printf("\n%d\t\t\t%s\t\t\t%d\t\t\t%d",s.itemNumber,s.itemName,s.itemsPrice,s.quantity);
            items=items+1;
            qunticount=qunticount+s.quantity;
            pri=pri+(s.itemsPrice*s.quantity);

        }
        printf("\n----------------------------------------------------------------------------------------------------\n");
        printf("Total items %d\n",items);
        printf("Total inventory %d\n",qunticount);
        printf("Total value of goods Rs. %d",pri);
        printf("\n----------------------------------------------------------------------------------------------------\n");
    }
    fclose(file);
    main();
}


/**
 * check the items number already store or not
 * search items using item number
 * used itemdata.dat file
 * */
void searchItem(){
    FILE *file;
    struct items s;
    int iNumber,found=0;
    file= fopen("itemdata.dat","r");
    if(file==NULL){
        printf("open fail\n");
    } else{
        printf("Enter item number:");
        scanf("%d",&iNumber);
        printf("\n--------------------------------------------------------------------\n");
        printf("ItemNumber\t\tName\t\tPrice\t\tquantity\n");
        printf("--------------------------------------------------------------------");
        while (fread(&s,sizeof (s),1,file)){
            if(s.itemNumber == iNumber){
                found=1;
                printf("\n%d\t\t\t%s\t\t%d\t\t%d",s.itemNumber,s.itemName,s.itemsPrice,s.quantity);
            }
        }
        printf("\n--------------------------------------------------------------------\n");
        if(found==0){
            printf("\n--- Item not found ! ---");
        }
    }
    fclose(file);
    main();
}

/**
 * update item table without change item number
 * used itemdata.dat file
 * used temp.dat file
 * */
void updateItem(){
    FILE *file,*file1;
    struct items s;
    int iNumber,found=0,n;
    file= fopen("itemdata.dat","r");
    file1= fopen("temp.dat","w");
    if(file==NULL){
        printf("open fail\n");
    } else{
        printf("Enter Update item number:");
        scanf("%d",&iNumber);
        while (fread(&s,sizeof (s),1,file)){
            if(s.itemNumber == iNumber){
                found=1;
                Loop: printf("1. Update Item name\n"
                             "2. Update Item price\n"
                             "3. Update Item quantity\n");
                scanf("%d",&n);
                if(1==n){
                    printf("Enter item name:");
                    scanf(" %s",&s.itemName);
                } else if (2 == n){
                    printf("Enter item price:");
                    scanf(" %d",&s.itemsPrice);
                } else if ( 3== n){
                    printf("Enter item quantity:");
                    scanf(" %d",&s.quantity);
                } else{
                    printf(" wrong input \n");
                    goto Loop;
                }
            }
            fwrite( &s,sizeof(s),1,file1 );
        }
        fclose(file);
        fclose(file1);
        if(found==0){
            printf("\nItem not found");
        } else{
            file1= fopen("temp.dat","r");
            file= fopen("itemdata.dat","w");

            while (fread(&s,sizeof (s),1,file1)){
                fwrite( &s,sizeof(s),1,file );
            }

            fclose(file);
            fclose(file1);
        }
    }
    main();
}

/**
 * delete item table row using item id
 * used itemdata.dat file
 * used temp.dat file
 * */
void deleteItem(){
    FILE *file,*file1;
    struct items s;
    int iNumber,found=0;
    file= fopen("itemdata.dat","r");
    file1= fopen("temp.dat","w");
    if(file==NULL){
        printf("open fail\n");
    } else{
        printf("\n--------------------------------------------------------------------\n");
        printf("Enter delete item number:");
        scanf("%d",&iNumber);
        while (fread(&s,sizeof (s),1,file)){
            if(s.itemNumber == iNumber){
                found=1;
            } else{
                fwrite( &s,sizeof(s),1,file1 );
            }
        }
        fclose(file);
        fclose(file1);
        if(found==0){
            printf("\n--- Item not found !---\n");
        } else{
            file1= fopen("temp.dat","r");
            file= fopen("itemdata.dat","w");

            while (fread(&s,sizeof (s),1,file1)){
                fwrite( &s,sizeof(s),1,file );
            }
            printf("\n---Item Delete successful---\n");
            fclose(file);
            fclose(file1);
        }
    }
    main();
}

void Buy(){
    FILE *file,*file1;
    int check=1;
    struct items s;
    struct tempbuy tb;
    file= fopen("itemdata.dat","r");
    file1= fopen("tempbuy.dat","w");
    if(file==NULL &&  file1 == NULL){
        printf("open fail\n");
    } else{
        printf("\n--------------------------------------------------------------------\n");
        printf("ItemNumber\t\tName\t\tPrice\t\tquantity\n");
        printf("--------------------------------------------------------------------");
        while (fread(&s,sizeof (s),1,file)){
            printf("\n%d\t\t\t%s\t\t%d\t\t%d",s.itemNumber,s.itemName,s.itemsPrice,s.quantity);
        }
        fclose(file);
        printf("\n--------------------------------------------------------------------\n");
        do {
            Loop:  printf("Enter item number \n");
            scanf("%d",&tb.itemNumber);
            int check1 =itemsIdChecker(tb.itemNumber);
            if (check1 == 1){
                Loop1: printf("Enter item quantity \n");
                scanf("%d",&tb.quantity);
                int check2 = checkItemQuantity(tb.itemNumber,tb.quantity);
                if(check2 == 1){
                    fwrite( &tb,sizeof(tb),1,file1);
                } else if(check2 == 2){
                    printf("--- This item out of stock---\n\n");
                    goto Loop;
                } else{
                    printf("--- Your Request quantity Not available ! Try again---\n\n");
                    goto Loop1;
                }
                Loop3:  printf("\nClose enter 0\n" "continue enter 1\n");
                scanf("%d",&check);
                if(check != 0 && check !=1 ){
                    goto Loop3;
                }
            } else{
                printf("\n--- Wrong item number try again ---\n\n");
                goto Loop;
            }
        } while (check==1);
        fclose(file1);

    }
    calculaterBill();
    main();
}

int checkItemQuantity(int id, int qun){
    FILE *file;
    struct items s;
    int check=0;
    file= fopen("itemdata.dat","r");
    if(file==NULL){
        printf("open fail\n");
    } else{
        while (fread(&s,sizeof (s),1,file)){
            if(s.itemNumber == id){
                if(s.quantity == 0){
                    check = 2;
                } else{
                    if(s.quantity >= qun ){
                        check= 1;
                    }
                }
            }
        }
    }
    fclose(file);
    return check;
}

void calculaterBill(){
    FILE *file;
    struct tempbuy tb;
    time_t tm;
    time(&tm);
    file= fopen("tempbuy.dat","r");
    printf("                             === Name of the shop ===                                         \n");
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("%s", ctime(&tm));
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("ItemNumber\t\tName\t\tPrice\t\tQuantity\t\tAmount");
    while (fread(&tb,sizeof (tb),1,file)){
        billCreater(tb.itemNumber,tb.quantity);
    }
    printf("\n----------------------------------------------------------------------------------------------------\n");
    printf("TOTAL Rs. %d\n",totalBill);
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("                             ===== Thank you come Again =====\n");
    fclose(file);
}

void billCreater(int number,int qun){
    FILE *file,*file1;
    struct items s;
    struct buy by;
    int found=0,bill;
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    file= fopen("itemdata.dat","r");
    file1= fopen("billdata.dat","a");
    if(file==NULL){
        printf("open fail\n");
    } else{
        while (fread(&s,sizeof (s),1,file)){
            if(s.itemNumber == number){
                bill=qun*s.itemsPrice;
                totalBill=totalBill+bill;
                found=1;
                printf("\n%d\t\t\t%s\t\t%d\t\t%d\t\t\t%d",s.itemNumber,s.itemName,s.itemsPrice,qun,bill);
                updatequntity(s.itemNumber, qun);
                strncpy(by.itemName, s.itemName, 20);
                by.itemNumber = s.itemNumber;
                by.quantity = qun;
                by.itemsPrice = s.itemsPrice;
                by.itembill=bill;
                by.date=tm.tm_mday;
                by.month=tm.tm_mon+1;
                by.year=tm.tm_year+1900;
                fwrite( &by,sizeof(by),1,file1);
            }
        }
        if(found==0){
            printf("\nItem not found");
        }
    }
    fclose(file);
    fclose(file1);
}

void updatequntity(int number, int quntity ){
    FILE *file,*file1;
    struct items s;
    int found=0;
    file= fopen("itemdata.dat","r");
    file1= fopen("temp.dat","w");
    if(file==NULL){
        printf("open fail\n");
    } else{
        while (fread(&s,sizeof (s),1,file)){
            if(s.itemNumber == number){
                found=1;
                s.quantity=s.quantity-quntity;
            }
            fwrite( &s,sizeof(s),1,file1 );
        }
        fclose(file);
        fclose(file1);
        if(found==0){
            printf("\nitem not found and not Update");
        } else{
            file1= fopen("temp.dat","r");
            file= fopen("itemdata.dat","w");

            while (fread(&s,sizeof (s),1,file1)){
                fwrite( &s,sizeof(s),1,file );
            }

            fclose(file);
            fclose(file1);
        }
    }
}

void displaybilldata(){
    FILE *file;
    struct buy s;
    int TotalSelling=0,daySelling=0;

    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);

    file= fopen("billdata.dat","r");
    if(file==NULL){
        printf("open fail\n");
    } else{
        printf("\n--- Total Selling Table --");
        printf("\n-------------------------------------------------------------------------------------------------------\n");
        printf("ItemNumber\t\tName\t\tPrice\t\tQuantity\tAmount\t\tDate");
        printf("\n-------------------------------------------------------------------------------------------------------");
        while (fread(&s,sizeof (s),1,file)){
            printf("\n%d\t\t\t%s\t\t%d\t\t%d\t\t%d\t\t%d-%d-%d",s.itemNumber,s.itemName,s.itemsPrice,s.quantity,s.itembill,s.date,s.month,s.year);
            TotalSelling=TotalSelling+s.itembill;
            if(s.date == tm.tm_mday && s.month == tm.tm_mon+1 && s.year == tm.tm_year+1900){
                daySelling=daySelling + s.itembill;
            }

        }
        printf("\n-------------------------------------------------------------------------------------------------------\n");
        printf("Total Selling Rs. %d",TotalSelling);
        printf("\n-------------------------------------------------------------------------------------------------------\n");
        printf("Today's Selling Rs. %d",daySelling);
        printf("\n-------------------------------------------------------------------------------------------------------\n");
    }

    fclose(file);
    main();
}


