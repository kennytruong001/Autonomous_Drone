# JSON-settings

This file contains all the settings you would probably need for our sim purposes.
Navigate to your settings.json file in the path **C:\Documents\Airsim**. Copy and paste the appropriate section into the settings.json file. Make sure to replace everything in your existing json file. 

### Single Drone Base with defined spawn points

    {
      "SeeDocsAt": "https://github.com/Microsoft/AirSim/blob/master/docs/settings.md",
      "SettingsVersion": 1.2,
      "SimMode": "Multirotor",
      "ClockSpeed": 1.0,
      "Vehicles": {
            "Drone1": {
                "VehicleType": "SimpleFlight",
                "X": 4,
                "Y": 0,
                "Z": -2,
                "EnableCollisionPassthrogh": false,
                "EnableCollisions": true,
                "AllowAPIAlways": true,
                "RC": {
                    "RemoteControlID": 0,
                    "AllowAPIWhenDisconnected": false
                }
             }
      }
    }

### Single Drone with API, Collision, and Spawn Point Enabled

    {
      "SeeDocsAt": "https://github.com/Microsoft/AirSim/blob/master/docs/settings.md",
      "SettingsVersion": 1.2,
      "SimMode": "Multirotor",
      "ClockSpeed": 1.0,
      "Vehicles": {
          "Drone1": {
            "VehicleType": "SimpleFlight",
            "X": 4,
            "Y": 0,
            "Z": -2,
            "EnableCollisionPassthrogh": false,
            "EnableCollisions": true,
            "AllowAPIAlways": true,
            "RC": {
                "RemoteControlID": 0,
                "AllowAPIWhenDisconnected": false
            }
          }
      }
    }


### Two Drones with API, Collision, Spawn Points; drones are named "Drone1" and "Drone2"

    {
        "SettingsVersion": 1.2,
        "SimMode": "Multirotor",
        "ClockSpeed": 1.0,
        "Vehicles": {
            "Drone1": {
                "VehicleType": "SimpleFlight",
                "X": 4,
                "Y": 0,
                "Z": -2,
                "EnableCollisionPassthrogh": false,
                "EnableCollisions": true,
                "AllowAPIAlways": true,
                "RC": {
                    "RemoteControlID": 0,
                    "AllowAPIWhenDisconnected": false
                }
            },
            "Drone2": {
            "VehicleType": "SimpleFlight",
            "X": 8,
            "Y": 0,
            "Z": -2,
            "EnableCollisionPassthrogh": false,
            "EnableCollisions": true,
            "AllowAPIAlways": true,
             "RC": {
                "RemoteControlID": 0,
                "AllowAPIWhenDisconnected": false
              }
            }
        }
    }
