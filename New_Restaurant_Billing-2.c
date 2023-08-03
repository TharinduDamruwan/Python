#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_DELETED_INVOICES 100

struct items{
    char item[20];
    float price;
    int qty;
};

struct orders{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};

const char* correct_username = "admin";
const char* correct_password = "admin6@@!";

//functions to generate biils
void generateBillHeader(char name[50],char date[30]){
    printf("\n\n");
    printf("\t\t            GLR Restaurant\n");
    printf("\t\t=======================================");
    printf("\n\t\tDate:%s",date);
    printf("\n\t\tInvoice To: %s",name);
    printf("\n");
    printf("\t\t---------------------------------------\n");
    printf("\t\tItems\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n\t\t---------------------------------------");
    printf("\n\n");
}
void generateBillBody(char item[30],int qty, float price){
    printf("\t\t%s\t\t",item);
    printf("%d\t\t",qty);
    printf("%.2f\t\t",qty * price);
    printf("\n");
}

void generateBillFooter(float total){
    printf("\n");
    float dis = 0.1*total;
    float netTotal=total-dis;
    float cgst=0.09*netTotal,grandTotal=netTotal + 2*cgst;//netTotal + cgst + sgst
    printf("\t\t---------------------------------------\n");
    printf("\t\tSub Total\t\t\t%.2f",total);
    printf("\n\t\tDiscount @10%s\t\t\t%.2f","%",dis);
    printf("\n\t\t\t\t\t\t-------");
    printf("\n\t\tNet Total\t\t\t%.2f",netTotal);
    printf("\n\t\tCGST @9%s\t\t\t%.2f","%",cgst);
    printf("\n\t\tSGST @9%s\t\t\t%.2f","%",cgst);
    printf("\n\t\t---------------------------------------");
    printf("\n\t\tGrand Total\t\t\t%.2f",grandTotal);
    printf("\n\t\t---------------------------------------\n");
    printf("\n\t\t          ****************\n");
}

int displayNumberOfInvoices() {
    FILE* fp = fopen("RestaurantBill.dat", "r");
    if (fp == NULL) {
        printf("Error opening the file.\n");
        return 0;
    }

    struct orders order;
    int numInvoices = 0;

    while (fread(&order, sizeof(struct orders), 1, fp)) {
        numInvoices++;
    }

    fclose(fp);
    return numInvoices;
}

struct orders deletedInvoices[MAX_DELETED_INVOICES];
int numDeletedInvoices = 0;

// Function to delete an invoice based on the customer name
void deleteInvoice(const char* name) {
    FILE* fp = fopen("RestaurantBill.dat", "r");
    if (fp == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    FILE* tmp_fp = fopen("tmpRestaurantBill.dat", "w");
    if (tmp_fp == NULL) {
        printf("Error creating the temporary file.\n");
        fclose(fp);
        return;
    }

    struct orders order;
    int invoiceFound = 0;

    while (fread(&order, sizeof(struct orders), 1, fp)) {
        if (strcmp(order.customer, name) == 0) {
            invoiceFound = 1;

            // Add the deleted invoice to the array
            if (numDeletedInvoices < MAX_DELETED_INVOICES) {
                deletedInvoices[numDeletedInvoices] = order;
                numDeletedInvoices++;
            }

            continue; // Skip this invoice, don't write it to the temporary file
        }

        // Write other invoices to the temporary file
        fwrite(&order, sizeof(struct orders), 1, tmp_fp);
    }

    fclose(fp);
    fclose(tmp_fp);

    // Remove the original file and rename the temporary file
    remove("RestaurantBill.dat");
    rename("tmpRestaurantBill.dat", "RestaurantBill.dat");

    if (invoiceFound) {
        printf("Invoice for %s has been deleted successfully.\n", name);
    } else {
        printf("Invoice for %s does not exist.\n", name);
    }
}

void showDeletedInvoices() {
    if (numDeletedInvoices == 0) {
        printf("No invoices have been deleted yet.\n");
        return;
    }

    printf("\nDeleted Invoices:\n");
    for (int i = 0; i < numDeletedInvoices; i++) {
        printf("Invoice for %s (Date: %s)\n", deletedInvoices[i].customer, deletedInvoices[i].date);
        for (int j = 0; j < deletedInvoices[i].numOfItems; j++) {
            printf("%d. %s - Qty: %d, Price: %.2f\n", j + 1, deletedInvoices[i].itm[j].item,
                   deletedInvoices[i].itm[j].qty, deletedInvoices[i].itm[j].price);
        }
        printf("----------------------------------\n");
    }
}

int main(){

    int opt,n;
    struct orders ord;
    struct orders order;
    char saveBill = 'y',contFlag = 'y';
    char name[50];
    FILE *fp;
    //dashboard

     char username[50];
    char password[50];

    printf("\n\t\t===========================================");
    printf("\n\t\t              GLR RESTAURANT");
    printf("\n\t\t===========================================");

    do {
        printf("\n\n\t\tPlease log in to continue\n");
        printf("\t\tUsername: ");
        fgets(username, 50, stdin);
        username[strcspn(username, "\n")] = '\0'; // Remove the newline character

        printf("\t\tPassword: ");
        fgets(password, 50, stdin);
        password[strcspn(password, "\n")] = '\0'; // Remove the newline character

        if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
            printf("\n\t\tLogin successful!\n");
            break; // Exit the login loop
        } else {
            printf("\n\t\tIncorrect username or password. Please try again.\n");
        }
    } while (1);

    while(contFlag == 'y')
    {
        //system("clear");
        float total = 0;
        int invoiceFound = 0;
        printf("\n\t\t===========================================");
        printf("\n\t\t              GLR RESTAURANT");
        printf("\n\t\t===========================================");
        printf("\n\n\t\tPlease select your prefered operation");
        printf("\n\n\t\t1.Generate Invoice");
        printf("\n\t\t2.Show all Invoices");
        printf("\n\t\t3.No. of Invoices");
        printf("\n\t\t4.Search Invoice");
        printf("\n\t\t5.Delete Invoice");
        printf("\n\t\t6.Show Deleted Invoices");
        printf("\n\t\t7.Exit");

        printf("\n\nYour choice:\t");
        scanf("%d",&opt);
        fgetc(stdin);
        switch(opt)
        {
        case 1:
            //system("clear");
            printf("\nPlease enter the name of the customer:\t");
            fgets(ord.customer,50,stdin);
            ord.customer[strlen(ord.customer)-1] = 0;
            strcpy(ord.date,__DATE__);
            printf("\nPlease enter the number of items:\t");
            scanf("%d",&n);
            ord.numOfItems = n;
            for(int i=0; i<n; i++)
            {
                fgetc(stdin);
                printf("\n\n");
                printf("Please enter the item %d:\t",i+1);
                fgets(ord.itm[i].item,20,stdin);
                ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
                printf("Please enter the quantity:\t");
                scanf("%d",&ord.itm[i].qty);
                printf("Please enter the unit price:\t");
                scanf("%f",&ord.itm[i].price);
                total += ord.itm[i].qty * ord.itm[i].price;
            }

            generateBillHeader(ord.customer,ord.date);
            for(int i=0; i<ord.numOfItems; i++)
            {
                generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
            }
            generateBillFooter(total);

            printf("\nDo you want to save the invoice [y/n]:\t");
            scanf("%s",&saveBill);

            if(saveBill == 'y')
            {
                fp = fopen("RestaurantBill.dat","a+");
                fwrite(&ord,sizeof(struct orders),1,fp);
                if(fp != 0)
                    printf("\nSuccessfully saved");
                else
                    printf("\nError saving");
                fclose(fp);
            }
            break;

        case 2:
            //system("clear");
            fp = fopen("RestaurantBill.dat","r");
            printf("\n\t\t  *****Your Previous Invoices*****\n");
            while(fread(&order,sizeof(struct orders),1,fp))
            {
                float tot = 0;
                generateBillHeader(order.customer,order.date);
                for(int i=0; i<order.numOfItems; i++)
                {
                    generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                    tot+=order.itm[i].qty * order.itm[i].price;
                }
                generateBillFooter(tot);
            }
            fclose(fp);
            break;

        case 3:
            printf("Total number of invoices saved: %d\n", displayNumberOfInvoices());
            break;

        case 4:
            printf("Enter the name of the customer:\t");
            //fgetc(stdin);
            fgets(name,50,stdin);
            name[strlen(name)-1] = 0;
//            system("clear");
            fp = fopen("RestaurantBill.dat","r");
            printf("\n\t\t*****Invoice of %s*****",name);
            while(fread(&order,sizeof(struct orders),1,fp))
            {
                float tot = 0;
                if(!strcmp(order.customer,name))
                {
                    generateBillHeader(order.customer,order.date);
                    for(int i=0; i<order.numOfItems; i++)
                    {
                        generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                        tot+=order.itm[i].qty * order.itm[i].price;
                    }
                    generateBillFooter(tot);
                    invoiceFound = 1;
                }

            }
            if(!invoiceFound)
            {
                printf("\nSorry the invoice for %s doesnot exists",name);
            }
            fclose(fp);
            break;

        case 5:
            printf("Enter the name of the customer to delete the invoice:\t");
            fgets(name, 50, stdin);
            name[strlen(name) - 1] = '\0';
            deleteInvoice(name);
            break;

        case 6:
            showDeletedInvoices();
        break;

        case 7:
            printf("\n\n\t\t Thank You!\n\n");
            exit(0);
            break;

        default:
            printf("Sorry invalid option");
            break;
        }
        printf("\nDo you want to perform another operation?[y/n]:\t");
        scanf("%s",&contFlag);
    }
    printf("\n\n\t\t Thank You!\n\n");
    printf("\n\n");

    return 0;
}
