#include<WT901C.h>
#include<Arduino.h>
#include<HardwareSerial.h>
#include<stdio.h>
#include<string>
// The WT901C constructor
// #### Parameters : 
// - port : the serial port connected to the sensor, is 2 by default.
WT901C::WT901C(byte port) {
    switch (port)
    {
    case 1: SerialWIT = &Serial1; break;
    
    default:
            SerialWIT = &Serial2; break;
        break;
    }
}

// The WT901C sensor constructor
// #### Parameters : 
// - serialPort : a pointer to the serial port connected to the sensor.
// #### Note :
// you do not need and should not start the serial port and should use WT901C::begin() instead
WT901C::WT901C(HardwareSerial* serialPort) : SerialWIT(serialPort) {}

//Get the X component of the current acceleration of the sensor in g (9.8067 m/s²).
// ### Limits : 
// The acceleration range is ±16g
double WT901C::AccelerationReading::getX(){return Ax;}
//Get the Y component of the current acceleration of the sensor in g (9.8067 m/s²).
// ### Limits : 
// The acceleration range is ±16g
double WT901C::AccelerationReading::getY() { return Ay;}
//Get the Z component of the ccurent acceleration of the sensor in g (9.8067 m/s²).
// ### Limits : 
// The acceleration range is ±16g
double WT901C::AccelerationReading::getZ() {return Az;}
// Returns a char array that is formatted in this format : 
// X : xValue m/s, Y : yValue m/s2, Z : zValue m/s2
char* WT901C::AccelerationReading::format() {
    static char formatted[64];
    std::sprintf(formatted, "X : %.4f m/s2, Y : %.4f m/s2, Z : %.4f m/s2", getX(), getY(), getZ());
    return formatted;
}

//Get the X(roll) component of the current angular velocity of the sensor in degrees per seconds.
// ### Limits : 
// The angular velocity of all angles have a range of ±2000°/s 
double WT901C::AngularVelocityReading::getX(){return Wx;}
//Get the Y(pitch) component of the current angular velocity of the sensor in degrees per seconds.
// ### Limits : 
// The angular velocity of all angles have a range of ±2000°/s 
double WT901C::AngularVelocityReading::getY() { return Wy;}
//Get the Z(yaw) component of the current angular velocity of the sensor in degrees per seconds.
// ### Limits : 
// The angular velocity of all angles have a range of ±2000°/s 
double WT901C::AngularVelocityReading::getZ() {return Wz;}

// Returns a char array that is formatted in this format : 
// X : xValue deg/s, Y : yValue deg/s, Z : zValue deg/s
char* WT901C::AngularVelocityReading::format() {
    static char formatted[64];
    std::sprintf(formatted, "X : %.4f deg/s, Y : %.4f deg/s, Z : %.4f deg/s", getX(), getY(), getZ());
    return formatted;
}

//Get the X(roll) component of the current angle of the sensor in degrees, represented as euler angles(X,Y,Z).
// ### Limits : 
// The angle components have a range of ±180 degrees
double WT901C::RotationReading::getX(){return Rx;}
//Get the Y(pitch) component of the current angle of the sensor in degrees, represented as euler angles(X,Y,Z).
// ### Limits : 
// The angle components have a range of ±180 degrees
double WT901C::RotationReading::getY() { return Ry;}
//Get the Z(yaw) component of the current angle of the sensor in degrees, represented as euler angles(X,Y,Z).
// ### Limits : 
// The angle components have a range of ±180 degrees
double WT901C::RotationReading::getZ() {return Rz;}

// Returns a char array that is formatted in this format : 
// X : xValue deg, Y : yValue deg, Z : zValue deg
char* WT901C::RotationReading::format() {
    static char formatted[64];
    std::sprintf(formatted, "X : %.4f deg, Y : %.4f deg, Z : %.4f deg", getX(), getY(), getZ());
    return formatted;
}

//Get the X component of the current magnetfic field strength of the sensor in Gauss.
// ### Limits : 
// The magnetic components have a range of ±2Gauss
double WT901C::MagnetometerReading::getX(){return Mx;}
//Get the Y component of the current magnetfic field strength of the sensor in Gauss.
// ### Limits : 
// The magnetic components have a range of ±2Gauss
double WT901C::MagnetometerReading::getY() { return My;}
//Get the Z component of the current magnetfic field strength of the sensor in Gauss.
// ### Limits : 
// The magnetic components have a range of ±2Gauss
double WT901C::MagnetometerReading::getZ() {return Mz;}
// Returns a char array that is formatted in this format : 
// X : xValue G, Y : yValue G, Z : zValue G
char* WT901C::MagnetometerReading::format() {
    static char formatted[64];
    std::sprintf(formatted, "X : %.4f G, Y : %.4f G, Z : %.4f G", getX(), getY(), getZ());
    return formatted;
}

// The method to initialize communication with the sensor
// #### Parameters
// - baud        : the baud rate represented as an integer, by defaut, this is usually 9600 bauds but the sensor could have been configured to use a diffenred baud rate.
// - receiver    : the receiver pin ID, usually 16, if on serial port 2
// - transmitter : the transmitter pin ID, usually 17, if on serial port 2
// #### NOTE
// THIS WILL ONLY COMPILE ON A ESP-32
void WT901C::begin(int baud, int receiver, int transmitter){
    SerialWIT->begin(baud, SERIAL_8N1, receiver, transmitter);
}

// The method to update the information given by the sensor, this should be called periodicly
void WT901C::update(){

        while(SerialWIT->available()){
            byte c = SerialWIT->read();
            if(idx ==0 && c != 0x55){
                continue;
            }

            buf[idx++] = c;
            
            if(idx == 11){
                byte sum = 0;
                for(int i = 0; i < 10; i++) sum += buf[i];
                if(buf[10] != sum) goto end; //Checksum

                temperature = ((short)(buf[9] << 8 | buf[8])) / 100.0f;

                switch (buf[1])
                {
                case 0x51: //Acceleration header
                    currentAcceleration.Ax = ((short)(buf[3] << 8 | buf[2]))/ 32768.0f * 16.0f;
                    currentAcceleration.Ay = ((short)(buf[5] << 8 | buf[4]))/ 32768.0f * 16.0f;
                    currentAcceleration.Az = ((short)(buf[7] << 8 | buf[6]))/ 32768.0f * 16.0f;
                    break;
                 
                case 0x52:
                    currentAngularVelocity.Wx = ((short)(buf[3] << 8 | buf[2]))/ 32768.0f * 2000.0f;
                    currentAngularVelocity.Wy = ((short)(buf[5] << 8 | buf[4]))/ 32768.0f * 2000.0f;
                    currentAngularVelocity.Wz = ((short)(buf[7] << 8 | buf[6]))/ 32768.0f * 2000.0f;
                    break;
                case 0x53:
                    currentRotation.Rx = ((short)(buf[3] << 8 | buf[2])) / 32768.0f * 180.0f;
                    currentRotation.Ry = ((short)(buf[5] << 8 | buf[4])) / 32768.0f * 180.0f;
                    currentRotation.Rz = ((short)(buf[7] << 8 | buf[6])) / 32768.0f * 180.0f;
                    break;
                case 0x54:
                    currentMagneticReading.Mx = ((short)(buf[3] << 8 | buf[2])) / 32768.0f * 2.0f;
                    currentMagneticReading.My = ((short)(buf[5] << 8 | buf[4])) / 32768.0f * 2.0f;
                    currentMagneticReading.Mz = ((short)(buf[7] << 8 | buf[6])) / 32768.0f * 2.0f;
                    break; 
                } 

                end: 
                idx = 0;

            }



        }
}

//return the acceleration readings obtained from the sensor
WT901C::AccelerationReading WT901C::getAccelerationReading(){
    return currentAcceleration;
}
//return the angular velocity readings obtained from the sensor
WT901C::AngularVelocityReading WT901C::getAngularVelocityReading(){
    return currentAngularVelocity;
}

//return the rotation readings obtained from the sensor
WT901C::RotationReading WT901C::getRotationReading(){
    return currentRotation;
}
//return the magnetic field readings obtained from the sensor
WT901C::MagnetometerReading WT901C::getMagneticFieldReading(){
    return currentMagneticReading;
}
//return the current temperature of the sensor
double WT901C::getTemperatureReading(){
    return temperature;
}



