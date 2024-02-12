
/*
  Fading effect using an EL Wire and AtTiny85 microcontroller

  Operation: This code is designed to control an EL wire such that it displays a fade in and fade out light effect. This is not possible using the original inverter EL wires typically come with.
  We use ATtiny85 microcontroller to perform the timing and the frequency of the ON/OFF pulse patterns generated for achieving the fading effect. Timing has been carefully measured via bench tests
  and has been optimized to provide the best visual experience.

  You can play with the values in pwm_levels[] array and its length as well as the LED_EFFECT_WAIT_TIME definition to experiment with different fading effects. Sky is the limit here!
  
  by circuitapps
  February 2024
*/
#include <avr/io.h>

// PORT B DEFINITIONS
#define PB5_PIN1 PB5
#define PB4_PIN3 PB4
#define PB3_PIN2 PB3
#define PB2_PIN7 PB2
#define PB1_PIN6 PB1
#define PB0_PIN5 PB0

// Application pin definitions
#define ELW_OUT_PIN PB2_PIN7

#define PWM_OUT_PIN PB1_PIN6
#define PWM_REGISTER OCR1A  // This is where the high duration (out of a max of 255) needs to be written

#define FADE_OUT 0
#define FADE_IN 1
#define LED_EFFECT_WAIT_TIME 175  // Every LED_EFFECT_WAIT_TIME ms a new LED light intensity will be observed


void timer_counter_1_pwm_setup()
{
  TCCR1 = 1<<PWM1A | 1<<COM1A0 | 1<<CS10;
  // OC1A is the output to pin 6 of Attiny85 (as per datasheet)
  pinMode(PWM_OUT_PIN, OUTPUT);  // pwm is programmed to be output here
}

// the setup function runs once when you press reset or power the board
void setup()
{
  timer_counter_1_pwm_setup();  // Sets PWM_OUT_PIN as PWM output
}

// the loop function runs over and over again forever
void loop()
{
  unsigned int count_state = FADE_IN;  // start with fade in effect
  //  Any maximum pwm_levels[] element can be 255. This determines the LED intensity level.
  unsigned int pwm_levels[] = {0,1,2,3,4,5,15,100,150,200,255};  // carefully selected through experimentation for best visual fading effect
  unsigned char current_level_idx = 0;

  unsigned int max_len = sizeof(pwm_levels) / sizeof(pwm_levels[0]);

  while(1)
  {
    PWM_REGISTER = pwm_levels[current_level_idx];
    delay(LED_EFFECT_WAIT_TIME);  // Wait time in ms before current LED light pattern is switched.

    if(count_state == FADE_IN)
    {// we are in FADE_IN phase
      if(current_level_idx == (max_len - 1))
      {// reached the FADE_IN limit
        count_state = FADE_OUT;  // time to switch to FADE_OUT state
        --current_level_idx;  // down one register value to kick off fade out next.
      }
      else
      {// FADE_IN limit not yet reached
        ++current_level_idx;  // up one register value for next fade in period.
      }
    }
    else
    {// we are in the FADE_OUT phase
      if(current_level_idx == 0)
      {// reached the FADE_OUT lower limit
        count_state = FADE_IN;  // time to switch to FADE_IN state
        ++current_level_idx;  // up one register value to kick off fade in next.
      }
      else
      {// FADE_OUT lower limit not yet reached
        --current_level_idx;  // down one register value for next fade out period.
      }
    }
  }

}
