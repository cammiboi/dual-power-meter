from serial import Serial


class DualPowerMeter():
    def __init__(self, serial_port: str):
        # open serial port for load and set receieve timeout to 0.5 sec
        self.ser = Serial(serial_port, 115200, timeout=0.5)

        self.v1 = 0.0
        self.i1 = 0.0
        self.v2 = 0.0
        self.i2 = 0.0

    def get_new_reading(self):
        self.ser.write("R".encode('utf-8'))
        self.v1 = float(self.ser.readline())
        self.i1 = float(self.ser.readline())
        self.v2 = float(self.ser.readline())
        self.i2 = float(self.ser.readline())

    def get_v1(self):
        return self.v1

    def get_v2(self):
        return self.v2

    def get_i1(self):
        return self.i1

    def get_i2(self):
        return self.i2