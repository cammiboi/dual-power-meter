from dual_power_meter import DualPowerMeter
from time import sleep

Meter = DualPowerMeter("/dev/cu.usbserial-1430")

sleep(1)

Meter.get_new_reading()

print("Ch 1 => {} V {} mA".format(Meter.get_v1(), Meter.get_i1()))
print("Ch 2 => {} V {} mA".format(Meter.get_v2(), Meter.get_i2()))