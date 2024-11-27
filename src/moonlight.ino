#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        1
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 3

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 100 // Time (in milliseconds) to pause between pixels

// Moon shades taken from https://www.nationalgeographic.com/science/article/photographer-marcella-giulia-pace-moon-colors
int mooncolors[48][3] = {
  {168, 101, 71},
  {130, 153, 175},
  {195, 203, 213},
  {147, 146, 150},
  {177, 173, 165},
  {191, 186, 175},
  {191, 164, 168},
  {181, 171, 170},
  {205, 198, 186},
  {191, 171, 141},
  {150, 141, 121},
  {163, 149, 124},
  {155, 141, 121},
  {138, 122, 100},
  {176, 142, 91},
  {169, 129, 82},
  {120, 85, 49},
  {139, 85, 50},
  {110, 72, 40},
  {69, 38, 15},
  {143, 27, 18},
  {203, 68, 34},
  {236, 96, 79},
  {238, 132, 50},
  {241, 166, 105},
  {214, 95, 58},
  {213, 100, 40},
  {153, 77, 48},
  {235, 154, 70},
  {242, 169, 89},
  {231, 187, 108},
  {213, 163, 98},
  {235, 199, 128},
  {223, 215, 149},
  {194, 168, 118},
  {214, 160, 105},
  {174, 126, 93},
  {205, 155, 109},
  {246, 203, 153},
  {236, 186, 154},
  {217, 189, 167},
  {159, 123, 115},
  {168, 118, 112},
  {143, 87, 76},
  {122, 71, 61},
  {81, 56, 59},
  {195, 136, 194},
  {147, 112, 125},
};

int currentR;
int currentG;
int currentB;

int targetR;
int targetG;
int targetB;

bool transitioning;
const int transitioningSteps = 1;

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  currentR = 100;
  currentG = 0;
  currentB = 0;

  targetR = 0;
  targetG = 0;
  targetB = 100;

  transitioning = false;
}


void loop() {
  pixels.clear(); // Set all pixel colors to 'off'

  if (!transitioning) {
    transitioning = true;

    int randomShade = random(0, 47);

    targetR = mooncolors[randomShade][0];
    targetG = mooncolors[randomShade][1];
    targetB = mooncolors[randomShade][2];
  }

  currentR = calculateNextValue(currentR, targetR);
  currentG = calculateNextValue(currentG, targetG);
  currentB = calculateNextValue(currentB, targetB);

  for (int i = 0; i < NUMPIXELS; i ++) {
    pixels.setPixelColor(i, pixels.Color(currentR, currentG, currentB));
  }
  pixels.show();   // Send the updated pixel colors to the hardware.
  delay(DELAYVAL); // Pause before next pass through loop

  if (currentR == targetR && currentG == targetG && currentB == targetB) {
    transitioning = false;
    delay(5000);
  }
}

int calculateNextValue(int currentVal, int targetVal) {
  int nextVal = targetVal;

  if (currentVal <= targetVal) {
    nextVal = currentVal + transitioningSteps;
    if (nextVal > targetVal) {
      nextVal = targetVal;
    }
  } else {
    nextVal = currentVal - transitioningSteps;
    if (nextVal < 0) {
      nextVal = 0;
    }
  }

  return nextVal;
}