import sounddevice as sd
import win32api
import win32con
import numpy as np
import time

class Sound:
    def __init__(self):
        self.decibel = 0

    def set_decibel(self, indata, outdata, frames, time, status):
        self.decibel = np.linalg.norm(indata)*10


        
if __name__ == '__main__':
    s = Sound()
    q_key = 0x51
    left_click = 0x01
    print("Q to quit")
    with sd.Stream(callback=s.set_decibel):
       while True:
            if s.decibel >= 3:
                #print(str(s.decibel))
                win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0)
                time.sleep(0.05)
                win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP, 0, 0, 0, 0)
            if win32api.GetAsyncKeyState(q_key):
                break
