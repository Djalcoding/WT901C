#include<WT901C.h>
#include<Arduino.h>
#include<HardwareSerial.h>

WT901C::WT901C(byte port) {
    switch (port)
    {
    case 1: SerialWIT = &Serial1; break;
    
    default:
            SerialWIT = &Serial2; break;
        break;
    }
}

double WT901C::AccelerationReading::getX(){return Ax;}
double WT901C::AccelerationReading::getY() { return Ay;}
double WT901C::AccelerationReading::getZ() {return Az;}

double WT901C::AngularVelocityReading::getX(){return Wx;}
double WT901C::AngularVelocityReading::getY() { return Wy;}
double WT901C::AngularVelocityReading::getZ() {return Wz;}


double WT901C::RotationReading::getX(){return Rx;}
double WT901C::RotationReading::getY() { return Ry;}
double WT901C::RotationReading::getZ() {return Rz;}

double WT901C::MagnetometerReading::getX(){return Mx;}
double WT901C::MagnetometerReading::getY() { return My;}
double WT901C::MagnetometerReading::getZ() {return Mz;}


void WT901C::begin(int baud, int receiver, int transmitter){
    SerialWIT->begin(baud, SERIAL_8N1, receiver, transmitter);
}

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
                    currentAcceleration.Ay = ((short)(buf[5] << 8 | buf[4]))/ 32768.0f * 16.0f;;
                    currentAcceleration.Az = ((short)(buf[7] << 8 | buf[6]))/ 32768.0f * 16.0f;;
                    break;
                 
                case 0x52:
                    currentAngularVelocity.Wx = ((short)(buf[3] << 8 | buf[2]))/ 32768.0f * 180.0f;
                    currentAngularVelocity.Wy = ((short)(buf[5] << 8 | buf[4]))/ 32768.0f * 180.0f;
                    currentAngularVelocity.Wz = ((short)(buf[7] << 8 | buf[6])) / 32768.0f * 180.0f;
                    break;
                case 0x53:
                    currentRotation.Rx = ((short)(buf[3] << 8 | buf[2])) / 32768.0f * 180.0f;
                    currentRotation.Ry = ((short)(buf[5] << 8 | buf[4])) / 32768.0f * 180.0f;
                    currentRotation.Rz = ((short)(buf[7] << 8 | buf[6])) / 32768.0f * 180.0f;
                    break;
                case 0x54:
                    currentMagneticReading.Mx = ((short)(buf[3] << 8 | buf[2])) / 32768.0f * 16.0f;
                    currentMagneticReading.My = ((short)(buf[5] << 8 | buf[4])) / 32768.0f * 16.0f;
                    currentMagneticReading.Mz = ((short)(buf[7] << 8 | buf[6])) / 32768.0f * 16.0f;
                    break; 
                } 

                end: 
                idx = 0;

            }



        }
}

WT901C::AccelerationReading WT901C::getAccelerationReadings(){
    return currentAcceleration;
}
WT901C::AngularVelocityReading WT901C::getAngularVelocityReadings(){
    return currentAngularVelocity;
}
WT901C::RotationReading WT901C::getRotationReadings(){
    return currentRotation;
}
WT901C::MagnetometerReading WT901C::getMagneticFieldReadings(){
    return currentMagneticReading;
}



