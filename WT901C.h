
class WT901C{
  public: 
  WT901C(int transmitter, int receiver);
  void update();

  struct AccelerationReading{
    double Ax;
    double Ay;
    double Az;
    double getX();
    double getY();
    double getZ();
  };
  struct RotationReading{
    double Rx;
    double Ry;
    double Rz;
    double getX();
    double getY();
    double getZ();
  };
  struct MagnetometerReading{
    double Mx;
    double My;
    double Mz;
    double getX();
    double getY();
    double getZ();
  };

  AccelerationReading getAccelerationReadings();
  RotationReading getRotationReadings();
  MagnetometerReading getMagneticFieldReadings();
  double getTemperature();

  private:
  int transmitterPin;
  int receiverPin;

  struct State{
  //Raw Acceleromter Reading
    AccelerationReading currentAcceleration;
  // Raw Rotation Reading
    RotationReading currentRotation;
  //Raw Magnetometer Reading
    MagnetometerReading currentMagneticReading;
  //temperature
    double temperature;

  } currentState;



};