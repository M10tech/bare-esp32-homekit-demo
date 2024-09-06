# bare-esp32-homekit-demo

## history


### 0.0.3 make switch accessory without gpio
- the objective is to be as bare as possible, no gpio
- remember that in 0.0.2 we added PRIV_REQUIRES esp32-homekit
- still, after pairing and disconnect, it does not work more
- mdns might not be doing it's magic
- debug time, let's commit this step

### 0.0.2 setup components
- esp32-homekit as a git component
- wolfssl and mdns as managed components from inside esp32-homekit
- rest is idf supplied
- and basic user-settings.h for wolfssl to match homekit

### 0.0.1 hello world
- shows IP stack and printf functions
- uses LCM to define SSID and password => safe and flexible