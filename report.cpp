#include<iostream>
#include<string>
#include "building.h"
#include "alert.h"
#include "reading.h"
#include "admin.h"
#include "report.h"
using namespace std;

// define any functions related to generating reports in this file ---> Eman

//define function to generate monthly campus report
void generateMonthlyCampusReport(building buildings[],int building_counter, int numberOfUnresolvedAlerts, int numberOfResolvedAlerts) {

	cout << " ______MONTHLY CAMPUS REPORT______ " << endl;
    calculateTotalCampusConsumption(buildings, building_counter);
    findMostEfficientBuilding(buildings, building_counter);
    findLeastEfficientBuilding(buildings, building_counter);
	cout << "Number of unresolved alerts: " << numberOfUnresolvedAlerts << endl;
	cout << "Number of resolved alerts: " << numberOfResolvedAlerts << endl;
}

// define function to calculate Total Campus Consumption
void calculateTotalCampusConsumption(building buildings[], int building_counter) {

    float total_campus_consumption = 0.0 ;
    // Calculate total campus consumption by summing the total consumption for each building
    for (int i = 0; i < building_counter; i++) {
        total_campus_consumption += buildings[i].Total_consumption ;
    }

    cout << "The total campus consumption : " << total_campus_consumption <<" kWh "<<endl;
}

// define function to find the most efficient building
void findMostEfficientBuilding(building buildings[],  int building_counter) {

    float most_efficient_score = buildings[0].Efficiency_Score ;
    string most_efficient_building = buildings[0].Name ;

    for (int i = 1; i < building_counter; i++) {

        //Determine the most efficient building by finding the highest  efficiency score
        if (buildings[i].Efficiency_Score > most_efficient_score) {
            most_efficient_score = buildings[i].Efficiency_Score ;
            most_efficient_building = buildings[i].Name ;
        }

    }
    cout << "The most efficient building is " << most_efficient_building << endl ;

}

// define function to find the least efficient building 
void findLeastEfficientBuilding(building buildings[], int building_counter) {

    float least_efficient_score = buildings[0].Efficiency_Score ;
    string least_efficient_building = buildings[0].Name ;

    for (int i = 1; i < building_counter; i++) {
        //Determine the least efficient building by finding the lowest efficiency score
        if (buildings[i].Efficiency_Score < least_efficient_score) {
            least_efficient_score = buildings[i].Efficiency_Score ;
            least_efficient_building = buildings[i].Name ;
        }
    }

    cout << "The least efficient building is " << least_efficient_building << endl ;
}
