import serial
import tkinter as tk
import time

import translation as mc

# Definitions for the serial connection
PORT = '/dev/tty.usbserial-54F40065441'
BAUD_RATE = 9600


# Create a serial connection
ser = serial.Serial()  
ser.port = PORT
ser.baudrate = BAUD_RATE
ser.open()


# Setup translation
word = ""
fontSizes = [10, 12, 18, 24, 30, 36, 48, 60, 72, 96]
backgroundColor = "#4E4B5C"
fontColor = "#EDF2F4"



############################
#     READ SERIAL DATA     #
############################

def update_display():
    global word
    
    if ser.in_waiting > 0:
        # Read data from serial port
        data = ser.readline().decode().strip()
        print(data)
        
        if data == "." or data == "-":
            word += data
        elif data == "space":
            word += " "
        elif data == "doublespace":
            word += " / "
        elif data == "delete":
            print("delete")
            word = ""
        else: 
            parts = data.split()
            dialVal = int(float(parts[1]))
            
            for i in range(3):
                if i==0:
                    labels[i].config(font=("Lato", round(fontSizes[dialVal]*1.5), "bold"))
                else:
                    labels[i].config(font=("Lato", fontSizes[dialVal]))
        
        # Update the label text with the received data
        labels[1].config(text=word)
        labels[2].config(text=mc.morse_to_text(word))
        
    # Schedule the function to run again after 100ms
    root.after(100, update_display)



############################
#   SETUP TKINTER WINDOW   #
############################

# Create the main Tkinter window
root = tk.Tk()
root.title("Serial Data Receiver")
root.geometry("1000x500")  # Width x Height
root.config(bg=backgroundColor)


# Create labels to display the received data
labels = []
for i in range(3): 
    if i==0:
        label = tk.Label(root, text="", font=("Lato", round(34*1.5), "bold"), fg=fontColor, bg=backgroundColor)
        label.pack(pady=30)  

    else:
        label = tk.Label(root, text="", font=("Lato", 34), fg=fontColor, bg=backgroundColor)
        label.pack(pady=5)  
    labels.append(label)

labels[0].config(text="Morse Code to Text")

# Start updating the display
update_display()

# Start the Tkinter event loop
root.mainloop()