import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# Project Doppler
# 2024.07.08 By Mint

# 아두이노의 시리얼 포트 설정입니다. 시리얼 포트 값이 하드코딩 되어있으니, 환경에 따라 수정하셔야합니다.
ser = serial.Serial('/dev/cu.usbmodem1101', 9600)

fig, (ax1, ax2) = plt.subplots(2, 1)
x_data, speed_data, freq_data = [], [], []

def update_graph(frame):
    line = ser.readline().decode('utf-8').strip()
    if line:
        try:
            speed, freq = map(float, line.split(','))
            x_data.append(frame)
            speed_data.append(speed)
            freq_data.append(freq)
            
            ax1.clear()
            ax2.clear()
            
            ax1.plot(x_data, speed_data, label='Relative Speed (m/s)')
            ax2.plot(x_data, freq_data, label='Delta Frequency (Hz)', color='red')
            
            ax1.legend(loc='upper left')
            ax2.legend(loc='upper left')
            
            ax1.set_title('Relative Speed vs Time')
            ax2.set_title('Delta Frequency vs Time')
            
            ax1.set_xlabel('Time')
            ax1.set_ylabel('Speed (m/s)')
            
            ax2.set_xlabel('Time')
            ax2.set_ylabel('Frequency (Hz)')
        except ValueError:
            pass

ani = animation.FuncAnimation(fig, update_graph, interval=100)
plt.show()