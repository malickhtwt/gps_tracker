import time
import math
import requests

# Flask server endpoint that accepts raw GPS data
URL = "http://127.0.0.1:5000/raw"
# URL = "https://gps-tracker-8747.onrender.com/raw"

# Center coordinates — Houston, TX
lat0 = 29.7604
lon0 = -95.3698

print("🚀 Sending mock raw GPS data around Houston...")

angle = 0
while True:
    # Move in a small circle (~100 m radius)
    lat = lat0 + 0.001 * math.sin(math.radians(angle))
    lon = lon0 + 0.001 * math.cos(math.radians(angle))

    # Build a fake SIM7600 +CGNSINF response line
    raw_data = (
        f"+CGNSINF: 1,1,20251030193000.000,{lat:.6f},{lon:.6f},100.0,0.00,0.0,0.0,"
        "1.0,1.0,0.9,,12,7,,,44,"
    )

    try:
        # Send it to your Flask /raw route using POST
        r = requests.post(URL, data=raw_data.encode(), timeout=2)
        print(f"Sent raw: {raw_data}")
        print(f"Server replied: {r.text}")
    except Exception as e:
        print("Error:", e)

    angle = (angle + 10) % 360
    time.sleep(2)
