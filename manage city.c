#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_CITIES 30
#define NAME_LENGTH 50

void addCity(char cities[MAX_CITIES][NAME_LENGTH], int *count);
void cityManagement(char cities[MAX_CITIES][NAME_LENGTH], int *count);
void renameCity(char cities[MAX_CITIES][NAME_LENGTH],int count);
void displayCities(char cities[MAX_CITIES][NAME_LENGTH],int count);
void removeCity(char cities[MAX_CITIES][NAME_LENGTH],int *count);
void inputOrEditDistance(int distance[MAX_CITIES][MAX_CITIES],char cities[MAX_CITIES][NAME_LENGTH],int count);
void manageDistance(char cities[MAX_CITIES][NAME_LENGTH], int distance[MAX_CITIES][MAX_CITIES], int count);
void displayDistanceTable(int distance[MAX_CITIES][MAX_CITIES],char cities[MAX_CITIES][NAME_LENGTH],int count);
void calculateCost(int D,float W,int R,int S,int E,float F);
void vehicalMangement();
void deliveryRequest(int distance[MAX_CITIES][MAX_CITIES], char cities[MAX_CITIES][NAME_LENGTH], int count);
int main()
{
    int count=0;


    char cities[MAX_CITIES][NAME_LENGTH];
    int distance[MAX_CITIES][MAX_CITIES]={0};
    int D,R,S,E;
    float W,F;
    int choice;

    do
    {
        printf("===Logistics & Delivery Management System===\n");
        printf("1.City Management\n");
        printf("2.Distance Management\n");
        printf("3.Vehicle Management(show vehicle info)\n");
        printf("4.Delivery Request and Cost,Time,Fuel Calculations\n");
        printf("5.Exit\n");
        printf("Enter Your Choice:");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            cityManagement(cities,&count);
            break;
        case 2:
            manageDistance(cities, distance, count);

            break;
        case 3:
           vehicalMangement();
            break;
        case 4:
           deliveryRequest(distance,cities,count);
            break;
        case 5:
            printf("Exiting the program...\n");
            break;
        default:
            printf("Invalid Input!\n");
            break;

        }
    }
    while(choice!=5);

    return 0;
}
void cityManagement(char cities[MAX_CITIES][NAME_LENGTH], int *count)
{

    int choice1;
    do
    {
        printf("===City Management System===\n");
        printf("1.Add a new city\n");
        printf("2.Rename a city\n");
        printf("3.Remove a city\n");
        printf("4.Display all cities\n");
        printf("5.Exit\n");
        printf("Enter your choice:");
        scanf("%d",&choice1);
        while (getchar() != '\n');
        switch(choice1)
        {
        case 1:
            addCity(cities,count);
            break;
        case 2:
            renameCity(cities,*count);
            break;
        case 3:
            removeCity(cities,count);
            break;
        case 4:
            displayCities(cities,*count);
            break;
        case 5:
            printf("Exiting the City Mangement System\n");
            break;
        default:
            printf("Invalid Input!\n");
            break;
        }
    }
    while(choice1!=5);
}
void addCity(char cities[MAX_CITIES][NAME_LENGTH],int *count)

{
    if (*count>=MAX_CITIES)
    {
        printf("Limit Reached Can't Add New Cities\n");
        return;
    }
    char newCity[NAME_LENGTH];
    printf("Enter new city name: ");
    fgets(newCity, sizeof(newCity), stdin);
    newCity[strcspn(newCity, "\n")] = '\0';


    for (int i=0; i< *count; i++)
    {
        if(strcmp(cities[i],newCity)==0)
        {
            printf("City already exists!\n");
            return;
        }
    }
    strcpy(cities[*count],newCity);
    (*count)++;
    printf("City added Successfully!\n");

}


void renameCity(char cities[MAX_CITIES][NAME_LENGTH], int count)
{
    if (count == 0)
    {
        printf("No cities to rename.\n");
        return;
    }


    char oldName[NAME_LENGTH], newName[NAME_LENGTH];
    printf("Enter the city name you want to rename: ");
    fgets(oldName,sizeof(oldName),stdin);
    oldName[strcspn(oldName,"\n")]='\0';

    int found = -1;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(cities[i], oldName) == 0)
        {
            found = i;
            break;
        }
    }

    if (found == -1)
    {
        printf("City not found!\n");
        return;
    }

    printf("Enter the new name: ");
    fgets(newName,sizeof(newName),stdin);
    newName[strcspn(newName,"\n")]='\0';


    for (int i = 0; i < count; i++)
    {
        if (strcmp(cities[i], newName) == 0)
        {
            printf("This city already exists!\n");
            return;
        }
    }


    strcpy(cities[found], newName);
    printf("City renamed successfully!\n");
}
void displayCities(char cities[MAX_CITIES][NAME_LENGTH],int count)
{
    if(count==0)
    {
        printf("No cities to display\n");
        return;
    }
    printf("---Display Cities---\n");
    for(int i=0; i<count; i++)
    {
        printf("%d.%s\n",i+1,cities[i]);
    }
}
void removeCity(char cities[MAX_CITIES][NAME_LENGTH],int *count)
{
    if(*count==0){
        printf("No cities to remove\n");
        return;
    }
    char cityRemove[NAME_LENGTH];
    printf("Enter the city name you want remove:");
    fgets(cityRemove,sizeof(cityRemove),stdin);
    cityRemove[strcspn(cityRemove,"\n")]='\0';

    int found=-1;
    for(int i=0;i<*count;i++)
    {
        if(strcmp(cities[i],cityRemove)==0)
        {
            found=i;
            break;
        }
    }
    if(found==-1){
        printf("City not found\n");
        return;
    }
    for(int i=found;i<*count-1;i++){
        strcpy(cities[i],cities[i+1]);
    }
    (*count)--;
    printf("City removed succesfully!\n");
}
void manageDistance(char cities[MAX_CITIES][NAME_LENGTH],int distance[MAX_CITIES][MAX_CITIES],int count)
{

    int choice2;


    do{
        printf("---Distance Management---\n");
        printf("1.Input or Edit Distance Between Cities\n");
        printf("2.Display Distance Table\n");
        printf("3.Exit\n");
        printf("Enter your choice:");
        scanf("%d",&choice2);
        while (getchar() != '\n');


        switch(choice2)
        {
        case 1:
           inputOrEditDistance(distance,cities,count);
            break;
        case 2:
           displayDistanceTable(distance,cities,count);
            break;
        case 3:
            printf("Exiting the distance Management System\n");
            break;
        default:
            printf("Invalid Input!\n");
        }

    }while(choice2!=3);
}
void inputOrEditDistance(int distance[MAX_CITIES][MAX_CITIES],char cities[MAX_CITIES][NAME_LENGTH],int count)
{
    if(count<2){
        printf("You need at least 2 cities to set distance!\n");
        return;
    }
    printf("Available Cities:\n");
    for(int i=0;i<count;i++)
        printf("%d,%s\n",i+1,cities[i]);
    int c1,c2;
    int d;
    printf("Enter first city number:");
    scanf("%d",&c1);

    printf("Enter second city number:");
    scanf("%d",&c2);



    if (c1<1||c1>count||c2<1||c2>count||c1==c2){
        printf("Invalid city selection!\n");
        return;
    }
    printf("Enter distance between %s and %s (in km):",cities[c1-1],cities[c2-1]);
    scanf("%d",&d);

    distance[c1-1][c2-1]=d;
    distance[c2-1][c1-1]=d;
    printf("Distance update successfully!\n");

}
void displayDistanceTable(int distance[MAX_CITIES][MAX_CITIES],char cities[MAX_CITIES][NAME_LENGTH],int count)
{
    if(count==0){
        printf("No cities avalible!\n");
        return;
    }
    printf("---Distance Table---\n");
    printf("%15s","");
    for(int i=0;i<count;i++)
        printf("%15s",cities[i]);
    printf("\n");

    for (int i=0;i<count;i++){
        printf("%15s",cities[i]);
        for(int j=0;j<count;j++)
            printf("%15d",distance[i][j]);
        printf("\n");
    }
}
void vehicalMangement()
{
    int van[4]={1000,30,60,12};
    int truck[4]={5000,40,50,6};
    int lorry[4]={10000,80,45,4};

    printf("Type\tCapacity(kg)\tRate per km(LKR)\tAvg Speed(km/h)\t\tFuel Efficiency(km/l)\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("Van\t%d\t\t%d\t\t\t%d\t\t\t%d\n",van[0],van[1],van[2],van[3]);
    printf("Truck\t%d\t\t%d\t\t\t%d\t\t\t%d\n",truck[0],truck[1],truck[2],truck[3]);
    printf("Lorry\t%d\t\t%d\t\t\t%d\t\t\t%d\n",lorry[0],lorry[1],lorry[2],lorry[3]);
}
void deliveryRequest(int distance[MAX_CITIES][MAX_CITIES], char cities[MAX_CITIES][NAME_LENGTH], int count)
{
    if (count < 2)
    {
        printf("Add at least 2 cities and set distances first!\n");
        return;
    }

    int vehicle[3][4] = {
        {1000, 30, 60, 12},
        {5000, 40, 50, 6},
        {10000, 80, 45, 4}};

    displayCities(cities, count);

    int src, dest, type;
    float weight;

    printf("Enter Source City Number: ");
    scanf("%d", &src);
    printf("Enter Destination City Number: ");
    scanf("%d", &dest);
    printf("Enter Weight (kg): ");
    scanf("%f", &weight);
    printf("Select Vehicle Type (1=Van, 2=Truck, 3=Lorry): ");
    scanf("%d", &type);

    if (src < 1 || src > count || dest < 1 || dest > count || src == dest)
    {
        printf("Invalid city selection!\n");
        return;
    }

    if (type < 1 || type > 3)
    {
        printf("Invalid vehicle type!\n");
        return;
    }

    int D = distance[src - 1][dest - 1];
    if (D == 0)
    {
        printf("Distance between %s and %s is not set yet!\n", cities[src - 1], cities[dest - 1]);
        return;
    }

    int cap = vehicle[type - 1][0];
    if (weight > cap)
    {
        printf("Weight exceeds vehicle capacity (%d kg)!\n", cap);
        return;
    }

    int R = vehicle[type - 1][1];
    int S = vehicle[type - 1][2];
    int E = vehicle[type - 1][3];
    float F = 310.0; // fuel price

    calculateCost(D, weight, R, S, E, F);
}

void calculateCost(int D, float W, int R, int S, int E, float F)
{
    float deliveryCost = D * R * (1 + (W / 10000.0));
    float time = (float)D / S;
    float fuelUsed = (float)D / E;
    float fuelCost = fuelUsed * F;
    float totalCost = deliveryCost + fuelCost;
    float profit = deliveryCost * 0.25;
    float customerCharge = totalCost + profit;

    printf("\n---- Delivery Calculation Summary ----\n");
    printf("Distance: %d km\n", D);
    printf("Weight: %.2f kg\n", W);
    printf("Delivery Cost: %.2f LKR\n", deliveryCost);
    printf("Estimated Time: %.2f hours\n", time);
    printf("Fuel Used: %.2f liters\n", fuelUsed);
    printf("Fuel Cost: %.2f LKR\n", fuelCost);
    printf("Total Operational Cost: %.2f LKR\n", totalCost);
    printf("Profit (25%%): %.2f LKR\n", profit);
    printf("Final Charge to Customer: %.2f LKR\n", customerCharge);
    printf("--------------------------------------\n");
}
