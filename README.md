# Morse Code Interpretation Tool
This code powers the Morse Code interpretation tool. This project uses an ESP32 to extract data from three 5-pin buttons and a potentiometer. This data is then used to generate and translate Morse Code. 

![Tool Demonstration](morse-code-doc.gif)


## Setup Requirements

### Python development environment (macOS)

1. Install [Python](https://www.python.org/downloads/). 

2. In this project's directory, create a virtual copy of the Python installation:

    ```bash 
    python -m venv env
    ```

3. Activate the virtual environment:

    ``` bash 
    source env/bin/activate
    ```

4. From this project's directory, install requirements:

    ```bash
    pip install -r ./requirements.txt
    ```

### Prepare ESP32

1. Install the [Arduino IDE](https://www.arduino.cc/en/software) (versions listed below).

2. Save `sensor-reading.ino` in a folder of the same name.

3. Open `sensor-reading.ino` in the Aruino IDE.

4. Plug your ESP32 into your computer, selecting the correct port and board (TTGO T1).

5. Upload the code to the ESP32.


## How to Run

1. Ensure the virtual environment is activated.

2. Verify that the ESP32 is connected to the computer and the Serial Monitor is closed in the Arduino IDE.

3. In this project's directory, run:
    ```bash
    python display.py
    ```

## Usage

### Write Button
- Short press: prints a dot (.)
- Long press (> 500 ms): prints a dash (-)

### Space Button
- Short press: indicates a new letter is starting
- Long press (> 500 ms): prints a whitespace (i.e., indicates a new word is starting)

### Delete Button
- Press once to clear all generated text.

### Font Size Dial
- On the first usage of the dial, the font size syncs up to the dial's location.
- Turn clockwise to increase font size.
- Turn counter-clockwise to decrease font size.


## Details

### Features
- Real-time translation of Morse Code input from physical buttons and a potentiometer.
- Interface displays both the Morse Code and its corresponding text interpretation.
- Ability to delete characters and add spaces while composing Morse Code sequences.

### Code Overview
- `display.py`: Handles the GUI interface using Tkinter and processes serial data from the ESP32.
- `translation.py`: Contains helper functions to convert text to Morse Code and vice versa.
- `sensor-reading.ino`: Arduino code uploaded to the ESP32, responsible for reading button presses and potentiometer values and sending data over serial communication.

### About
- Author: Aryana Mohammadi
- Built with Arduino IDE version 2.3.0, CLI Version: 0.35.2
- Displayed on a ESP32 TTGO, Model: T-Display V1.1
- This project runs on Python 3.9.12.
- Updated March 24, 2024