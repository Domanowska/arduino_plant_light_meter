import boto3 as boto3
import serial.serialutil

from datetime import datetime

from boto3.dynamodb.conditions import Attr
from serial import Serial

# The name of your DynamoDB Table
DYNAMO_TABLE = 'gardener_bot_light_sensor_data'
# The port which your arduino is using to write to serial monitor
ARDUINO_PORT = '/dev/ttyACM0'

if __name__ == "__main__":
    # DynamoDB
    dynamo = boto3.resource('dynamodb')
    table = dynamo.Table(DYNAMO_TABLE)
    print(table.creation_date_time)

    # Set up serial port from your Arduino
    light_meter_ser = Serial(ARDUINO_PORT, timeout=1)

    # A variable to keep track of data flowing through serial port
    data_exists = True

    # While serial port is sending data, write to DB
    while data_exists:
        try:
            data = light_meter_ser.readline()
            try:
                data = data.decode('utf8')
            except:
                print(f"Could not decode byte {data}")
                data = str(data)
            table.put_item(
                Item={
                    'timestamp': datetime.now().strftime('%Y-%m-%d-%H%M%S.%f'),
                    'data': data
                }
            )
            response = table.scan(FilterExpression=Attr('data').eq(data))
            print(response['Items'])
        except serial.serialutil.SerialException:
            print("No more data is being sent!")
            data_exists = False
