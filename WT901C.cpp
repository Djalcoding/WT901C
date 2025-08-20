#include<WT901C.h>
#include<Arduino.h>


WT901C::WT901C(int transmiter, int receiver){
    transmitterPin = transmiter;
    receiverPin = receiver;
}
WT901C::AccelerationReading WT901C::getAccelerationReadings(){
    return currentState.currentAcceleration;
}
WT901C::RotationReading WT901C::getRotationReadings(){
    return currentState.currentRotation;
}
WT901C::MagnetometerReading WT901C::getMagneticFieldReadings(){
    return currentState.currentMagneticReading;
}

