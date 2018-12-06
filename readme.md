# Met de afstandsbediening LEDs bedienen

## Solderen

Voor dit kun je een [Arduino Pro mini ATMEGA328P 3.3V 8M](https://www.dennisdeal.com/products/10pcs-pro-mini-atmega328p-3-3v-8m-interactive-media-upgrade-version-for-arduino) gebruiken.

De LEDs kunnen met een weerstand van 100 Ohm aan de PWM pins worden gemaakt.
Rood op 9, groen op 10, blauw op 5, en geel op 6.
Maar je kan natuurlijk ook andere kleuren gebruiken

IR ontvanger CHQ1838 is aangesloten op pin 2

![Schema](https://github.com/pikoe/Arduino-IR-sensor-LEDs/blob/master/IR-receiver-LEDs.png?raw=true)

## Het programma op een Arduino Pro mini zetten

De Pro mini heeft zelf geen USB aansluiting om het programma er op te kunnen zetten.
Dit kan met een Arduino Uno, haal de microcontroller er voorzichtig uit zodat je niet deze schrijft maar de mini die je er op aan sluit.

![Schema](https://github.com/pikoe/Arduino-IR-sensor-LEDs/blob/master/programm%20arduion%20pro%20mini%20with%20uno.png?raw=true)

## Het programma zelf

Het eerste deel (state -1) is om een signaal van een afstandsbediening op te vangen, deze word onthouden.
Het volgende deel is dat de lampjes gaan branden. Er zijn meerdere opties waartussen gewisseld kan worden door dezelfde knop op de afstandsbediening te gebruiken als aan het begin.

+ Faden, de lampjes gaan om en om feller en minder fel branden
+ Alleen rood aan
+ Alleen groen aan
+ Alleen blauw aan
+ Alleen geel aan
+ Allemaal aan

