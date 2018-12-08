#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;
//Th approach is to calculate UserSum i.e sum total of weightage multiplied by 
//the choice(+1 or -1) over all preferences  . So we assume male as +1 and female as -1 for instance.

//This Function returns the User sum for a specific user
int GetUserSum(int *U, int *W)
{
	int UserSum = 0;
	for (int i = 1; i < 6; i++)
	{
		UserSum += *(U+i) * (*(W+i-1));
	}
	return UserSum;
 
}
//This return the array of userids sorted according to Usersum. Partioning into groups of contiguos groups of
//5 gives us the answer
void GetFinalUserIds(vector<int> SumSet, map<int, int> SumMap, vector<int> &FinUserId)
{
	
	map<int, int>::iterator it;
	for (size_t i = 0; i < SumSet.size(); i++)
	{
		for (it = SumMap.begin(); it != SumMap.end(); it++)
		{
			if (it->second == SumSet[i])
			{
				FinUserId.push_back(it->first);
			}
		}
	}
}
 

int main()
{
	//set of weights for 5 different preferences 
	//for preference i ,the weight is a[i]
	int WeightOfPreferences[5];
	//The first element is Unique User id and other 5 elements are +1 and -1 depending on the user preferenec
	int UserPreferences[6];
	map<int, int> UserNetSumMap;
	vector<int> UserSumSet;
	vector<int> temp;
	vector<int> FinalUserIds;
	int UserSum = 0;
	int j;
	int size;
	bool valid = true;
	

	cout <<"Enter the weight of different preferences :- ";
	// Sample input [ 10000,1000,100,10 ,10]
	for (int i=0; i < 5; i++)
	{
		cin >> WeightOfPreferences[i];
    }
	
	
	cout << "Enter the number of users";
	cin >> size;
	while (size > 0)
	{
		j = 1;
		cout << endl;
		cout << "Enter the new user's ID and his 5 preferences:- (+1 or -1) ";
		//Sample input [2 1 -1 1 -1 1]
		for (int i = 0; i < 6; i++)
		{
			cin>>UserPreferences[i];			
        }
		for (int i = 1; i < 6; i++)
		{
			if (abs(UserPreferences[i]) != 1)
			{
				cout << "Invalid input. Choices should be +1 or -1";
				valid = false;
				break;
			}
			
		}
		if (!valid)
		{
			valid = true;
			continue;
		}
		if (UserNetSumMap.find(UserPreferences[0]) != UserNetSumMap.end())
		{
			cout << "This user id has been already entered. Enter a new user";
			continue;
		}

		UserSum = GetUserSum(UserPreferences, WeightOfPreferences);

		UserSumSet.push_back(UserSum); //Inserting UserSum in a vector

		UserNetSumMap.insert(pair<int,int>(UserPreferences[0], UserSum)); //This maintains the user sum for a specific user

		sort(UserSumSet.begin(), UserSumSet.end());
		UserSumSet.erase(unique(UserSumSet.begin(), UserSumSet.end()), UserSumSet.end());


	  GetFinalUserIds(UserSumSet,UserNetSumMap,FinalUserIds);

		for (size_t i = 0; i < FinalUserIds.size(); i++)
		{
			if (i % 5 == 0)
			{
				cout << endl;
				cout <<"Group"<<j<< "has users:- ";
				j++;
			}
			cout << FinalUserIds[i] << " ";
		}
		FinalUserIds.clear();
		size--;
	}
	//For avoiding closing of command prompt
	int ch;
	cin >> ch;

}