#include<Arduino.h>
#include<HardwareSerial.h>
#include<string>
class WT901C{
  public:
  WT901C(byte port);
  WT901C(HardwareSerial* serial);

  void begin(int baud, int rx, int tx);
  void update();

  // A struct that contains the three variables(x,y,z) of acceleration
  struct AccelerationReading{
    double Ax;
    double Ay;
    double Az;
    double getX();
    double getY();
    double getZ();
    char* format();
  };

  // A struct that contains the three variables(x,y,z) of angular velocity
  struct AngularVelocityReading{
    double Wx;
    double Wy;
    double Wz;
    double getX();
    double getY();
    double getZ();
    char* format();
  };

  // A struct that contains the three variables(x,y,z) of rotation 
  struct RotationReading{
    double Rx;
    double Ry;
    double Rz;
    double getX();
    double getY();
    double getZ();
    char* format();
  };

  // A struct that contains the three variables(x,y,z) of magnetic field strenght
  struct MagnetometerReading{
    double Mx;
    double My;
    double Mz;
    double getX();
    double getY();
    double getZ();
    char* format(); 
  };

  AccelerationReading getAccelerationReading();
  RotationReading getRotationReading();
  MagnetometerReading getMagneticFieldReading();
  AngularVelocityReading getAngularVelocityReading();
  double getTemperatureReading();

  private:
  //HardwareSerial SerialWIT;

  byte idx = 0;
  byte buf[11];

  HardwareSerial* SerialWIT;
  //Raw Acceleromter Reading
    AccelerationReading currentAcceleration;
  //Raw Angular Velocity Reading
    AngularVelocityReading currentAngularVelocity;
  // Raw Rotation Reading
    RotationReading currentRotation;
  //Raw Magnetometer Reading
    MagnetometerReading currentMagneticReading;
  //temperature
    double temperature;



};