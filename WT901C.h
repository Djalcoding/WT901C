#include<Arduino.h>
#include<HardwareSerial.h>
class WT901C{
  public:
    // The WT901C constructor
    // #### Parameters : 
    // - port : the serial port connected to the sensor, is 2 by default.
  WT901C(byte port);
    // The WT901C constructor
    // #### Parameters : 
    // - serialPort : a pointer to the serial port connected to the sensor.
    // #### Note :
    // you do not need and should not start the serial port and should use WT901C::begin() instead
  WT901C(HardwareSerial* serial);

// The method to initialize communication with the sensor
// #### Parameters
// - baud        : the baud rate represented as an integer, by defaut, this is usually 9600 bauds but the sensor could have been configured to use a diffenred baud rate.
// - receiver    : the receiver pin ID, usually 16, if on serial port 2
// - transmitter : the transmitter pin ID, usually 17, if on serial port 2
// #### NOTE
// THIS WILL ONLY COMPILE ON A ESP-32
  void begin(int baud, int rx, int tx);

// The method to update the information given by the sensor, this should be called periodicly
  void update();

  // A struct that contains the three variables(x,y,z) of acceleration
  struct AccelerationReading{
    double Ax;
    double Ay;
    double Az;

    //Get the X component of the current acceleration of the sensor in g (9.8067 m/s²).
    // ### Limits : 
    // The acceleration range is ±16g
    double getX();

    //Get the Y component of the current acceleration of the sensor in g (9.8067 m/s²).
    // ### Limits : 
    // The acceleration range is ±16g
    double getY();

    //Get the Z component of the ccurent acceleration of the sensor in g (9.8067 m/s²).
    // ### Limits : 
    // The acceleration range is ±16g
    double getZ();

    // Returns a char array that is formatted in this format : 
    // X : xValue g, Y : yValue g, Z : zValue g
    char* format();
  };

  // A struct that contains the three variables(x,y,z) of angular velocity
  struct AngularVelocityReading{
    double Wx;
    double Wy;
    double Wz;

    //Get the X(roll) component of the current angular velocity of the sensor in degrees per seconds.
    // ### Limits : 
    // The angular velocity of all angles have a range of ±2000°/s 
    double getX();

    //Get the Y(pitch) component of the current angular velocity of the sensor in degrees per seconds.
    // ### Limits : 
    // The angular velocity of all angles have a range of ±2000°/s 
    double getY();

    //Get the Z(yaw) component of the current angular velocity of the sensor in degrees per seconds.
    // ### Limits : 
    // The angular velocity of all angles have a range of ±2000°/s 
    double getZ();

    // Returns a char array that is formatted in this format : 
    // X : xValue deg/s, Y : yValue deg/s, Z : zValue deg/s
    char* format();
  };

  // A struct that contains the three variables(x,y,z) of rotation 
  struct RotationReading{
    double Rx;
    double Ry;
    double Rz;

    //Get the X(roll) component of the current angle of the sensor in degrees, represented as euler angles(X,Y,Z).
    // ### Limits : 
    // The angle components have a range of ±180 degrees
    double getX();

    //Get the Y(pitch) component of the current angle of the sensor in degrees, represented as euler angles(X,Y,Z).
    // ### Limits : 
    // The angle components have a range of ±180 degrees
    double getY();

    //Get the Z(yaw) component of the current angle of the sensor in degrees, represented as euler angles(X,Y,Z).
    // ### Limits : 
    // The angle components have a range of ±180 degrees
    double getZ();

    // Returns a char array that is formatted in this format : 
    // X : xValue deg, Y : yValue deg, Z : zValue deg
    char* format();
  };

  // A struct that contains the three variables(x,y,z) of magnetic field strenght
  struct MagnetometerReading{
    double Mx;
    double My;
    double Mz;
    //Get the X component of the current magnetfic field strength of the sensor in Gauss.
    // ### Limits : 
    // The magnetic components have a range of ±2Gauss
    double getX();

    //Get the Y component of the current magnetfic field strength of the sensor in Gauss.
    // ### Limits : 
    // The magnetic components have a range of ±2Gauss
    double getY();

    //Get the Z component of the current magnetfic field strength of the sensor in Gauss.
    // ### Limits : 
    // The magnetic components have a range of ±2Gauss
    double getZ();

    // Returns a char array that is formatted in this format : 
    // X : xValue G, Y : yValue G, Z : zValue G
    char* format(); 
  };

//return the acceleration readings obtained from the sensor
  AccelerationReading getAccelerationReading();
//return the rotation readings obtained from the sensor
  RotationReading getRotationReading();
//return the magnetic field readings obtained from the sensor
  MagnetometerReading getMagneticFieldReading();
//return the angular velocity readings obtained from the sensor
  AngularVelocityReading getAngularVelocityReading();
//return the current temperature of the sensor
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
