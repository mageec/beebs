#!/usr/bin/env python2

import pyenergy
import sys
from time import sleep

if len(sys.argv) is not 4:
  sys.stderr.write("Usage: energytool.py SERIAL POINT PIN")
  sys.exit(1)

serial_port = sys.argv[1]
trigger_pin = sys.argv[3]

try:
  measurement_point = int(sys.argv[2])
except ValueError:
  sys.exit(1)

try:
  em = pyenergy.EnergyMonitor(serial_port)
  em.connect()

  em.enableMeasurementPoint(measurement_point)
  em.setTrigger(trigger_pin, measurement_point)
except RuntimeError:
  sys.exit(1)


while not em.measurementCompleted():
  sleep(0.1)

m = em.getMeasurement(measurement_point)

# Print out the measurement using csv.
print "{:f},{:f},{:f},{:f},{:f}".format(m.energy, m.time, m.avg_power, m.avg_current, m.avg_voltage)
