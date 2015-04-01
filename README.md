# remoteVolume
An AVR-based IR controlled audio volume controller.
Primary purpose was to use active studio monitors with a TV without a fitting AV receiver.

# Features
* ATmega168 controller
* Volume controlling via <a href="http://www.ti.com/lit/ds/symlink/pga2311.pdf" target="_blank">TI PGA2311</a>
* Working with most IR protocols thanks to <a href="http://www.mikrocontroller.net/articles/IRMP" target="_blank">IRMP</a> library
* Two selectable input sources
* Switch output to control a subwoofer
* Display current volume by a ring of LEDs and a motorized pot.

#Caveats
* External power supply needed, for example <a href="http://www.meanwell.com/search/NET-35/NET-35-spec.pdf" target="_blank">Mean Well NET-35B</a>