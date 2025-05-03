#ifndef GPIO_WRAPPER_H
#define GPIO_WRAPPER_H

#include "stm32f4xx_hal.h"

// C++ wrapper for STM32 GPIO using HAL drivers
class GPIOPin {
public:
    
		// Pin modes: input, output (push-pull), alternate function
    enum class Mode : uint32_t { In = GPIO_MODE_INPUT, Out = GPIO_MODE_OUTPUT_PP, Alt = GPIO_MODE_AF_PP };
    
		// Pull-up/pull-down configuration
    enum class Pull : uint32_t { Nop = GPIO_NOPULL, Up = GPIO_PULLUP, Down = GPIO_PULLDOWN };
    
		// Output speed levels
    enum class Speed : uint32_t 
		{
        Low = GPIO_SPEED_FREQ_LOW,
        Medium = GPIO_SPEED_FREQ_MEDIUM,
        High = GPIO_SPEED_FREQ_HIGH,
        VeryHigh = GPIO_SPEED_FREQ_VERY_HIGH
    };

    // Constructor 
    GPIOPin(GPIO_TypeDef* port, uint16_t pin) : _port(port), _pin(pin) {}

    // Initialize the pin with mode, pull configuration, speed, and optional alternate function
    void init(Mode mode, Pull pull = Pull::Nop, Speed speed = Speed::Low, uint8_t alternate = 0) {
        GPIO_InitTypeDef config{};
        config.Pin       = _pin;
        config.Mode      = static_cast<uint32_t>(mode);
        config.Pull      = static_cast<uint32_t>(pull);
        config.Speed     = static_cast<uint32_t>(speed);
        if (mode == Mode::Alt) {
            config.Alternate = alternate;
        }
        HAL_GPIO_Init(_port, &config);
    }

    // Write pin state: true = high, false = low
    void write(bool state) const {
        HAL_GPIO_WritePin(_port, _pin, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }

    // Toggle pin state
    void toggle() const {
        HAL_GPIO_TogglePin(_port, _pin);
    }

    // Read current pin state (true if high)
    bool read() const {
        return (HAL_GPIO_ReadPin(_port, _pin) == GPIO_PIN_SET);
    }

private:
    GPIO_TypeDef* _port;
    uint16_t      _pin;
};

#endif // GPIO_WRAPPER_H
