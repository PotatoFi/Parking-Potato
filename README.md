# Car-Parkinator
<p>Simple Arduino-based device that helps you park your car in the garage. It has a total range of 21 feet, is push-button configurable, and features 3 LED's:</p>
* Green, which just lets the driver know that the thing is working, I guess
* Yellow, which tells the driver they have ~12 inches until they need to stop
* Red, which tells the driver to stop now!

<h1>Configuration</h1>
<p>The device starts with a default "stop" distance of 24 inches. To configure a custom stop distance, park your car where you want it, and press the button. This will set a custom stop distance, and it will save it to the EEPROM, so the distance will persist after power failures.</p>
