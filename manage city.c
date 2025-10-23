#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_CITIES 30
#define NAME_LENGTH 50
#define MAX_DELIVERIES 50
#define FUEL_PRICE 310.00

typedef struct {
char source[NAME_LENGTH];
char destination[NAME_LENGTH];
char vehical[50];
float weight;
float distance;
float cost;
}Delivery;

typedef struct {
    char name[20];
    int capacity;
    float ratePerKm;
    float avgSpeed;
    float fuelEfficiency;
} Vehicle;

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
void deliveryRecordMenu(Delivery deliveries[MAX_DELIVERIES],int *deliveryCount);
void addDeliveryRecord(Delivery deliveries[MAX_DELIVERIES], int *deliveryCount);
void displayDeliveryRecords(Delivery deliveries[MAX_DELIVERIES], int deliveryCount);
void findLeastDistanceRoute(int distance[MAX_CITIES][MAX_CITIES], char cities[MAX_CITIES][NAME_LENGTH], int count);
void deliveryCostEstimation();


int main()
{
    int count=0;
    int deliveryCount =0;
    Delivery deliveries[MAX_DELIVERIES];


    char cities[MAX_CITIES][NAME_LENGTH];
    int distance[MAX_CITIES][MAX_CITIES]={0};
    int D,R,S,E;
    float W,F;
    int choice;
    int src;
    int dest;

    do
    {
        printf("===Logistics & Delivery Management System===\n");
        printf("1.City Management\n");
        printf("2.Distance Management\n");
        printf("3.Vehicle Management(show vehicle info)\n");
        printf("4.Delivery Request and Cost,Time,Fuel Calculations\n");
        printf("5.Delivery Records Mangement\n");
        printf("6.Find the Least-Cost Route\n");
        printf("7.To get Delivery Cost Estimate\n");
        printf("8.Exit\n");
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
             deliveryRecordMenu(deliveries, &deliveryCount);
            break;
        case 6:
            findLeastDistanceRoute(distance,cities,count);
            break;
        case 7:
             deliveryCostEstimation();
             break;
        case 8:
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
        printf("===Distance Management===\n");
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
void deliveryRecordMenu(Delivery Deliveries[MAX_DELIVERIES],int *deliveryCount)
{
    int choice3;
    do{
        printf("---Delivery Records Management---\n");
        printf("1.Add Delivery Record\n");
        printf("2.Display All Delvery Records\n");
        printf("3.Exit\n");
        printf("Enter your choice:");
        scanf("%d",&choice3);
        while(getchar()!='\n');
        switch(choice3)
        {
        case 1:
            addDeliveryRecord(Deliveries, deliveryCount);
            break;
        case 2:
            displayDeliveryRecords(Deliveries, *deliveryCount);
            break;
        case 3:
            printf("Exit\n");
            break;
        default:
            printf("Invalid Input!\n");
        }
    }while(choice3!=3);
}
void addDeliveryRecord(Delivery deliveries[MAX_DELIVERIES],int *deliveryCount)
{

    if (*deliveryCount >= MAX_DELIVERIES)
    {
        printf("Delivery record limit reached (max 50)!\n");
        return;
    }

    Delivery newDelivery;

    printf("Enter Source City: ");
    fgets(newDelivery.source, sizeof(newDelivery.source), stdin);
    newDelivery.source[strcspn(newDelivery.source, "\n")] = '\0';

    printf("Enter Destination City: ");
    fgets(newDelivery.destination, sizeof(newDelivery.destination), stdin);
    newDelivery.destination[strcspn(newDelivery.destination, "\n")] = '\0';

    printf("Enter Vehicle Type (Van/Truck/Lorry): ");
    fgets(newDelivery.vehical, sizeof(newDelivery.vehical), stdin);
    newDelivery.vehical[strcspn(newDelivery.vehical, "\n")] = '\0';

    printf("Enter Weight (kg): ");
    scanf("%f", &newDelivery.weight);

    printf("Enter Distance (km): ");
    scanf("%f", &newDelivery.distance);

    printf("Enter Total Cost (LKR): ");
    scanf("%f", &newDelivery.cost);

    deliveries[*deliveryCount] = newDelivery;
    (*deliveryCount)++;

    printf("Delivery record added successfully!\n");
}
void deliveryRecordsMenu(Delivery deliveries[MAX_DELIVERIES], int *deliveryCount)
{
    int choice;
    do {
        printf("\n=== Delivery Records Management ===\n");
        printf("1. Add Delivery Record\n");
        printf("2. Display All Delivery Records\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch(choice)
        {
            case 1:
                addDeliveryRecord(deliveries, deliveryCount);
                break;
            case 2:
                displayDeliveryRecords(deliveries, *deliveryCount);
                break;
            case 3:
                printf("Exiting Delivery Records Management...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 3);
}


void displayDeliveryRecords(Delivery deliveries[MAX_DELIVERIES], int deliveryCount)
{
    if (deliveryCount == 0)
    {
        printf("No delivery records available.\n");
        return;
    }

    printf("\n--- All Delivery Records ---\n");
    for (int i = 0; i < deliveryCount; i++)
    {
        printf("\nRecord #%d:\n", i + 1);
        printf("Source: %s\n", deliveries[i].source);
        printf("Destination: %s\n", deliveries[i].destination);
        printf("Vehicle: %s\n", deliveries[i].vehical);
        printf("Weight: %.2f kg\n", deliveries[i].weight);
        printf("Distance: %.2f km\n", deliveries[i].distance);
        printf("Cost: %.2f LKR\n", deliveries[i].cost);
    }
}
void findLeastDistanceRoute(int distance[MAX_CITIES][MAX_CITIES], char cities[MAX_CITIES][NAME_LENGTH], int count)
{
    if (count < 2)
    {
        printf("Add at least 2 cities and set distances first!\n");
        return;
    }

    int src, dest;
    displayCities(cities, count);

    printf("Enter Source City Number: ");
    scanf("%d", &src);
    printf("Enter Destination City Number: ");
    scanf("%d", &dest);

    if (src < 1 || src > count || dest < 1 || dest > count || src == dest)
    {
        printf("Invalid city selection!\n");
        return;
    }

    int dist[MAX_CITIES];
    int visited[MAX_CITIES];
    int prev[MAX_CITIES];

    // Initialize arrays
    for (int i = 0; i < count; i++)
    {
        dist[i] = 999999;
        visited[i] = 0;
        prev[i] = -1;
    }
    dist[src - 1] = 0;

    // Dijkstra’s algorithm
    for (int i = 0; i < count - 1; i++)
    {
        int min = 999999, u = -1;
        for (int j = 0; j < count; j++)
        {
            if (!visited[j] && dist[j] <= min)
            {
                min = dist[j];
                u = j;
            }
        }
        if (u == -1)
            break;

        visited[u] = 1;

        for (int v = 0; v < count; v++)
        {
            if (!visited[v] && distance[u][v] && dist[u] + distance[u][v] < dist[v])
            {
                dist[v] = dist[u] + distance[u][v];
                prev[v] = u;
            }
        }
    }

    if (dist[dest - 1] == 999999)
    {
        printf("No valid route found between %s and %s!\n", cities[src - 1], cities[dest - 1]);
        return;
    }

    // Print shortest route
    int path[MAX_CITIES];
    int index = 0;
    for (int v = dest - 1; v != -1; v = prev[v])
        path[index++] = v;

    printf("\n=============================================\n");
    printf("  SHORTEST ROUTE RESULT\n");
    printf("=============================================\n");
    printf("From: %s\nTo: %s\n", cities[src - 1], cities[dest - 1]);
    printf("Route: ");
    for (int i = index - 1; i >= 0; i--)
    {
        printf("%s", cities[path[i]]);
        if (i > 0) printf(" -> ");
    }
    printf("\nMinimum Distance: %d km\n", dist[dest - 1]);
    printf("=============================================\n");
}
void deliveryCostEstimation() {
    Vehicle vehicles[3] = {
        {"Van",   1000, 30, 60, 12},
        {"Truck", 5000, 40, 50, 6},
        {"Lorry", 10000, 45, 40, 4}
    };

    char fromCity[30], toCity[30];
    float distance;
    int weight, choice;

    printf("Enter From City: ");
    scanf("%s", fromCity);
    printf("Enter To City: ");
    scanf("%s", toCity);
    printf("Enter delivery distance (km): ");
    scanf("%f", &distance);
    printf("Enter parcel weight (kg): ");
    scanf("%d", &weight);

    printf("\nSelect Vehicle Type:\n");
    printf("1. Van\n2. Truck\n3. Lorry\nEnter choice: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > 3) {
        printf("Invalid vehicle selection!\n");
        return;
    }

    Vehicle v = vehicles[choice - 1];


    printf("\n======================================================\n");
    printf("DELIVERY COST ESTIMATION\n");
    printf("------------------------------------------------------\n");
    printf("From: %s\n", fromCity);
    printf("To: %s\n", toCity);
    printf("Minimum Distance: %.2f km\n", distance);
    printf("Vehicle: %s\n", v.name);
    printf("Weight: %d kg\n", weight);
    printf("------------------------------------------------------\n");


    float baseCost = distance * v.ratePerKm * (1 + (float)weight / v.capacity);


    float fuelUsed = distance / v.fuelEfficiency;
    float fuelCost = fuelUsed * FUEL_PRICE;


    float operationalCost = baseCost + fuelCost;
    float profit = operationalCost * 0.25;
    float customerCharge = operationalCost + profit;


    float estimatedTime = distance / v.avgSpeed;


    printf("Base Cost: %.2f × %.2f × (1 + %d/%d) = %.2f LKR\n",
           distance, v.ratePerKm, weight, v.capacity, baseCost);
    printf("Fuel Used: %.2f L\n", fuelUsed);
    printf("Fuel Cost: %.2f LKR\n", fuelCost);
    printf("Operational Cost: %.2f LKR\n", operationalCost);
    printf("Profit: %.2f LKR\n", profit);
    printf("Customer Charge: %.2f LKR\n", customerCharge);
    printf("Estimated Time: %.2f hours\n", estimatedTime);
    printf("======================================================\n");
}
