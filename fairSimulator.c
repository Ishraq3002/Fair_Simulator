#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PRICE_OF_ADMIT           15.26
#define SINGLE_RIDE_TICKET       1.13
#define ALL_RIDE_PASS            43.51
#define AVAILABLE_TICKETS        5000
#define AVAILABLE_ALLDAYPASS     200
#define TOTAL_RIDES              10
#define TOTAL_GUESTS             300


typedef struct {
  int    rideTickets;
  int    allDaypasses;
  float  totalAmount;
} TicketBoothType;

typedef struct {
  char  *name;
  int    numTicketReq;
  int    heightReq;
  int    numRiders;
  int    guestRefused;
} RideType;

typedef struct {
  int    age;
  int    height;
  float  money;
  int    tickets;
  int    allRidepass;
  int    rideCompleted;
} GuestType;

typedef struct {
  TicketBoothType booth;
  RideType        rides[TOTAL_RIDES];
} FairType;

int admitFair(FairType *fairptr, GuestType *guestptr);
int purchaseTickets(FairType *fairptr, GuestType *guestptr, int numTickets);
int purchaseAlldayPass(FairType *fairptr, GuestType *guestptr);
int guestGonnaRide(GuestType *guestptr, RideType *ride);

int main()
{
    FairType   fair;

    fair.booth.rideTickets  = AVAILABLE_TICKETS;
    fair.booth.allDaypasses = AVAILABLE_ALLDAYPASS;

    fair.rides[0].name = "Fun House";
    fair.rides[0].numTicketReq = 1;
    fair.rides[0].heightReq = 60; //cm

    fair.rides[1].name = "Merry-Go-Round";
    fair.rides[1].numTicketReq = 2;
    fair.rides[1].heightReq = 60; //cm

    fair.rides[2].name = "Calm Train";
    fair.rides[2].numTicketReq = 3;
    fair.rides[2].heightReq = 105; //cm

    fair.rides[3].name = "Tea Cups";
    fair.rides[3].numTicketReq = 3;
    fair.rides[3].heightReq = 108; //cm

    fair.rides[4].name = "Ferris Wheel";
    fair.rides[4].numTicketReq = 4;
    fair.rides[4].heightReq = 110; //cm

    fair.rides[5].name = "Back Destroyer";
    fair.rides[5].numTicketReq = 4;
    fair.rides[5].heightReq = 150; //cm

    fair.rides[6].name = "Pirate Ship";
    fair.rides[6].numTicketReq = 4;
    fair.rides[6].heightReq = 152; //cm

    fair.rides[7].name = "Drop To Death";
    fair.rides[7].numTicketReq = 5;
    fair.rides[7].heightReq = 154; //cm

    fair.rides[8].name = "Roller Coaster";
    fair.rides[8].numTicketReq = 5;
    fair.rides[8].heightReq = 156; //cm

    fair.rides[9].name = "Tummy Tosser";
    fair.rides[9].numTicketReq = 5;
    fair.rides[9].heightReq = 160; //cm

    GuestType   guest[TOTAL_GUESTS];

    srand(time(NULL));
    int num;
    for (int i = 0; i < TOTAL_GUESTS; i++){
        //Guest Age Distribution
        if (i <= TOTAL_GUESTS / 2){
            num = (rand() % (19 - 13 + 1)) + 13;
            guest[i].age = num;
        } else if ((i > TOTAL_GUESTS / 2) && (i < (3 * TOTAL_GUESTS / 4)) ){
            num = (rand() % (12 - 5 + 1)) + 5;
            guest[i].age = num;
        } else if((i >= (3 * TOTAL_GUESTS / 4)) && (i < TOTAL_GUESTS)){
            num = (rand() % (65 - 20 + 1)) + 20;
            guest[i].age = num;

        }

        //Guest Money Distribution
        int minMoney = ((rand() % (14 - 10 + 1)) + 10) * 2;
        int adultMoney = ((rand() % (9 - 4 + 1)) + 4) * 5;
        int numDecades = (guest[i].age) / 10;
        if (numDecades == 0){
            guest[i].money = minMoney;
        } else {
            guest[i].money = minMoney + (numDecades * adultMoney);
        }


        //Guest Height Distribution
        int heightChild = (rand() % (81 - 72 + 1)) + 72;
        int heightAdult = (rand() % (280 - 149 + 1)) + 149;

        if (guest[i].age <= 12){
            guest[i].height = (guest[i].age * 6) + heightChild;
        } else {
            guest[i].height = heightAdult;
        }

        admitFair(&fair, &guest[i]);
        int indiTicket = ((rand() % (8 - 2 + 1)) + 2) * 5;
        if (i <= TOTAL_GUESTS / 2){
            purchaseTickets(&fair, &guest[i], indiTicket);
        } else {
            purchaseAlldayPass(&fair, &guest[i]);
        }

        if (!purchaseAlldayPass(&fair, &guest[i])){
            purchaseTickets(&fair, &guest[i], 40);
        }

        if(!purchaseTickets(&fair, &guest[i], indiTicket)){
            indiTicket -= 5;
        } else if(!purchaseTickets(&fair, &guest[i], indiTicket) && indiTicket == 5 && indiTicket >= 1){
            indiTicket -= 1;
        } else {
            purchaseTickets(&fair, &guest[i], indiTicket);
        }


        //printf("%d = %d, mon = %.0f, dec = %d, height = %d, admit = %d, ticket = %d, pass = %d, inditicket = %d\n", i, guest[i].age, guest[i].money, numDecades, guest[i].height, admitFair(&fair, &guest[i]), purchaseTickets(&fair, &guest[i], indiTicket),purchaseAlldayPass(&fair, &guest[i]), indiTicket);
    }

    int randomRide;
    int n = 0;
    while(n < 20){
        for(int j = 0; j < TOTAL_GUESTS; j++){
            guest[j].rideCompleted = 0;
            if(guest[j].age <= 12){
                randomRide = (rand() % (4 - 0 + 1)) + 0;
                guestGonnaRide(&guest[j], &fair.rides[randomRide]);
                //guest[j].rideCompleted++;
            } else if(guest[j].age > 12){
                randomRide = (rand() % (9 - 5 + 1)) + 5;
                guestGonnaRide(&guest[j], &fair.rides[randomRide]);
                //guest[j].rideCompleted++;
            }
            //guest[j].rideCompleted++;
            if(guest[j].allRidepass == 0 || guest[j].tickets == 0){
                !guestGonnaRide(&guest[j], &fair.rides[TOTAL_RIDES]);
            }
            guest[j].rideCompleted++;
        }
        n++;
    }

    for(int k = 0; k < TOTAL_GUESTS; k++){
        printf("Guest %d, Age: %d, Height: %d, Money: %0.2f, Tickets: %d, Rides: %d\n", k, guest[k].age, guest[k].height, guest[k].money, guest[k].tickets, guest[k].rideCompleted);

    }
    printf("\n\n");

    for(int m = 0; m < TOTAL_GUESTS; m++){
        fair.booth.totalAmount += ((guest[m].tickets * SINGLE_RIDE_TICKET) + (guest[m].allRidepass * ALL_RIDE_PASS));
    }
    printf("$ %.2f has been earned\n\n", fair.booth.totalAmount);

    for(int r = 0; r < TOTAL_RIDES; r++){
        printf("%s allowed %d guests on but turned away %d guests\n", fair.rides[r].name, fair.rides[r].numRiders, fair.rides[r].guestRefused);
    }

    return 0;
}

int admitFair(FairType *fairptr, GuestType *guestptr){
    if(guestptr->age >= 13){
        guestptr->money = guestptr->money - PRICE_OF_ADMIT;
    } else if(guestptr->age > 6 && guestptr->age < 13) {
        guestptr->money = guestptr->money - (PRICE_OF_ADMIT / 2);
    } else if(guestptr->age <= 6){
        guestptr->money = guestptr->money - 0;
    }


    if(guestptr->money < 0)
        return 0;
    else
        return 1;
    /*if (guestptr->age >= 13 && guestptr->money >= PRICE_OF_ADMIT){
        guestptr->money = guestptr->money - PRICE_OF_ADMIT;
        return 1;
    } else
        return 0;

    if ((guestptr->age > 6 && guestptr->age < 13) && (guestptr->money >= (PRICE_OF_ADMIT / 2))){
        guestptr->money = guestptr->money - (PRICE_OF_ADMIT / 2);
        return 1;
    } else
        return 0;

    if (guestptr->age <= 6 && guestptr->money >= 0){
        return 1;
    } else
        return 0;

    //if (guestptr)*/
}


int purchaseTickets(FairType *fairptr, GuestType *guestptr, int numTickets){
    int totalCost = numTickets * SINGLE_RIDE_TICKET;
    guestptr->tickets = numTickets;
    if (guestptr->money >= totalCost && fairptr->booth.rideTickets >= numTickets && numTickets > 0){
        int a = AVAILABLE_TICKETS - numTickets;
        return 1;
    } else
        return 0;
}

int purchaseAlldayPass(FairType *fairptr, GuestType *guestptr){
    if(guestptr->money >= ALL_RIDE_PASS && fairptr->booth.allDaypasses > 0){
        guestptr->allRidepass = 1;
        int b = AVAILABLE_ALLDAYPASS - 1;
        return 1;
    } else
        return 0;
}


int guestGonnaRide(GuestType *guestptr, RideType *ride){
    ride->guestRefused = 0;
    ride->numRiders = 0;
    if(guestptr->height >= ride->heightReq && (guestptr->allRidepass == 1 || guestptr->tickets >= ride->numTicketReq)){
        ride->numRiders++;
        return 1;
    } else {
        ride->guestRefused++;
        return 0;
    }
}

























