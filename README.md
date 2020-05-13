# Smart-Health-Monitoring-System
Monitoring patient health whenever doctors/caretaker is not in the vicinity has always been a serious issue. With the number of patients rising each day and the lack of medical professionals in the region, it is laborious to analyze patient health status all the time. Thus, we need to find an IOT solution to this problematic situation.

One of the approaches is to monitor the health state of the patient and screen it to doctors or paramedical staff through the IoT, as it is hard to screen the patient for 24 hours. So here the patient health parameters such as Pulse rate, Respiratory rate, Body Temperature, Position of the body, ECG and so on can be measured by utilizing the Non-invasive sensors.

To keep a constant track of patient’s health condition, a variety of sensors can be used. This work presents a smart health monitoring system that uses biomedical sensors to check patient’s health condition and uses internet to inform the concerned. To keep this project simple, the biomedical sensors used in the proposed system are pulse sensor and temperature sensor. Pulse rate sensor can measure the heart rate of a person per minute which is typically around 70 beats per minute in normal state. Furthermore, the LM35 temperature sensor will measure body temperature.

These biomedical sensors are connected to Arduino UNO controller to read the data which is in turn interfaced to an LCD display/serial monitor to see the output. The "Thingspeak" named cloud is utilized here to store the detected data into the server.  From this server, data is converted into JSON link in order to send an SMS alert through IFTTT applet services whenever the system observes abnormal heart rate or abnormal human body temperature to the concerned doctor/caretaker.

The proposed IOT system can be used by the health care centres to monitor physiological statuses of patients through sensors by collecting and analyzing their information and then sending the analyzed patient’s data remotely to the concerned doctor/paramedical staff whenever the system detects a critical reading.


# HARDWARE SPECIFICATIONS
The components used in design and connections of the project are as follows:
1. ARDUINO UNO
2. LM35 TEMPERATURE SENSOR
3. PULSE SENSOR
4. ESP8266 WI-FI MODULE
5. LIQUID CRYSTAL DISPLAY
6. BREADBOARD
7. RESISTORS
8. JUMPER WIRES

# SOFTWARE SPECIFICATIONS
The software tools utilized during the course of the project are:
1. ARDUINO IDE
2. THINGSPEAK 
3. IFTTT

# Read the report for more details on project implementation.
