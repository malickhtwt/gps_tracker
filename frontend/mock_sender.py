import time
import math
import requests

# Flask server endpoint (adjust if needed)
URL = "http://127.0.0.1:5000/update"

# Center coordinates — Houston, TX
lat0 = 29.7604
lon0 = -95.3698

print("🚀 Sending mock GPS data around Houston...")

angle = 0
while True:
    # Move in a small circle (~100 m radius)
    lat = lat0 + 0.001 * math.sin(math.radians(angle))
    lon = lon0 + 0.001 * math.cos(math.radians(angle))

    # Send data to Flask endpoint
    params = {"lat": lat, "lon": lon}
    try:
        r = requests.get(URL, params=params, timeout=1)
        print(f"Sent: {params}, Server: {r.text}")
    except Exception as e:
        print("Error:", e)

    angle = (angle + 10) % 360  # increment angle
    time.sleep(2)  # update every 2 seconds
import time
import math
import requests

# Flask server endpoint (adjust if needed)
URL = "http://127.0.0.1:5000/update"

# Center coordinates — Houston, TX
lat0 = 29.7604
lon0 = -95.3698

print("🚀 Sending mock GPS data around Houston...")

angle = 0
while True:
    # Move in a small circle (~100 m radius)
    lat = lat0 + 0.001 * math.sin(math.radians(angle))
    lon = lon0 + 0.001 * math.cos(math.radians(angle))

    # Send data to Flask endpoint
    params = {"lat": lat, "lon": lon}
    try:
        r = requests.get(URL, params=params, timeout=1)
        print(f"Sent: {params}, Server: {r.text}")
    except Exception as e:
        print("Error:", e)

    angle = (angle + 10) % 360  # increment angle
    time.sleep(2)  # update every 2 seconds
