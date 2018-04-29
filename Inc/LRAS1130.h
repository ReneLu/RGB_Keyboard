//
// Lucky Resistor's AS1130 Library
// ---------------------------------------------------------------------------
// (c)2017 by Lucky Resistor. See LICENSE for details.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>
//
#pragma once

#ifdef ARDUINO_ARCH_AVR
#include <inttypes.h>
#else
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#endif


/// @brief A low-level AS1130 chip access class.
///
/// You have to initialize the chip in the order shown below.
///
/// 1. Set the RAM configuration using setRamConfiguration().
/// 2. Set the On/Off frames with your data using setOnOffFrame24x5() and similar functions.
/// 3. Set the Blink&PWM sets with your data using setBlinkAndPwmSetAll() and similar functions.
/// 4. Set the dot correction data (if required).
/// 5. Set control registers for interrupt masks, interface and clock synchronization.
/// 6. Set the current source level using setCurrentSource().
/// 7. Set the display options like picture/movie etc, using e.g. setMovieFrameCount() and similar.
/// 8. Start displaying a picture or movie using startPicture() or startMovie().
/// 9. Enable the chip using startChip().
///
/// After this you can use most function to change the settings, but you can not change the
/// RAM configuration without resetting the chip first.
///



/// @brief The chip address.
///
typedef enum _ChipAddress {
ChipBaseAddress = 0b0110000, ///< The base address for all chips.
ChipAddress0 = ChipBaseAddress+0x0, ///< The (A and B) chip address with 1Mohn resistor or floating address pin.
ChipAddress1 = ChipBaseAddress+0x1, ///< The (A and B) chip address with 470kohm resistor on the address pin.
ChipAddress2 = ChipBaseAddress+0x2, ///< The (A and B) chip address with 220kohm resistor on the address pin.
ChipAddress3 = ChipBaseAddress+0x3, ///< The (A and B) chip address with 100kohm resistor on the address pin.
ChipAddress4 = ChipBaseAddress+0x4, ///< The (A and B) chip address with 47kohm resistor on the address pin.
ChipAddress5 = ChipBaseAddress+0x5, ///< The (A and B) chip address with 22kohm resistor on the address pin.
ChipAddress6 = ChipBaseAddress+0x6, ///< The (A and B) chip address with 10kohm resistor on the address pin.
ChipAddress7 = ChipBaseAddress+0x7, ///< The (A and B) chip address with 4.7kohm resistor or ground on the address pin.
ChipAddress8 = ChipBaseAddress+0x8, ///< The (C and D) chip address with 1Mohn resistor or floating address pin.
ChipAddress9 = ChipBaseAddress+0x9, ///< The (C and D) chip address with 470kohm resistor on the address pin.
ChipAddressA = ChipBaseAddress+0xa, ///< The (C and D) chip address with 220kohm resistor on the address pin.
ChipAddressB = ChipBaseAddress+0xb, ///< The (C and D) chip address with 100kohm resistor on the address pin.
ChipAddressC = ChipBaseAddress+0xc, ///< The (C and D) chip address with 47kohm resistor on the address pin.
ChipAddressD = ChipBaseAddress+0xd, ///< The (C and D) chip address with 22kohm resistor on the address pin.
ChipAddressE = ChipBaseAddress+0xe, ///< The (C and D) chip address with 10kohm resistor on the address pin.
ChipAddressF = ChipBaseAddress+0xf, ///< The (C and D) chip address with 4.7kohm resistor or ground on the address pin.
} ChipAddress;

/// @brief The RAM configuration.
///
typedef enum _RamConfiguration{
RamConfiguration1 = 1, ///< Configuration with 1 blink/PWM sets, 36 on/off frames and 35 on/off frames with dot correction.
RamConfiguration2 = 2, ///< Configuration with 2 blink/PWM sets, 30 on/off frames and 29 on/off frames with dot correction.
RamConfiguration3 = 3, ///< Configuration with 3 blink/PWM sets, 24 on/off frames and 23 on/off frames with dot correction.
RamConfiguration4 = 4, ///< Configuration with 4 blink/PWM sets, 18 on/off frames and 17 on/off frames with dot correction.
RamConfiguration5 = 5, ///< Configuration with 5 blink/PWM sets, 12 on/off frames and 11 on/off frames with dot correction.
RamConfiguration6 = 6, ///< Configuration with 6 blink/PWM sets, 6 on/off frames and 5 on/off frames with dot correction.
} RamConfiguration;

/// @brief The interrupt mask flags
///
typedef enum _InterruptMaskFlag {
IMF_MovieFinished   = 0b00000001, ///< Flag set if the movie has finished playing.
IMF_ShortTestError  = 0b00000010, ///< Flag set if there is a short while testing the LEDs.
IMF_OpenTestError   = 0b00000100, ///< Flag set if there is an open LED connection.
IMF_LowVdd          = 0b00001000, ///< Flag set if the VDD is too low for the LEDs.
IMF_OverTemperature = 0b00010000, ///< Flag set if the chip has over temperature.
IMF_POR             = 0b00100000, ///< Flag set if there is a POR (power on reset).
IMF_WatchDog        = 0b01000000, ///< Flag set if there is a time-out in the interface.
IMF_SelectedPicture = 0b10000000, ///< Flag set if the selected picture is reached.
} InterruptMaskFlag;

/// @brief The synchronization mode.
///
typedef enum _Synchronization {
SynchronizationOff      = 0b00, ///< Turn synchronization off.
SynchronizationIn       = 0b01, ///< Use the synchonization pin for the ineternal clock.
SynchronizationOut      = 0b10, ///< Send the internal clock to the synchronization pin.
} Synchronization;

/// @brief The clock frequency.
///
typedef enum _ClockFrequency {
Clock1MHz   = 0b0000, ///< Use 1 MHz as internal clock.
Clock500kHz = 0b0100, ///< Use 500 kHz as internal clock.
Clock125kHz = 0b1000, ///< Use 125 kHz as internal clock.
Clock32kHz  = 0b1100  ///< Use 32 kHz as internal clock.
} ClockFrequency;

/// @brief The current for the LEDs.
///
typedef enum _Current {
Current0mA  = 0x00, ///< Disable the current source for the LEDs.
Current5mA  = 0x2b, ///< Use 5mA as current source for the LEDs.
Current10mA = 0x55, ///< Use 10mA as current source for the LEDs.
Current15mA = 0x80, ///< Use 15mA as current source for the LEDs.
Current20mA = 0xaa, ///< Use 20mA as current source for the LEDs.
Current25mA = 0xd5, ///< Use 25mA as current source for the LEDs.
Current30mA = 0xff ///< Use 30mA as current source for the LEDs.
} Current;

/// @brief The scan limit.
///
typedef enum _ScanLimit {
ScanLimit1 = 0x0, ///< Set 1 section as scan limit.
ScanLimit2 = 0x1, ///< Set 2 sections as scan limit.
ScanLimit3 = 0x2, ///< Set 3 sections as scan limit.
ScanLimit4 = 0x3, ///< Set 4 sections as scan limit.
ScanLimit5 = 0x4, ///< Set 5 sections as scan limit.
ScanLimit6 = 0x5, ///< Set 6 sections as scan limit.
ScanLimit7 = 0x6, ///< Set 7 sections as scan limit.
ScanLimit8 = 0x7, ///< Set 8 sections as scan limit.
ScanLimit9 = 0x8, ///< Set 9 sections as scan limit.
ScanLimit10 = 0x9, ///< Set 10 sections as scan limit.
ScanLimit11 = 0xa, ///< Set 11 sections as scan limit.
ScanLimit12 = 0xb, ///< Set 12 sections as scan limit.
ScanLimitFull = ScanLimit12, ///< Set all sections as scan limit.
} ScanLimit;

/// @brief The movie end frame
///
typedef enum _MovieEndFrame {
MovieEndWithFirstFrame, ///< The movie ends with the first frame.
MovieEndWithLastFrame ///< The movie ends with the last frame.
} MovieEndFrame;

/// @brief The scrolling block size.
///
typedef enum _ScrollingBlockSize {
ScrollInFullMatrix, ///< Scroll in full 12x11 matrix mode.
ScrollIn5LedBlocks ///< Scroll in the 24x5 matrix mode.
} ScrollingBlockSize;

/// @brief The scrolling direction.
///
typedef enum _ScrollingDirection {
ScrollingLeft, ///< Scroll to the left.
ScrollingRight ///< Scroll to the right.
} ScrollingDirection;

/// @brief The blink frequency.
///
typedef enum _BlinkFrequency {
BlinkFrequency1_5s, ///< Set the blink frequency to 1.5s
BlinkFrequency3s ///< Set the blink frequency to 3s
} BlinkFrequency;

/// @brief The movie loop count.
///
typedef enum _MovieLoopCount {
MovieLoopInvalid   = 0b00000000, ///< Invalid movie loop value (this is the default after reset).
MovieLoop1         = 0b00100000, ///< Loop the movie once.
MovieLoop2         = 0b01000000, ///< Loop the movie twice.
MovieLoop3         = 0b01100000, ///< Loop the movie 3 times.
MovieLoop4         = 0b10000000, ///< Loop the movie 4 times.
MovieLoop5         = 0b10100000, ///< Loop the movie 5 times.
MovieLoop6         = 0b11000000, ///< Loop the movie 6 times.
MovieLoopEndless   = 0b11100000, ///< Loop the movie endless.
} MovieLoopCount;

/// @brief The status of a LED.
///
typedef enum _LedStatus {
LedStatusOk, ///< The LED is ok and working.
LedStatusOpen, ///< The LED is not connected.
LedStatusDisabled ///< The LED is disabled in the driver.
} LedStatus;

/// @name Low-Level Definitions.
/// Definitions used for low-level operations.
/// @{

/// @brief The register selection (base) value.
///
typedef enum _RegisterSelection {
RS_NOP = 0x00,
RS_OnOffFrame = 0x01,
RS_BlinkAndPwmSet = 0x40,
RS_DotCorrection = 0x80,
RS_Control = 0xc0
} RegisterSelection;

/// @brief The control register address.
///
typedef enum _ControlRegister {
CR_Picture = 0x00,
CR_Movie = 0x01,
CR_MovieMode = 0x02,
CR_FrameTimeScroll = 0x03,
CR_DisplayOption = 0x04,
CR_CurrentSource = 0x05,
CR_Config = 0x06,
CR_InterruptMask = 0x07,
CR_InterruptFrameDefinition = 0x08,
CR_ShutdownAndOpenShort = 0x09,
CR_InterfaceMonitoring = 0x0a,
CR_ClockSynchronization = 0x0b,
CR_InterruptStatus = 0x0e,
CR_Status = 0x0f,
CR_OpenLedBase = 0x20
} ControlRegister;

/// @brief The flags and masks for the picture register.
///
typedef enum _PictureFlag {
PF_PictureAddressMask = 0b00111111,
PF_DisplayPicture     = 0b01000000,
PF_BlinkPicture       = 0b10000000,
} PictureFlag;

/// @brief The flags and masks for the movie register.
///
typedef enum _MovieFlag {
MF_MovieAddressMask   = 0b00111111,
MF_DisplayMovie       = 0b01000000,
MF_BlinkMovie         = 0b10000000,
} MovieFlag;

/// @brief The flags and masks for the movie mode register.
///
typedef enum _MovieModeFlag {
MMF_MovieFramesMask   = 0b00111111,
MMF_EndLast           = 0b01000000,
MMF_BlinkEnabled      = 0b10000000,
} MovieModeFlag;

/// @brief The flags and masks for the frame time/scroll register.
///
typedef enum _FrameTimeScrollFlag {
FTSF_FrameDelay       = 0b00001111,
FTSF_EnableScrolling  = 0b00010000,
FTSF_BlockSize        = 0b00100000,
FTSF_ScrollDirection  = 0b01000000,
FTSF_FrameFade        = 0b10000000,
} FrameTimeScrollFlag;

/// @brief The flags and masks for the display option register.
///
typedef enum _DisplayOptionFlag {
DOF_ScanLimitMask     = 0b00001111,
DOF_BlinkFrequency    = 0b00010000,
DOF_LoopsMask         = 0b11100000,
} DisplayOptionFlag;

/// @brief The flags and masks for the config register.
///
typedef enum _ConfigFlag {
CF_MemoryConfigMask   = 0b00000111,
CF_CommonAddress      = 0b00001000,
CF_DotCorrection      = 0b00010000,
CF_LedErrorCorrection = 0b00100000,
CF_LowVddStatus       = 0b01000000,
CF_LowVddReset        = 0b10000000,
} ConfigFlag;

/// @brief Flags/masks for the shutdown & open/short register
///
typedef enum _ShutdownAndOpenShortFlag {
SOSF_Shutdown   = 0b00000001,
SOSF_Initialize = 0b00000010,
SOSF_ManualTest = 0b00000100,
SOSF_AutoTest   = 0b00001000,
SOSF_TestAll    = 0b00010000,
} ShutdownAndOpenShortFlag;

/// @brief Flags/masks for the status register
///
typedef enum _StatusFlag {
SF_TestOn       = 0b00000001,
SF_MovieOn      = 0b00000010,
SF_FrameOnMask  = 0b11111100,
} StatusFlag;

/// @}

// High-level functions.
/// @brief Check the chip communication.
///
/// This function checks if the chip aknowledges a command on the I2C bus.
/// If it does, this function returns `true`, otherwise it returns `false`.
///
/// @return `true` if the chip answers, `false` if there is no answer.
///
bool AS1130_isChipConnected();

/// @brief Set the RAM configuration.
///
/// The RAM configuration defines how many On/Off frames and PWM/blink sets are available.
/// This numbers are not checked if you define frames later, you have to make sure you
/// only use the maximum number of frames and sets as possible for your choosen configuration.
///
/// You can not change the configuration as soon as you wrote the first frame without resetting
/// the chip.
///
/// Ram Configuration | Blink & PWM Sets | On/Off Frames | On/Off Frames with Dot Connection
/// ------------------|------------------|---------------|----------------------------------
/// 1                 | 1                | 36            | 35
/// 2                 | 2                | 30            | 29
/// 3                 | 3                | 24            | 23
/// 4                 | 4                | 18            | 17
/// 5                 | 5                | 12            | 11
/// 6                 | 6                | 6             | 5
///
/// @param ramConfiguration The RAM configuration.
///
void AS1130_setRamConfiguration(RamConfiguration ramConfiguration);

/// @brief Set-up a on/off frame.
///
/// @param frameIndex The index of the frame. This has to be a value between 0 and 35. Depending
///   on your RAM configuration this can be less. The frame number is not checked to be
///   valid. See the RAM configuration for details.
/// @param pwmSetIndex The PWM set index for this frame. It has to be a value between 0 and 7
///   selecting one of the PWM sets.
/// @param picture The picture to write into the frame.
///

void AS1130_setOnOffFrame(uint8_t frameIndex, uint8_t *picture, uint8_t pwmSetIndex); // default pwmSetIndex = 0

/// @brief Set-up a on/off frame with all LEDs disabled.
///
/// @param frameIndex The index of the frame. This has to be a value between 0 and 35.
/// @param pwmSetIndex The PWM set index for this frame. It has to a value between 0 and 7
///   selecting one of the PWM sets.
///
void AS1130_setOnOffFrameAllOff(uint8_t frameIndex, uint8_t pwmSetIndex);

/// @brief Set-up a on/off frame with all LEDs enabled.
///
/// @param frameIndex The index of the frame. This has to be a value between 0 and 35.
/// @param pwmSetIndex The PWM set index for this frame. It has to a value between 0 and 7
///   selecting one of the PWM sets.
///
void AS1130_setOnOffFrameAllOn(uint8_t frameIndex, uint8_t pwmSetIndex);

/// @brief Set-up a blink&PWM set with values for all LEDs.
///
/// This will set the given blink&PWM set and set all LEDs to the given values.
///
/// @param setIndex The set index has to be a value between 0 and 5.
/// @param doesBlink If the LEDs in the set are set to blink or not.
/// @param pwmValue The PWM value for all LEDs.
///

void AS1130_setBlinkAndPwmSetAll(uint8_t setIndex, bool doesBlink, uint8_t pwmValue);

/// @brief Set a PWM value in a given blink&PWM set.
///
/// @param setIndex The set index has to be a value between 0 and 5.
/// @param ledIndex The index of the LED. A value between 0x00 and 0xba.
/// @param value The PWM value between 0x00 and 0xff.
///
void AS1130_setPwmValue(uint8_t setIndex, uint8_t ledIndex, uint8_t value);

/// @brief Set the dot correction data.
///
/// This correction data is a correction factor for all 12 segments of the display.
/// You have to pass an array with 12 byte values.
///
/// @param data Pointer to an array with 12 bytes.
///
void AS1130_setDotCorrection(uint8_t *data);

/// @brief Set the interrupt mask.
///
/// @param mask A mask with a OR combination of the flags from enum InterruptMaskFlag.
///
void AS1130_setInterruptMask(uint8_t mask);

/// @brief Set the interrupt frame.
///
/// @param lastFrame The index of the frame which triggers the inetrrupt. A value between 0 and 35.
///
void AS1130_setInterruptFrame(uint8_t lastFrame);

/// @brief Set the I2C monitoring.
///
/// This sets the values for the interface monitoring.
///
/// @param timeout The timeout value between 0x00 and 0x3f. The resulting timeout is calculated
///   with the following formula: timeout window = (value + 1) * 256 microseconds.
/// @param enabled If set to true, the monitoring is enabled. If set to false, the monitoring is disabled.
///
void AS1130_setInterfaceMonitoring(uint8_t timeout, bool enabled);

/// @brief Set the clock synchronization.
///
/// @param synchronization The synchronization mode.
/// @param clockFrequency The clock frequency.
///
void AS1130_setClockSynchronization(Synchronization synchronization, ClockFrequency clockFrequency);

/// @brief Set the current source.
///
/// This is the current source for all LEDs. It is not the actual current for each LED because of
/// the multiplexing. See the datasheet, section "LED Current Calculation" for an exact calculation
/// of the resulting current for each LED.
///
/// @param current The current source for all LEDs.
///
void AS1130_setCurrentSource(Current current);

/// @brief Set the scan limit.
///
/// @param scanLimit The scan limit. This is the number of sections which are included in
///   the displayed image or movie.
///
void AS1130_setScanLimit(ScanLimit scanLimit);

/// @brief Set if blinking is enabled or not for all modes.
///
/// If you disable blinking using this flag, all blinking is disabled. It will ignore
/// any bits set in the blink sets and the blink flags in the picture and movie modes.
///
/// @param enabled True if the blinking is enabled, false if all blinking is disabled.
///
void AS1130_setBlinkEnabled(bool enabled);

/// @brief Start displaying a picture
///
/// @param frameIndex The index of the frame to display.
/// @param blinkAll If all LEDs should blink while the picture is displayed.
///
void AS1130_startPicture(uint8_t frameIndex, bool blinkAll);

/// @brief Stop displaying a picture.
///
void AS1130_stopPicture();

/// @brief Sets at which frame the movie ends.
///
/// @param movieEndFrame The frame where the movie ends.
///
void AS1130_setMovieEndFrame(MovieEndFrame movieEndFrame);

/// @brief Set the number of movie frames to play.
///
/// @param count The number of movie frames to play. Minimum is 2, maximum is 36.
///   This value is converted into the register format.
///
void AS1130_setMovieFrameCount(uint8_t count);

/// @brief Set the frame delay.
///
/// @param delayMs The frame delay in milliseconds. This value has to be between
///   zero and 488 milliseconds. The final value is changed to the next lower matching
///   value. See the datasheet for the final values.
///
void AS1130_setFrameDelayMs(uint16_t delayMs);

/// @brief Set scrolling enabled or disabled.
///
/// @param enable True if the scrolling is enabled. False to disable the scrolling.
///
void AS1130_setScrollingEnabled(bool enable);

/// @brief Set the block size for scrolling.
///
/// @param scrollingBlockSize If the scrolling uses the full matrix or the 5 LED block mode.
///
void AS1130_setScrollingBlockSize(ScrollingBlockSize scrollingBlockSize);

/// @brief Set the scroll direction.
///
/// @param scrollingDirection The direction for the scrolling.
///
void AS1130_setScrollingDirection(ScrollingDirection scrollingDirection);

/// @brief Enable or disable frame fading.
///
/// @param enable True to enable the frame fading. False to disable frame fading.
///
void AS1130_setFrameFadingEnabled(bool enable);

/// @brief Change the blink frequency.
///
/// @param blinkFrequency The frequency for blinking LEDs.
///
void AS1130_setBlinkFrequency(BlinkFrequency blinkFrequency);

/// @brief Set the loop count for the movie.
///
/// @param movieLoopCount The number of loops while playing a movie.
///
void AS1130_setMovieLoopCount(MovieLoopCount movieLoopCount);

/// @brief Start displaying a movie
///
/// @param firstFrameIndex The first frame of the movie to start with.
/// @param blinkAll If all LEDs should blink while the movie is displayed.
///
void AS1130_startMovie(uint8_t firstFrameIndex, bool blinkAll);

/// @brief Stop displaying a movie
///
void AS1130_stopMovie();

/// @brief Enable or disable low VDD reset.
///
/// @param enabled True to enable this feature, false to disable it.
///
void AS1130_setLowVddResetEnabled(bool enabled);

/// @brief Enable or diable low VDD status.
///
/// @param enabled True to enable this feature, false to disable it.
///
void AS1130_setLowVddStatusEnabled(bool enabled);

/// @brief Enable or disable LED error correction.
///
/// @param enabled True to enable this feature, false to disable it.
///
void AS1130_setLedErrorCorrectionEnabled(bool enabled);

/// @brief Enable or disable analog current dot correction.
///
/// @param enabled True to enable this feature, false to disable it.
///
void AS1130_setDotCorrectionEnabled(bool enabled);

/// @brief Enable test on all LED locations.
///
/// @param enabled True to enable this feature, false to disable it.
///
void AS1130_setTestAllLedsEnabled(bool enabled);

/// @brief Enable the automatic LED test.
///
/// This enables an automatic LED test as soon a movie or picture is displayed.
///
/// @param enabled True to enable this feature, false to disable it.
///
void AS1130_setAutomaticTestEnabled(bool enabled);

/// @brief Start the chip.
///
/// This starts the internal state machine and enabled power for the LEDs.
///
void AS1130_startChip();

/// @brief Stop the chip.
///
/// This puts the chip in shutdown mode and stops the state machine.
///
void AS1130_stopChip();

/// @brief Reset the chip.
///
/// This will reset the chip using the initialize flag.
///
void AS1130_resetChip();

/// @brief Start a manual LED test.
///
/// This starts a manual LED test and waits until this test finishes. After
/// running this test you can check with the isLedOpen() function.
///
void AS1130_runManualTest();

/// @brief Get the status of a LED.
///
/// If a LED is physically connected to the device and works, this function will
/// return LedStatusOk. If no LED is connected or if there is a problem, the function
/// will return LedStatusOpen. The a led index is disabled in the chip, you will
/// get the status LedStatusDisabled.
///
/// You have to start a test, before this function will return a valid value.
/// Use setAutomaticTestEnabled() or runManualTest() for the test.
///
/// @param ledIndex The index of the LED to test. A value between 0x00 and 0xba.
///   This chip has a special LED numbering. 0x00-0x0a, 0x10-0x1a, etc. The
///   LEDs between this values are reported as disabled. Also all values over 0xba
///   report a disabled LED.
/// @return The status for the given LED index.
///
LedStatus AS1130_getLedStatus(uint8_t ledIndex);

/// @brief Check if a LED test is running.
///
/// @return `true` if a LED test is running, `false` if no test is running.
///
bool AS1130_isLedTestRunning();

/// @brief Check if a movie is runnning.
///
/// @return `true` if a movie is running, `false` if no movie is running.
///
bool AS1130_isMovieRunning();

/// @brief Get the current displayed frame.
///
/// @return The frame index. A value between 0 and 35.
///
uint8_t AS1130_getDisplayedFrame();

/// @brief Get the interrupt status register.
///
/// @return The bitmask with the interrupt status.
///
uint8_t AS1130_getInterruptStatus();

/// @name Low-Level Functions.
/// Functions used for low-level operations.
/// @{

/// @brief Write a two byte sequence to the chip.
///
/// @param address The address byte.
/// @param data The data byte.
///
void AS1130_writeToChip(uint8_t address, uint8_t data);

/// @brief Write a byte sequence to the chip.
///
/// @param address The address byte.
/// @param pdata Pointer to the data.
/// @param size Size of the data.
///
void AS1130_pWriteToChip(uint8_t *pdata, uint8_t size);

/// @brief Write a byte to a given memory location.
///
/// @param registerSelection The register selection address.
/// @param address The address of the register.
/// @param data The data byte to write to the selected register.
///
void AS1130_writeToMemory(uint8_t registerSelection, uint8_t address, uint8_t *data, uint8_t size);

/// @brief Fill a memory location block with a single byte/
///
/// @param registerSelection The register selection address.
/// @param startAddress The address of the register.
/// @param value The value to write.
/// @param size The number of bytes to write.
///
void AS1130_fillMemory(uint8_t registerSelection, uint8_t address, uint8_t value, uint8_t size);

/// @brief Read a byte from a given memory location.
///
/// @param registerSelection The register selection address.
/// @param address The address of the register.
/// @return The read byte.
///
uint8_t AS1130_readFromMemory(uint8_t registerSelection, uint8_t address);

/// @brief Write a byte to a control register.
///
/// @param controlRegister The control register.
/// @param data The data byte to write to the control register.
///
void AS1130_writeControlRegister(ControlRegister controlRegister, uint8_t data);

/// @brief Read a byte from a control register.
///
/// @param controlRegister The control register to read a byte from.
/// @return The read byte.
///
uint8_t AS1130_readControlRegister(ControlRegister controlRegister);

/// @brief Write bits in a control register.
///
/// @param controlRegister The control register to change.
/// @param mask The mask for the bits. Only the bits set in this mask are changed.
/// @param data The bits to set. The data is masked with the mask.
///
void AS1130_writeControlRegisterBits(ControlRegister controlRegister, uint8_t mask, uint8_t data);

/// @brief Set selected bits in a control register.
///
/// @param controlRegister The control register to change.
/// @param mask The mask for the bits to set.
///
void AS1130_setControlRegisterBits(ControlRegister controlRegister, uint8_t mask);

/// @brief Clear selected bits in a control register.
///
/// @param controlRegister The control register to change.
/// @param mask The mask for the bits to clear.
///
void AS1130_clearControlRegisterBits(ControlRegister controlRegister, uint8_t mask);

/// @brief Set or clear selected bits in a control register.
///
/// @param controlRegister The control register to change.
/// @param mask The mask for the bits to clear.
/// @param setBits True to set the bits, false to clear the bits.
///
void AS1130_setOrClearControlRegisterBits(ControlRegister controlRegister, uint8_t mask, bool setBits);


