#ifndef controller_h
#define controller_h

#include <Arduino.h>
#include <BLEServer.h>

enum MODE
{
  PAIRING,
  CONNECTED
};

class Controller
{
private:
  MODE _mode = PAIRING;
  BLECharacteristic *_feedbackCharacteristic;
  BLECharacteristic *_commandCharacteristic;
  void (*_onDisconnection)(void);
  void (*_moveForwardCmd)(uint16_t stepNbr);
  void (*_moveBackwardCmd)(uint16_t stepNbr);
  void (*_onStopCmd)(void);
  void (*_onGoToZeroCmd)(void);

public:
  Controller();
  void notify(uint8_t *data, size_t size);
  // Callbacks
  void setOnDisconnectionCallback(void (*onDisconnection)(void));
  void setMoveForwardCmdCallback(void (*moveForwardCmd)(uint16_t stepNbr));
  void setMoveBackwardCmdCallback(void (*moveBackwardCmd)(uint16_t stepNbr));
  void setOnStopCmdCallback(void (*onStopCmd)(void));
  void setOnGoToZeroCallback(void (*onGoToZeroCmd)(void));

  class BLEServerCallbacksImpl : public BLEServerCallbacks
  {
  private:
    Controller *_controller;

  public:
    virtual void onConnect(BLEServer *pServer);
    virtual void onDisconnect(BLEServer *pServer);
    virtual void setController(Controller *controller);
  };

  class BLECharacteristicCallbacksImp : public BLECharacteristicCallbacks
  {
  private:
    Controller *_controller;

  public:
    virtual void onWrite(BLECharacteristic *pCharacteristic);
    virtual void setController(Controller *controller);
  };
};

#endif