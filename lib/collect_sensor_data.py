import tempfile

import boto3 as boto3
import serial.serialutil

from datetime import datetime
from serial import Serial

# The port which your arduino is using to write to serial monitor
ARDUINO_PORT = '/dev/ttyACM0'
S3_BUCKET = 'gardener-bot-sensor-data-bucket'

if __name__ == "__main__":
    # Set up serial port from your Arduino
    light_meter_ser = Serial(ARDUINO_PORT, timeout=1)

    # A temporary file we can upload to s3
    tmp_file = tempfile.NamedTemporaryFile()
    # The s3 file name
    date = datetime.now()
    s3_file_name = f"{date.strftime('%Y-%m-%d_%H%M')}_light_sensor_data"

    # A variable to keep track of data flowing through serial port
    data_exists = True

    # While serial port is sending data, write to a temp file
    # TODO: Maybe limit the size of the temp file before it gets uploaded?
    while data_exists:
        try:
            data = light_meter_ser.readline()
            tmp_file.write(data)
        except serial.serialutil.SerialException:
            print("No more data is being sent!")
            data_exists = False

    # Upload temp file to S3
    s3 = boto3.client('s3')
    s3.upload_file(tmp_file.name, S3_BUCKET, s3_file_name)
    print(f"Temp file {tmp_file.name} was written to {S3_BUCKET}/{s3_file_name}")

    # Close and delete temporary file
    tmp_file.close()
