import 'dart:convert';

class TelemetryData {
  bool connected;
  int leftWheelSpeed;
  int rightWheelSpeed;
  bool isLeftSensorDark;
  bool isRightSensorDark;
  int distanceTravelled;

  TelemetryData(
      {this.connected = false,
      this.leftWheelSpeed = 0,
      this.rightWheelSpeed = 0,
      this.isLeftSensorDark = false,
      this.isRightSensorDark = false,
      this.distanceTravelled = 0});

  TelemetryData.fromJson(Map<String, dynamic> json)
      : connected = json['connected'] as bool? ?? false,
        leftWheelSpeed = json['leftWheelSpeed'] as int? ?? 0,
        rightWheelSpeed = json['leftWheelSpeed'] as int? ?? 0,
        isLeftSensorDark = json['isLeftSensorDark'] as bool? ?? false,
        isRightSensorDark = json['isRightSensorDark'] as bool? ?? false,
        distanceTravelled = json['distanceTravelled'] as int? ?? 0;

  static Map<String, dynamic> toJson(TelemetryData value) => {
        'connected': value.connected,
        'leftWheelSpeed': value.leftWheelSpeed,
        'rightWheelSpeed': value.rightWheelSpeed,
        'isLeftSensorDark': value.isLeftSensorDark,
        'isRightSensorDark': value.isRightSensorDark,
        'distanceTravelled': value.distanceTravelled
      };

  /*static String? listToString(List<TelemetryData>? tasks) {
    if (tasks == null) {
      return null;
    }
    var jsonText = (tasks.map((task) => jsonEncode(TelemetryData.toJson(task))))
        .toList()
        .toString();
    jsonText = jsonText.replaceAll("(", "[");
    jsonText = jsonText.replaceAll(")", "]");
    return jsonText;
  }*/
}
