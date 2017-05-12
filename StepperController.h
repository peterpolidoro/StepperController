// ----------------------------------------------------------------------------
// StepperController.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef STEPPER_CONTROLLER_H
#define STEPPER_CONTROLLER_H
#include "Flash.h"
#include <EEPROM.h>
#include "Streaming.h"
#include "ArduinoJson.h"
#include "JsonSanitizer.h"
#include "JsonStream.h"
#include "Array.h"
#include "Vector.h"
#include "MemoryFree.h"
#include "ConstantVariable.h"
#include "SavedVariable.h"
#include "Functor.h"
#include "IndexedContainer.h"
#include "FunctorCallbacks.h"

#include "SPI.h"
#include "TMC429.h"
#include "TMC26X.h"

#include "ModularClient.h"

#include "ModularServer.h"
#include "ModularDeviceBase.h"
#include "StepDirController.h"

#include "utility/Constants.h"


class StepperController : public StepDirController
{
public:
  StepperController();
  virtual void setup();

  virtual void reinitialize();

  void minimizeCurrent(const size_t channel);
  void restoreCurrent(const size_t channel);

protected:
  virtual double stepsToPositionUnits(const size_t channel, const double steps);
  virtual double positionUnitsToSteps(const size_t channel, const double position_units);

private:
  modular_server::Property properties_[stepper_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[stepper_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[stepper_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[stepper_controller::constants::CALLBACK_COUNT_MAX];

  typedef TMC26X Driver;
  Driver drivers_[stepper_controller::constants::DRIVER_COUNT];

  // Handlers
  void setCurrentScaleHandler(const size_t channel);
  void preSetMicrostepsPerStepHandler(const size_t channel);
  void postSetMicrostepsPerStepHandler(const size_t channel);
  void setMicrostepsPerStepHandler(const size_t channel);
  void minimizeCurrentHandler();
  void restoreCurrentHandler();

};

#endif
