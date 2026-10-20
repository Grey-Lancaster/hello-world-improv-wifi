# CLAUDE.md

hello-world-improv-wifi: a small ESP32 example that uses the Improv WiFi library to receive WiFi credentials over USB serial, blinks the onboard LED to show status, and then serves a basic web page with chip and network info. Public repo. `README.md` describes usage and the LED blink codes.

## Layout
- `platformio.ini` - one env, `esp32dev` (ESP32, Arduino, 115200 baud, `lib_ldf_mode=deep`). Library: `jnthas/Improv WiFi Library@^0.0.2`.
- `src/main.cpp` - the app: sets up `ImprovWiFi` on `Serial`, `blink_led()` for status, connects with the received credentials, then a raw `WiFiServer` on port 80 (`handleHttpRequest()`) serves the info page. `LED_BUILTIN` is forced to 2.
- `src/improv.cpp`, `src/improv.h` - a copy of the Improv serial protocol SDK (`improv::` namespace). `main.cpp` does not reference it (it uses `ImprovWiFiLibrary.h` from the library); I did not check whether it is needed.

## Build / flash
- `pio run` builds; `pio run -t upload` flashes; open the serial monitor at 115200. To send credentials use an Improv serial tool such as improv-wifi.com/serial (see README).
- I found no tests and no CI.

## Gotchas
- Per the README, if a web flasher reports "port fails to initialize", power the board off and retry.
- Credentials are supplied at runtime over Improv; the source holds none. Keep it that way.

## Deploy
- Push to `main`. There are no tags, releases or workflows.
