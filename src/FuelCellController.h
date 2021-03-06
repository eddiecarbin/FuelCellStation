
#ifndef FUELCELLCONTROLLER_H_
#define FUELCELLCONTROLLER_H_
#include <Arduino.h>
#include "FastLED.h" // FastLED library. Preferably the latest copy of FastLED 2.1.
#include <FastLED.h> // for short list
#include <JC_Button.h>
#include "PanelLightController.h"
// #include "../lib/TweenDuino/TweenDuino.h"

enum FuelCellState
{
    NONE,
    EMPTY,
    FILLING,
    FULL
};

class FuelCellController
{
public:
    FuelCellController(int id, int cells, int leds);
    FuelCellState getState(void);
    void initialize(struct CRGB *data, Button *lever, PanelLightController *p);
    void update(void);
    void drawColor(CRGB color);
    virtual ~FuelCellController();

private:
    int totalCells;
    int cellCount;
    int id;
    FuelCellState currentState;
    CRGB *_leds;
    Button *lever;
    unsigned long pause;
    int totalLeds;
    int prevpos;
    int index;
    PanelLightController *panel;
    void plasma(void);
    void test(void);
    void sinlon(const struct CRGB &color);
    void sawtooth(void);
    uint32_t timebase;
    CRGBPalette16 currentPalette; // Palette definitions
    // CRGBPalette16 targetPalette;
};

#endif /* FUELCELLCONTROLLER_H_ */