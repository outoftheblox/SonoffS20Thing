# SonoffS20Thing
Alternative software for the Sonoff S20.

## Hardware
### Sonoff S20
Pinout 
- GND
- Tx
- Rx
- 3V3 (square)

GPIO pin numbers
-  0 Button
- 12 Relay and blue led
- 13 Green led

### Programmer
- USB A to micro cable
- USB micro power connector
- AMS1117 5v to 3v3 voltage regulator
- CH340G USB to TTL board

Connections
- Laptop USB - USB cable
- USB cable - board
- USB TTL board Tx - Board Tx
- USB TTL board Rx - Board Rx
- Board 3v3 - Sonoff 3v3
- Board GND - Sonoff GND
- Board Tx - Sonoff Rx
- Board Rx - Sonoff Tx

### Instructions
- Connect board to Sonoff
- Connect USB TTL to laptop
- Hold down Sonoff button
- Connect USB power cable to laptop
- Release Sonoff button
- run pio -t upload
