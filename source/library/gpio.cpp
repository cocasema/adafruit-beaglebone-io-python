/*
Copyright (c) 2017 Adafruit
Copyright (c) 2017 Nikolay Semenov

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "adafruit/bbio/gpio.h"

#include "adafruit/bbio/error.h"

extern "C" {
#include "common.h"
#include "c_pinmux.h"
#include "event_gpio.h"
}

namespace adafruit {
namespace bbio {

/*
 * Gpio
 */
Gpio::Gpio(std::string const& key, Direction direction)
    : key_(key)
    , pin_(0)
{
    (CheckError)get_gpio_number(key_.c_str(), &pin_);
    /*(CheckError)*/gpio_export(pin_);

    timespec ts[] = {{0, 1 * 1000000}};
    nanosleep(ts, NULL);

    if (direction == Direction::Input) {
        (CheckError)set_pin_mode(key_.c_str(), "gpio");
    }
}

Gpio::~Gpio()
{
    if (pin_) {
        gpio_unexport(pin_);
    }
}

void Gpio::set_direction(Direction direction)
{
    (CheckError)gpio_set_direction(pin_, (uint32_t)direction);
}

void Gpio::set_value(Value value)
{
    (CheckError)gpio_set_value(pin_, (uint32_t)value);
}

} // namespace bbio
} // namespace adafruit
