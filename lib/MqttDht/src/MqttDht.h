#ifndef MqttDht_h
#define MqttDht_h

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#define DHT11 11
#define DHT22 22
#define DHT21 21
#define AM2301 21

#define CELCIUS false
#define FAHRENHEIT true

#define DEBUG 1

class MqttDht
{
  public:
    MqttDht(uint8_t dpin,uint8_t dhtType, uint8_t count=6);

    void setup();
    float temperature(bool S=false, bool force=false);
    float humidity(bool force=false);
    float convertCtoF(float);
    float convertFtoC(float);
    float computeHeatIndex(float temperature, float percentHumidity, bool isFahrenheit=true);
    void setPin(int dpin);

  private:
    uint8_t data[5];
    uint8_t _pin;
    uint8_t _type;
    boolean read(bool force=false);
    #ifdef __AVR
    // Use direct GPIO access on an 8-bit AVR so keep track of the port and bitmask
    // for the digital pin connected to the DHT.  Other platforms will use digitalRead.
    uint8_t _bit, _port;
    #endif
    uint32_t _lastreadtime, _maxcycles;
    bool _lastresult;

    uint32_t expectPulse(bool level);
};

class InterruptLock {
    public:
     InterruptLock() {
      noInterrupts();
     }
     ~InterruptLock() {
      interrupts();
     }
};

#endif
