// https://os.mbed.com/users/amithy/code/DHT22/
#ifndef DHT22_H
#define DHT22_H
 
#include "mbed.h"
 
#define DHTLIB_OK                0
#define DHTLIB_ERROR_CHECKSUM   -1
#define DHTLIB_ERROR_TIMEOUT    -2
 
/** Class for the DHT22 sensor.
 * 
 * Example:
 * @code
 * #include "mbed.h"
 * #include "Dht22.h"
 *
 * Serial pc(USBTX, USBRX);
 * Dht22 sensor(PTD7);
 * 
 * int main() {
 *     sensor.read()
 *     pc.printf("T: %f, H: %d\r\n", sensor.getFahrenheit(), sensor.getHumidity());
 * }
 * @endcode
 */
class Dht22
{
public:
    /** Construct the sensor object.
     *
     * @param pin PinName for the sensor pin.
     */
    Dht22(PinName const &p);
    
    /** Update the humidity and temp from the sensor.
     *
     * @returns
     *   0 on success, otherwise error.
     */
    int read();
    
    /** Get the temp(f) from the saved object.
     *
     * @returns
     *   Fahrenheit float
     */
    float getFahrenheit();
    
    /** Get the temp(c) from the saved object.
     *
     * @returns
     *   Celsius int
     */
    float getCelsius();
    
    /** Get the humidity from the saved object.
     *
     * @returns
     *   Humidity percent int
     */
    float getHumidity();
 
private:
    /// percentage of humidity
    float _humidity;
    /// celsius
    float _temperature;
    /// pin to read the sensor info on
    DigitalInOut _pin;
    /// times startup (must settle for at least a second)
    Timer _timer;
};
 
#endif