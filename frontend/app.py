from flask import Flask, request, render_template, jsonify
import re

app = Flask(__name__)

latest = {"lat": 0.0, "lon": 0.0}

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/update")
def update():
    """Receive direct lat/lon from STM32"""
    try:
        lat = float(request.args.get("lat", 0))
        lon = float(request.args.get("lon", 0))
        latest["lat"], latest["lon"] = lat, lon
        print(f"📡 Updated position: lat={lat}, lon={lon}")
        return "OK"
    except Exception as e:
        print("Update error:", e)
        return "ERROR", 400

@app.route("/raw", methods=["GET", "POST"])
def raw():
    """Receive raw CGNSINF-style data and extract lat/lon"""
    raw_data = request.data.decode() if request.method == "POST" else request.args.get("data", "")
    print(f"🛰️ Raw data received: {raw_data}")

    # Example raw string:
    # +CGNSINF: 1,1,20251014193000.000,41.8781,-87.6298,180.00,0.00,0.0,0.0,1.0,1.0,0.9,,12,7,,,44,

    # Use regex to extract latitude and longitude
    match = re.search(r"\+CGNSINF: [^,]*,[^,]*,[^,]*,([-\d.]+),([-\d.]+)", raw_data)
    if match:
        lat, lon = float(match.group(1)), float(match.group(2))
        latest["lat"], latest["lon"] = lat, lon
        print(f"✅ Parsed coordinates: lat={lat}, lon={lon}")
        return "OK"
    else:
        print("⚠️ Could not parse lat/lon from raw data")
        return "PARSE_ERROR", 400

@app.route("/data")
def data():
    return jsonify(latest)

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
