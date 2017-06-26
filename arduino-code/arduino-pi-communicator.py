from datetime import datetime
import serial
import sys
import sqlite3

db = sqlite3.connect("plantdata.db")
sql_table = '''
CREATE TABLE plant_data(timestamp text, sensor_read text, percentage text, num_lights text)
'''

cursor = db.cursor()
cursor.execute(sql_table)

cur_time = datetime.now()

cursor.execute('''INSERT INTO plant_data(timestamp, sensor_read, percentage, num_lights) VALUES(?,?,?,?)''',
               (cur_time, "255.0", "95.0", "Test Data"))

ser_port = serial.Serial("/dev/ttyACM0", 9600)

while 1:
    data = ser_port.readline().decode()[:-1].strip().split(",")
    sensor_read = data[0]
    percentage = data[1]
    num_leds = data[2]
    cur_time = datetime.now()
    cursor.execute('''INSERT INTO plant_data(timestamp, sensor_read, percentage, num_lights) VALUES(?,?,?,?)''',
                   (cur_time, sensor_read, percentage, num_leds))
    db.commit()
    print(cur_time, sensor_read, percentage, num_leds)