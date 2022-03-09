# Fair_Simulator
Created by: Md Ishraq Tanzim
Date: 	    February, 2022

The C program simulates a fair in which guests admit themselves to the fair and then go onto rides buying the required number of tickets and all day passes from the ticket booth.

1) A single fair is created in the program with 5000 available tickets, 200 available all-day-ride-passes and exactly 10 rides.

2) A fixed array is created that can hold 300 guests. The code fills in the array using the following rules based on a random number generator:
	o The ages:
		▪ Roughly 1/2 of the guests are in the range of 13 to 19 years of age.
		▪ Roughly 1/4 of the guests are in the range of 5 to 12 years of age.
		▪ Roughly 1/4 of the guests are in the range of 20 to 65 years of age.
	o The money:
		▪ Each guest has a minimum of $20, $22, $24, $26 or $28 chosen randomly.
		▪ If the guest is 10 years of age or more, more money is added to their starting amount by adding the following amount to the money for each full decade of age that they have been alive (i.e., a 13 year old has been alive for 1 decade, a 37 year old for 3 decades, etc..):
		  (# full decades) X ($20, $25, $30, $35, $40 or $45 chosen randomly).
	o The heights:
		▪ A guest who is 12 or under has a height which is (age * 6) + a random amount from 72 to 81 inclusively.
		▪ A guest who is over 12 has a height between 149 and 280 inclusively.

3) The admitFair() function simulates the admitting of a guest to the fair.

4) The purchaseTickets() function simulates the purchasing of ride tickets.

5) The purchaseAlldayPass() function simulates the purchasing of a single all-day-ride-pass.

6) In the main() function, after the guests have been created, the program simulates ALL the guests attempting to be admitted to the fair and purchasing tickets and ride passes.

7) The guestGonnaRide() function simulates a guest going onto a ride.

6) Command for compiling the code in linux environment: gcc -o fairSimulator fairSimulator.c
7) Command for running the code after compiling	      : ./fairSimulator	 

