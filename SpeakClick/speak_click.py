import sounddevice as sd
import win32api
import numpy as np

class Sound:
    def __init__(self):
        self.decibel = 0

    def set_decibel(self, indata, outdata, frames, time, status):
        self.decibel = np.linalg.norm(indata)*10


        
if __name__ == '__main__':
    s = Sound()
    q_key = 0x51
    print("Q to quit")
    with sd.Stream(callback=s.set_decibel):
       while True:
           if win32api.GetAsyncKeyState(q_key):
              break
