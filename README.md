# 24013 - FADING CONTROL FOR EL WIRES
---

In this video we are introducing a simple method that will allow you to create fade in and fade out light effects using any EL wire! This project uses the legendary AtTiny85 microcontroller to achieve this.

Following is the circuit diagram of the fading controller.

![fading controller circuit diagram](./EL_wire_fader_circuit.png)

You can access the AtTiny85 software code using the following link.

![AtTiny85 code folder](./attiny85_code_24013)

Though the above code showcases one fading pattern shown in our **<u>[project video][1]</u>**, there are many more fading patterns you can create simply by modifying the source code.

If you build this project, please share your thoughts and suggestions with the rest of circuitapps community in the comments section of **<u>[our YouTube video][1]</u>**. Also, please feel free to talk about any interesting modifications you make and your experimentations, if any !

## Project Challenges
There are a few things to be careful with while building this project to make sure you get it working after the first attempt

### **Caution 1 - The shrink fit installation**

You need to use a 1 inch shrink fit with an LED on one aend and a photo resistor on the other. Be sure to only shrink the ends and not the middle part of this shrink fit since the light from the LED needs to reach the photoresistor to achieve the EL wire fading effect!

### **Caution 2 - Power supply voltage**

Though we are using a modified inverter we built in **<u>[this guide video][2]</u>**, you can power the AtTiny85 using alternative DC power sources. Just make sure the ground of the EL wire inverter and the power supply are connected it that's what you are planning to do.

## Useful tips

### **Tip 1:**
If you have not worked with ATtiny85 before and need support with the basic operation and programming of this device, have a look at this **<u>[excellent reference][3]</u>** that walks you through the entire process step by step. If you get stuck, drop us a message in the comments section of **<u>[our YouTube video][1]</u>**


GOOD LUCK & ENJOY EXPERIMENTING WITH YOUR FEDING EL WIRES !


[1]: https://youtube.com/shorts/IckCkDhcclc

[2]: https://youtu.be/yBwCZ95K7WI

[3]: https://circuitdigest.com/microcontroller-projects/programming-attiny85-microcontroller-ic-using-arduin