#include "TimeManager.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip> 


//#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable : 4996)

using namespace std;


string TimeManager::GetCurrentTime1()
{
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    
    tm local_tm;
    localtime_s(&local_tm, &now_time);
    /*tm local_tm = *localtime_s(&now_time);*/

    ostringstream oss;
    oss << put_time(&local_tm, "%Y-%m-%d %H:%M:%S"); 
    return oss.str();


}