#include <stdio.h>
#include <string.h>
void addItems();
void readItemdata();
void searchItem();
void appendItems();
void numberOfItem();
void updateItem();
void deleteItem();
void Buy();
void calculaterBill();
void updatequntity(int number, int quntity );
void billCreater(int number,int qun);
void displaybilldata();
int itemsIdChecker(int id);
int checkItemQuantity(int id, int qun);

struct items{
    char itemName[20];
    int quantity;
    int itemsPrice;
    int itemNumber;
};

struct buy{
    char itemName[20];
    int itemNumber;
    int itemsPrice;
    int quantity;
    int itembill;
};

struct tempbuy{
    int quantity;
    int itemNumber;
};

int totalBill=0;

int main() {

    int n;
    printf("\n");
    printf("0. add items \n");
    printf("3. append items \n");
    printf("1. disply full items \n");
    printf("2. search items\n");
    printf("4. number of items \n");
    printf("5. delete items \n");
    printf("6. update items \n");
    printf("7. buy items \n");
    printf("8. display bill \n");
    scanf("%d",&n);
    if(n==0){
        addItems();
    } else if (n==1){
        readItemdata();
    } else if(n==2){
        searchItem();
    }else if(n==3){
        appendItems();
    }else if(n==4){
        numberOfItem();
    }else if(n==6){
        updateItem();
    }else if(n==5){
        deleteItem();
    }else if(n==7){
        Buy();
    }else if(n==8){
        displaybilldata();
    }
    return 0;
}

void addItems(){
    FILE *file;
    int number = 0;
    struct items structitems,s;
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

void appendItems(){
    FILE *file;
    int number = 0;
    struct items structitems,s;
    file= fopen("itemdata.dat","a");

    if(file==NULL){
        printf("open fail\n");
    } else{
        printf("--------------------------------------------------------------------\n");
        printf("\nHow much item you add:");
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
                printf("\n---Items number Already used please add other number and try again--\n\n");
                goto LOOP;
            }
        }

    }

    fclose(file);
    main();
}

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

void readItemdata(){
    FILE *file;
    struct items s;
    file= fopen("itemdata.dat","r");
    if(file==NULL){
        printf("open fail\n");
    } else{
        printf("--------------------------------------------------------------------\n");
        printf("ItemNumber\t\tName\t\tPrice\t\tquantity\n");
        printf("--------------------------------------------------------------------");
        while (fread(&s,sizeof (s),1,file)){
            printf("\n%d\t\t\t%s\t\t%d\t\t%d",s.itemNumber,s.itemName,s.itemsPrice,s.quantity);
        }
        printf("\n--------------------------------------------------------------------\n");
    }
    fclose(file);
    main();
}

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
            printf("\n--- Not found items ! ---");
        }
    }
    fclose(file);
    main();
}

void numberOfItem(){
    FILE *file;
    struct items s;
    file= fopen("itemdata.dat","r");
    if(file==NULL){
        printf("open fail\n");
    } else{
        fseek(file,0,SEEK_END);
        int n = ftell(file)/ sizeof(s);
        printf("Record is %d\n",n);
    }
    fclose(file);
    main();
}

void updateItem(){
    FILE *file,*file1;
    struct items s;
    int iNumber,found=0;
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
                printf("Enter item name:");
                scanf(" %s",&s.itemName);
                printf("Enter item price:");
                scanf(" %d",&s.itemsPrice);
                printf("Enter item quantity:");
                scanf(" %d",&s.quantity);
            }
            fwrite( &s,sizeof(s),1,file1 );
        }
        fclose(file);
        fclose(file1);
        if(found==0){
            printf("\nNot found items");
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
            printf("\n--- Not found item !---\n");
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
    file= fopen("tempbuy.dat","r");
    printf("\n--------------------------------------------------------------------\n");
    printf("ItemNumber\t\tName\t\tPrice\t\tquantity\t\tfullprice");
    while (fread(&tb,sizeof (tb),1,file)){
        billCreater(tb.itemNumber,tb.quantity);
    }
    printf("\n--------------------------------------------------------------------\n");
    printf("\nyour total Bill is Rs. %d\n",totalBill);
    fclose(file);
}

void billCreater(int number,int qun){
    FILE *file,*file1;
    struct items s;
    struct buy by;
    int found=0,bill;
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
                printf("\n%s\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d",s.itemName,s.itemNumber,s.itemsPrice,qun,bill);
                updatequntity(s.itemNumber, qun);
                strncpy(by.itemName, s.itemName, 20);
                by.itemNumber = s.itemNumber;
                by.quantity = qun;
                by.itemsPrice = s.itemsPrice;
                by.itembill=bill;
                fwrite( &by,sizeof(by),1,file1);
            }
        }
        if(found==0){
            printf("\nNot found items");
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
            printf("\nNot found items and not Update");
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
    file= fopen("billdata.dat","r");
    if(file==NULL){
        printf("open fail\n");
    } else{
        printf("ItemNumber\t\tName\t\tPrice\t\tquantity\t\tbill");
        while (fread(&s,sizeof (s),1,file)){
            printf("\n%d\t\t\t%s\t\t\t%d\t\t\t%d\t\t\t%d",s.itemNumber,s.itemName,s.itemsPrice,s.quantity,s.itembill);
        }
    }
    fclose(file);
    main();
}


