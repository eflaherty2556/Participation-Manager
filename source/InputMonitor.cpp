#include <unistd.h>
#include <ctime>
#include <iostream>
#include "QRScanner.h"
#include "User.h"
#include "request.h"
#include "result.h"
#include "GetUserRequest.cpp"
#include "UpdateUserRequest.cpp"
#include "Requester.h"
#include "LCD.h"

using namespace std;

void printDecodedUsers(vector<QRScanner::decodedObject> decodedObjects)
{
	for(int i = 0; i < decodedObjects.size(); i++)
	{
		QRScanner::decodedObject object = decodedObjects.at(i);
		printf("QR Code %d:\nType: '%s'\nData: '%s'\n", //Location: (%d, %d)\n
			i, (object.type).c_str(), (object.data).c_str()); //, object.location.at(0), object.location.at(1)
	}
}

User *requestUserInfo(QRScanner::decodedObject object)
{
	int userID = stoi(object.data);
	Request *myRequest = new GetUserRequest(userID);

	GetUserResult *result = (GetUserResult *)Requester::makeRequest(myRequest);
	vector<User *> *myUsers = result->getResults();

	return myUsers->at(0);
}

int getDaysInMonth(int month, int year)
{
	switch(month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31;
		case 4:
		case 6:
		case 9:
		case 11:
			return 30;
		case 2:
			if((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
				return 29;
			else
				return 28;
		default:
			printf("something has gone horribly wrong");
			return 0;

	}
}

int carryTime(int index, int month, int year)
{
	switch(index)
	{
		case 5:
		case 4:
			return 60; //seconds, minutes
		case 3:
			return 24; //hours
		case 2:
			return getDaysInMonth(month, year); //days
		case 1:
			return 12; //months
		default:
			printf("something has gone horribly wrong");
			return 0;
	}
}

string calculateTimeDifference(string previousTime, string currentTime)
{ 
	//Year, Month, Day, Hour, Minute, Second
	int previousTimeValues[6];
	int currentTimeValues[6];
	int differenceTime[6];

	sscanf(previousTime.c_str(), "%d-%d-%d %d:%d:%d ", &previousTimeValues[0], &previousTimeValues[1], 
		&previousTimeValues[2], &previousTimeValues[3], &previousTimeValues[4], &previousTimeValues[5]);
	sscanf(currentTime.c_str(), "%d-%d-%d %d:%d:%d ", &currentTimeValues[0], &currentTimeValues[1], 
		&currentTimeValues[2], &currentTimeValues[3], &currentTimeValues[4], &currentTimeValues[5]);

	for(int i = 5; i > 0; i--)
	{
		if(previousTimeValues[i] > currentTimeValues[i])
		{
			currentTimeValues[i-1]--;
			currentTimeValues[i] += carryTime(i, previousTimeValues[1], previousTimeValues[0]);
		}
		differenceTime[i] = currentTimeValues[i] - previousTimeValues[i];
	}
	differenceTime[0] = currentTimeValues[0] - previousTimeValues[0];

	char timeDifferenceBuffer[sizeof("0000-00-00 00:00:00 ")];
	sprintf(timeDifferenceBuffer, "%d-%d-%d %d:%d:%d ", differenceTime[0], differenceTime[1], 
		differenceTime[2], differenceTime[3], differenceTime[4], differenceTime[5]);

	string timeDifference(timeDifferenceBuffer);
	return timeDifference;
}

string calculateNewTimeSpent(string previousTime, string currentTime, string timeSpent)
{
	string additionalTime = calculateTimeDifference(previousTime, currentTime);

	int spentHours, spentMinutes, spentSeconds;
	int additionalYears, additionalMonths, additionalDays, additionalHours, additionalMinutes, additionalSeconds;
	int totalHours, totalMinutes, totalSeconds;

	sscanf(timeSpent.c_str(), "%d:%d:%d ", &spentHours, &spentMinutes, &spentSeconds);
	sscanf(additionalTime.c_str(), "%d-%d-%d %d:%d:%d ", &additionalYears, &additionalMonths, 
		&additionalDays, &additionalHours, &additionalMinutes, &additionalSeconds);

	//add individually, rather than dealing with library (https://www.includehelp.com/cpp-programs/add-two-times.aspx)
	totalSeconds = spentSeconds + additionalSeconds;
	totalMinutes = spentMinutes + additionalMinutes + (totalSeconds/60);
	totalHours = spentHours + additionalHours + (totalMinutes/60);

	totalMinutes %= 60;
	totalSeconds %= 60;

	char timeSpentBuffer[sizeof("00000:00:00 ")];
	sprintf(timeSpentBuffer, "%d:%d:%d ", totalHours, totalMinutes, totalSeconds);

	string timeSpentString(timeSpentBuffer);
	return timeSpentString;
}

void updateUserInfo(User *user)
{
	//handle time
	//parse iso string via sscanf (https://stackoverflow.com/questions/26895428/how-do-i-parse-an-iso-8601-date-with-optional-milliseconds-to-a-struct-tm-in-c)
	//read time via strftime (https://stackoverflow.com/questions/9527960/how-do-i-construct-an-iso-8601-datetime-in-c)
	time_t currentTime;
	time(&currentTime);
	char currentTimeBuffer[sizeof("0000-00-00 00:00:00 ")];
	strftime(currentTimeBuffer, sizeof(currentTimeBuffer), "%F %T", gmtime(&currentTime));
	
	string currentTimeString(currentTimeBuffer);
	string timeSpent;

	//only add time, if user was logged in, otherwise keep their time the same
	if(user->getIsLoggedIn())
		timeSpent = calculateNewTimeSpent(user->getLastLogTime(), currentTimeString, user->getTimeSpent());
	else
		timeSpent = user->getTimeSpent();


	//make request with new times
	Request *myRequest = new UpdateUserRequest(user->getId(), timeSpent, 
		currentTimeString, !(user->getIsLoggedIn()), user->getPrivilege());

	UpdateUserResult *myResults = (UpdateUserResult *)Requester::makeRequest(myRequest);

	printf("Successfully Logged in!\n");

}

int main(int argc, char *argv[])
{
	printf("Launching input monitor\n");

	//setup LCD
	LCD::setup();
	LCD::lcd_write(0, 0, "Welcome!");
	LCD::lcd_write(0, 1, "Please Sign in:");

	//setup camera
	bool cameraSetupSuccess = QRScanner::setupCamera();
	if(!cameraSetupSuccess)
	{
		printf("Unable to setup camera, exiting...\n");
		return 1;
	}

	vector<QRScanner::decodedObject> decodedObjects;
	QRScanner::decodedObject *currentObject = NULL;
	QRScanner::decodedObject *previousObject = NULL;
	Mat newImage;
	bool foundQR;
	int lastDisplayedText = -1; //used to prevent the lcd from being updated too frequently
	bool runForever = true; 

	while(runForever)
	{

		newImage = QRScanner::getImage();
		foundQR = QRScanner::decode(newImage, decodedObjects);

		if(foundQR)
		{	
			printf("QRCode found!");

			printDecodedUsers(decodedObjects);

			previousObject = currentObject;
			currentObject = &(decodedObjects.at(0));

			if(previousObject == NULL || ((*currentObject).data != (*previousObject).data) )
			{

				User *user = requestUserInfo(*currentObject);
				printf("User logged in:\n-ID: %d\n-Name: %s\n-Time Spent: %s\n-Last Log Time: %s\n-Logged in?: %d\n-Privilege Level: %d\n", 
					user->getId(), (user->getName()).c_str(), (user->getTimeSpent()).c_str(), (user->getLastLogTime()).c_str(),
					 user->getIsLoggedIn(), user->getPrivilege());

				updateUserInfo(user);

				if(lastDisplayedText != 1)
				{
					LCD::clear();
					LCD::lcd_write(0, 0, "Success! You");
					if(user->getIsLoggedIn())
						LCD::lcd_write(0, 1, "have logged in");
					else
						LCD::lcd_write(0, 1, "have logged out");

					lastDisplayedText = 1; //this is text option 1

					usleep(2000); //2 seconds
				}
				
					
			}
			else //same card as last sample
			{
				printf("Ok to remove card.\n");

				if(lastDisplayedText != 2)
				{
					LCD::clear();
					LCD::lcd_write(0, 0, "OK to remove");
					LCD::lcd_write(0, 1, "your card");
					lastDisplayedText = 2; //this is text option 2
				}
				
			}
		}
		else
		{
			printf("Waiting for ID card...\n");

			if(lastDisplayedText != 3)
			{
				LCD::clear();
				LCD::lcd_write(0, 0, "Welcome!");
				LCD::lcd_write(0, 1, "Please Sign in:");
				lastDisplayedText = 3; //this is text option 3
			}
			
		}

		usleep(2500); //2.5 seconds
	}

	QRScanner::shutdownCamera();
	LCD::clear();
}
