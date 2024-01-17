
/*
  Fading effect using an EL Wire and a microcontroller

  Operation: This code is designed to control an EL wire such that it displays a fade in and fade out light effect. This is not possible using the original inverter EL wires typically come with.
  We use ATtiny85 microcontroller to perform the timing and the frequency of the ON/OFF pulse patterns generated for achieving the fading effect. Timing has been carefully measured via bench tests
  and has been optimized to provide the best visual experience.
  
  by circuitapps
  January 2024
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

#define LOOP_1_LIMIT 100

void turn_on(unsigned int pin_name)
{
  digitalWrite(pin_name, HIGH);
}

void turn_off(unsigned int pin_name)
{
  digitalWrite(pin_name, LOW);
}

void wait_ms(unsigned int delay_ms)
{
  delay(delay_ms);
}

// EL WIRE ILLUMINATION PATTERN 1:
void (*pattern_1_funcs[])(unsigned int) = {&turn_on,          &wait_ms,    &turn_off,   &wait_ms};
//unsigned int pattern_1_func_args[] =      {ELW_OUT_PIN,       10,         ELW_OUT_PIN,  10};

unsigned int *pattern_1_func_args[] = {
                                          (unsigned int[]){ELW_OUT_PIN,       20,         ELW_OUT_PIN,  20},
                                          (unsigned int[]){ELW_OUT_PIN,       30,         ELW_OUT_PIN,  30},
                                          (unsigned int[]){ELW_OUT_PIN,       35,         ELW_OUT_PIN,  35},
                                          (unsigned int[]){ELW_OUT_PIN,       40,         ELW_OUT_PIN,  40},
                                          (unsigned int[]){ELW_OUT_PIN,       45,         ELW_OUT_PIN,  45},
                                          (unsigned int[]){ELW_OUT_PIN,       50,         ELW_OUT_PIN,  50},
                                          (unsigned int[]){ELW_OUT_PIN,       70,         ELW_OUT_PIN,  70}
                                        };

  int number_of_loops[] = {25, 17, 15, 13, 11, 10, 7};  // NEEDS TO HAVE THE SAME NUMBER OF ELEMENTS AS THE NUMBER OF ROWS IN *pattern_1_func_args[]

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(ELW_OUT_PIN, OUTPUT);

  digitalWrite(ELW_OUT_PIN, LOW);
}

// the loop function runs over and over again forever

void loop() {

  int i, loop_idx, arg_row;
  int num_pattern_1_elements = sizeof(pattern_1_funcs) / sizeof(pattern_1_funcs[0]);
  int num_arg_rows = sizeof(pattern_1_func_args) / sizeof(pattern_1_func_args[0]);

  // SCAN FORWARD
  for( arg_row = 0; arg_row < num_arg_rows; ++arg_row )
  {
    for(loop_idx = 0 ; loop_idx < number_of_loops[arg_row]; ++loop_idx)
    {
      for(i = 0 ; i < num_pattern_1_elements; ++i)
      {// Cycling through each pattern defined by the user.
        pattern_1_funcs[i](pattern_1_func_args[arg_row][i]);  // calling the function via function pointers and the specified function argument.
      }

    }// end loop_idx
  }// end arg_row

  // SCAN BACKWARD
  for( arg_row = num_arg_rows - 1; arg_row >=0 ; --arg_row )
  {
    for(loop_idx = 0 ; loop_idx < number_of_loops[arg_row]; ++loop_idx)
    {
      for(i = 0 ; i < num_pattern_1_elements; ++i)
      {// Cycling through each pattern defined by the user.
        pattern_1_funcs[i](pattern_1_func_args[arg_row][i]);  // calling the function via function pointers and the specified function argument.
      }

    }// end loop_idx
  }// end arg_row

}
