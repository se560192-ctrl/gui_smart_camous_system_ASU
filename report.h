#pragma once
#include <string>
#include <iostream>
#include "building.h"
using namespace std;

// Eman declare any functions or structs related to generating reports in this file
// if you want a reference how to write in this file 
// you can check the other header files in this project like building.h, alert.h, reading.h, admin.h
// write functions definitions in report.cpp


// تحسب إجمالي استهلاك الحرم الجامعي وترجعه كرقم
float calculateTotalCampusConsumption(building buildings[], int building_counter);

// تجد المبنى الأكثر كفاءة وترجع اسمه
string getMostEfficientBuilding(building buildings[], int building_counter);

// تجد المبنى الأقل كفاءة وترجع اسمه
string getLeastEfficientBuilding(building buildings[], int building_counter);
