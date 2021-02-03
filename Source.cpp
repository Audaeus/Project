#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

time_t start = time(0);

using namespace std;

int iterationFactor = 0; //velocity of rocket
int counter = 0; //point of this is to keep track of iterations
int upperLimit = rand() % 60 + 490; //range 490 - 550
int deployAlt = rand() % 20 + upperLimit; //range upperLimit - upperLimit + 60
float maxHeight = 0;
float pdHeight = 0;
clock_t t;
bool pdTrigger; //Given
bool pdDeploy = false; //Made
int deployTimes = 0;

float simpleSensor_Function() {

    float dataValue;

    try {
        dataValue = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 9.0)) + iterationFactor;

        if (counter < upperLimit) {
            iterationFactor += 20;
        }
        else {
            iterationFactor -= 20;
        }

        counter++;

        if (counter > (upperLimit * 2 + 10)) {
            throw "crashDetection";
        }
    }

    catch (...) {
        cout << "It appears we've turned this rocket into a lawn dart! MISSION FAILED";
        exit(0);
    }

    return dataValue;
}

float* noisySensor_Function() {

    float dataValue;
    float static dataSet[3];

    try {
        for (int i = 0; i < 3; i++) {
            dataSet[i] = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 9.0)) + iterationFactor;
        }

        if (counter <= upperLimit) {
            iterationFactor += 20;
        }
        else {
            iterationFactor -= 20;
        }

        if (deployAlt < counter)  {
            pdDeploy = true;
        }

        counter++;

        if (counter > (upperLimit * 2 + 10)) {
            throw "crashDetection";
        }
    }

    catch (...) {
        for (int i = 0; i < 3; i++) {
            cout << "\n";
        }
        t = clock() - t;
        cout << "---Flight Data---";
        cout << "\n" << "Total Flight Time: " << ((float)t) / CLOCKS_PER_SEC << " seconds.";
        cout << "\n" << "Max Altitude: " << maxHeight;
        cout << "\n" << "Parachute Deploy: " << pdHeight;
        cout << "\n" << "\n" << "It appears we've turned this rocket into a lawn dart! MISSION FAILED";
        for (int i = 0; i < 3; i++) {
            cout << "\n";
        }
        exit(0);
    }

    return dataSet;
}

int main()
{
    // display max altitude, height at which parachute is deployed, flight time
    t = clock(); // Start time lauch

    float* data; //https://www.tutorialspoint.com/cplusplus/cpp_return_arrays_from_functions.htm?fbclid=IwAR1NiTClRMcOKfu7gH_n3psQv2Q527U8YTKE5f6XmKHymrzQQiIe2qoWybs

    while (pdTrigger == false) { //trigger paracute deployment
        // Write code here
        // Implement either the simple sensor or noisy sensor function when completing the program
        data = noisySensor_Function();

        // Gather sensor data
        float sensorOne = *(data + 0);
        float sensorTwo = *(data + 0);
        float sensorThree = *(data + 0);
        float sensorAverage = (sensorOne + sensorTwo + sensorThree) / 3;

        // Display sensor data
        cout << sensorOne << " " << sensorTwo << " " << sensorThree << " Average Alt: " << sensorAverage << " Iteration step: " << counter << "\n";

        // Save max height
        if (sensorAverage > maxHeight) {
            maxHeight = sensorOne;
        }

        //Release parachute
        if (pdDeploy == true && deployTimes < 1) {
            cout << "\n" << "\n" << "------Release Parachute------" << "\n" << "\n" << "\n";
            pdHeight = sensorAverage;
            //pdTrigger = true;
            deployTimes++;
        }

    }
    return 0;
}
