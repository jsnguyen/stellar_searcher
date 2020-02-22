![dis my logo](logos/stellar_searcher_logo_large.png?raw=true "stellar_searcher_logo")

# Stellar Searcher

The Stellar Searcher Project is an open source auto star tracker currently in development. The main purpose of this device is to make amateur stargazing easy by allowing people to search and find celestial objects with the aid of a small star tracking laser that points to an object in the sky, given the inputted equatorial coordinates of the object. The project uses 3D-printed parts and standard, easy-to-acquire electronics/materials. The project is written mainly in C for ease of compatibility with an arduino microcontroller.

The device itself will ultimately look like a small box that fits in a roughly 6in x 6in x 6in footprint with a small laser mounted on top of an alt-az motorized turret. Lasers are great stargazing tools because when shined in the night sky, laser light is scattered by the particles in the atmosphere producing a distinct laser beam. Even a small 5mW laser is strong enough to produce a beam that is very visible even in light polluted conditions.

## Organization
```src``` is where all of the source files are
```include/stellar_searcher``` is where all the header files are
```build``` is made from using ` make ` and removed using ` make clean `
```lib``` like build, lib is made and removed using ` make ` and ` make clean ` respectively
```examples``` folder is for showing examples of how a user might use the code
```tests``` folder is for testing specific functions, less user friendly

## Features
### In Progress
* CAD Model for the device
* Naked-eye object database
* Bluetooth connection between arduino and phone app
* Arduino code
* 3D spatial orientation
### Done
* Elemental classes
* Conversion between various stellar and terrestrial coordinate systems
	* Corrections for precession and nutation
	* Conversion between J2000 to JNow
	* Implementation of various timekeeping standards
* Coordinates for constellation tracing
* World Magnetic Model wrapper for getting the magnetic declination
* Rough bill of materials

## Compiling
Currently requires [jsmn](https://github.com/zserge/jsmn) and [SOFA](http://www.iausofa.org/current_C.html#Downloads). Make sure the ` jsmn ` folder is in the same directory as the ` stellar_searcher ` folder. These dependencies will be removed later.

To compile the library as is, simply run:

``` make ```

To compile the tests:

``` cd ./tests ```

``` make ```
## Bill of Materials
| Item | Price | 
| --- | --- |
| [NEMA 17 Bipolar Stepper Motor](https://www.amazon.com/Short-Bipolar-Motor-18-4oz-13Ncm/dp/B00PNEQ79Q/ref=sr_1_2?ie=UTF8&qid=1540856145&sr=8-2&keywords=short+body+stepper+motor) | $13.50 |
| [Low Voltage Stepper Motor Driver](https://www.pololu.com/product/2134*) | $5.95 | 
| [5mW Laser Diode](https://www.amazon.com/DTOL-Laser-Diode-Module-650nm/dp/B00R73MC1S/ref=sr_1_5?ie=UTF8&qid=1540856438&sr=8-5&keywords=laser+diode) | $5.48 |
| [ESP32 Microcontroller](https://www.amazon.com/HiLetgo-ESP-WROOM-32-Development-Microcontroller-Integrated/dp/B0718T232Z/ref=sr_1_1_sspa?keywords=arduino+bluetooth&qid=1563425500&s=gateway&sr=8-1-spons&psc=1*) | $26.79 |
| [9-DOF Sensor](https://www.adafruit.com/product/3463) | $14.95 |
| [18650 Batteries and Charger](https://www.amazon.com/Nitecore-D4-Rechargeable-EdisonBright-rechargeable/dp/B00RW3J8CE/ref=sr_1_14?ie=UTF8&qid=1540858083&sr=8-14&keywords=18650+battery+and+charger) | $34.99 |
| [18650 Battery Holder](https://www.amazon.com/Battery-Holder-1-Slot-Storage-4-Pack/dp/B07D1GLQBX/ref=sr_1_5?ie=UTF8&qid=1540858156&sr=8-5&keywords=18650+battery+holder) | $5.49 |
| Total | $126.60 |

## Reference
[1] Urban, S.E., & Seidelmann, P. K. (2013). *Explanatory supplement to the Astronomical almanac*. Mill Valley, CA: University Science Books.

