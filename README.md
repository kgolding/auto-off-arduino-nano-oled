# Auto-off timer using Arduino Nano and 1.3" OLED display

I wanted to ensure a 3G Router was only on when it needed to be, and that it got switched off. This project is powered from the 3G Routers PSU, and has simple two button operation and a rich display with count down in the form of an OLED 1.3" module.

## Operation

Each press of the green button switches the router on for 30 minutes, up to a maximum of 5 hours.

The red button resets the timer to zero, and powers the 3G Router off after a further 8 seconds during which the green button can be used to cancel the switching off and reset/extend the timer by 30 mins.

