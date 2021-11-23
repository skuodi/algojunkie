#include <stdio.h>

int monthLong[] = {31,28,31,30,31,30,31,31,30,31,30,31}; //length of months within the year
int startDate,startMonth,startYear, offset,remDays= 0;
int endDate,endMonth,endYear = 0;

int startSec,startMin,startHour = 0;
int offsetSec,offsetMin,offsetHour = 0;
int endSec,endMin,endHour = 0;

int leapness(int year);

int main(int argc, char const *argv[])
{
	printf("\n***********************************************************\n");
	printf("*********************TIMEWALKER****************************\n");
	printf("***********************************************************\n\n");
	printf("I'm rudimentary time machine at your disposal...\n");
	printf("I'll return a final date & time given a starting and an offset\n");
	printf("\t    and yes, I do account for leap years!!\n");
	printf("***********************************************************\n\n");
	printf("Enter a starting date in the format DD/MM/YY:\t");		//initial user prompt
	scanf("%i/%i/%i",&startDate,&startMonth,&startYear);						//take the starting date in user-friendly
	// printf("%i/%i/%i\n",startDate,startMonth,startYear);
	printf("How many days into the future?... \t");
	scanf("%i",&offset);													//days to be added
	printf("Enter the starting time in the 24-hour format HH:MM:SS ->\t");
	scanf("%i:%i:%i",&startHour,&startMin,&startSec);
	printf("Enter the time offset (time into the future) in the format HH:MM:SS ->\t");
	scanf("%i:%i:%i",&offsetHour,&offsetMin,&offsetSec);
	
	startSec += offsetSec;												//sum up the seconds

	startMin += startSec/60;											// increment the minutes if seconds overflow, and 
	endSec = startSec%60;													// set the final seconds reading to the overflow

	startMin += offsetMin;												// sum up the minutes
	startHour += startMin/60;											//	increment the hours if minutes overflow, and
	endMin = startMin%60;													// set the final minutes reading to the overflow

	startHour += offsetHour;											//sum up the hours
	offset+= startHour/24;												// increment the days if hours overflow, and
	endHour = startHour%24;													// set the final hours reading to the overflow

	endYear = startYear;
	while(offset>0){													//while there are days left to count
		if (leapness(endYear))												//give Feb 29 days if the current year is leap
			monthLong[1]=29;													

		for (int i = startMonth-1; i < 12; ++i)								//starting with the current month count forward
		{
			if (offset>0)													//if there are days to count
			{																//To count up given a starting date
				remDays = monthLong[i] - startDate;								// we first check if the count will overflow into the nextmonth*/
				if((offset - remDays) > 0){										// and if it will,
					offset -= remDays;												// the overflow becomes our new offset
					if(i==11){														//So if the current month is December, moving to the next month means
						endYear ++;														// moving to the next year
						endMonth = 1;startMonth = 1;									// setting the new month to be January
						if (leapness(endYear))												//give Feb 29 days if said new current year is leap
							monthLong[1]=29;
						else
							monthLong[1]=28;
					}else{													
					endMonth = i;												 
					}
					startDate = 0;												//Reset the counting of date to 0 for the new month
				}else{															//If the count doesn't overflow into another month,
					endDate = offset + startDate;									// our final date becomes the offset + the days already counted
					offset = 0;														// we finish counting
					endMonth = i+1;													// and set out final month to be the current month
					break;
				}
			}else{
				break;
			}
		}
	}
	printf("\nDestination Arrived (DD/MM/YYYY | HH:MM:SS Hrs): \t %i/%i/%i\t", endDate,endMonth,endYear);
	printf("|\t %i:%i:%i Hrs\n", endHour,endMin,endSec);

}
/**
 * Function to determine whether a year is leap using the year 2000 as a reference point*/
int leapness(int year){
	if((2000-year)%4)
		return 0;
	else
		return 1;
}
