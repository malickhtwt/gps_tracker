from flask import Flask, request, render_template, jsonify

app = Flask(__name__)

# store the latest coordinates in memory
latest = {"lat": 0.0, "lon": 0.0}


@app.route("/")
def index():
    """Serve the map page"""
    return render_template("index.html")


@app.route("/update")
def update():
    """Receive GPS updates from STM32"""
    try:
        lat = float(request.args.get("lat", 0))
        lon = float(request.args.get("lon", 0))
        latest["lat"], latest["lon"] = lat, lon
        print(f"📡 Updated position: lat={lat}, lon={lon}")
        return "OK"
    except Exception as e:
        print("Update error:", e)
        return "ERROR", 400


@app.route("/data")
def data():
    """Send current coordinates to the map page"""
    return jsonify(latest)


if __name__ == "__main__":
    # use host='0.0.0.0' so STM32 can reach your computer over LAN
    app.run(host="0.0.0.0", port=5000, debug=True)
