import 'dart:convert';
import 'dart:typed_data';
import 'package:flutter/material.dart';
import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';
import 'package:flutter_libserialport/flutter_libserialport.dart';
import 'package:robot_control/telemetry.dart'; //https://www.youtube.com/watch?v=4WiH9pf2ULQ

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'robot_control',
      theme: ThemeData(
          useMaterial3: true,
          colorScheme: const ColorScheme.dark(
            primary: Color.fromARGB(255, 54, 117, 136),
            secondary: Color.fromARGB(255, 47, 79, 79),
            background: Color.fromARGB(255, 70, 70, 70),
          )),
      home: const MyHomePage(),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({super.key});
  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  SerialPort port = SerialPort(SerialPort.availablePorts[1]);
  late SerialPortReader reader;

  TelemetryData currentState = TelemetryData();
  String data = "";

  bool AutoMode = false;

  @override
  void initState() {
    super.initState();

    var res = port.openReadWrite();

    port.config = SerialPortConfig()
      ..baudRate = 115200
      ..bits = 8
      ..parity = 0
      ..stopBits = 1;

    if (!res) {
      print('Error opening port:${port.name}');
    }

    reader = SerialPortReader(port);
  }

  @override
  Widget build(BuildContext context) {
    return Focus(
      autofocus: true,
      onKeyEvent: (node, event) {
        if (!AutoMode) {
          if (event.logicalKey == LogicalKeyboardKey.keyW &&
              (event is KeyDownEvent || event is KeyRepeatEvent)) {
            currentState.leftWheelSpeed = 255;
            currentState.rightWheelSpeed = 255;
          } else if (event.logicalKey == LogicalKeyboardKey.keyA &&
              (event is KeyDownEvent || event is KeyRepeatEvent)) {
            currentState.leftWheelSpeed = -124;
            currentState.rightWheelSpeed = 124;
          } else if (event.logicalKey == LogicalKeyboardKey.keyD &&
              (event is KeyDownEvent || event is KeyRepeatEvent)) {
            currentState.leftWheelSpeed = 124;
            currentState.rightWheelSpeed = -124;
          } else if (event.logicalKey == LogicalKeyboardKey.keyS &&
              (event is KeyDownEvent || event is KeyRepeatEvent)) {
            currentState.leftWheelSpeed = -255;
            currentState.rightWheelSpeed = -255;
          } else if (event is KeyUpEvent) {
            currentState.leftWheelSpeed = 0;
            currentState.rightWheelSpeed = 0;
          }
          return KeyEventResult.handled;
        }
        return KeyEventResult.ignored;
      },
      child: StreamBuilder<Uint8List>(
        stream: reader.stream,
        builder: (context, snapshot) {
          if (snapshot.hasError) {
            currentState = TelemetryData();

            return Text('Error: ${snapshot.error}');
          }
          if (snapshot.connectionState == ConnectionState.waiting) {
            port.write(Uint8List.fromList("{echo}\n".codeUnits));
            return Scaffold(
              body: Text('Awaiting result...'),
              floatingActionButton: Row(
                children: [
                  const Spacer(),
                  IconButton(
                    icon: const Icon(Icons.precision_manufacturing),
                    onPressed: () {
                      AutoMode = true;
                      port.write(Uint8List.fromList("{auto}\n".codeUnits));
                    },
                  ),
                  IconButton(
                    icon: const Icon(Icons.control_camera),
                    onPressed: () {
                      AutoMode = false;
                      port.write(Uint8List.fromList("{manual}\n".codeUnits));
                    },
                  ),
                ],
              ),
            );
          }

          if (AutoMode) {
            var decodedString = String.fromCharCodes(snapshot.data!);
            try {
              /*if (decodedString.contains('}')) {
                data += decodedString.substring(0, decodedString.indexOf('}'));
                currentState = TelemetryData.fromShortJson(
                    json.decode(data.toString().substring(0, data.length - 2)));
                print(data);
              } else if (decodedString[0] == '{') {
                data = decodedString;
              } else {
                data += decodedString;
              }*/

              print(decodedString);

              if (decodedString[0] == '0') {
                currentState.leftWheelSpeed = 220;
                currentState.rightWheelSpeed = 220;
                currentState.isLeftSensorDark = false;
                currentState.isRightSensorDark = false;
              } else if (decodedString[0] == '1') {
                currentState.leftWheelSpeed = 90;
                currentState.rightWheelSpeed = 90;
                currentState.isLeftSensorDark = false;
                currentState.isRightSensorDark = false;
              } else if (decodedString[0] == '2') {
                currentState.leftWheelSpeed = -70;
                currentState.rightWheelSpeed = 60;
                currentState.isLeftSensorDark = true;
                currentState.isRightSensorDark = false;
              } else if (decodedString[0] == '3') {
                currentState.leftWheelSpeed = 60;
                currentState.rightWheelSpeed = -70;
                currentState.isLeftSensorDark = false;
                currentState.isRightSensorDark = true;
              } else if (decodedString[0] == '4') {
                currentState.leftWheelSpeed = 70;
                currentState.rightWheelSpeed = 70;
                currentState.isLeftSensorDark = false;
                currentState.isRightSensorDark = false;
              } else if (decodedString[0] == '5') {
                currentState.leftWheelSpeed = 100;
                currentState.rightWheelSpeed = 100;
                currentState.isLeftSensorDark = false;
                currentState.isRightSensorDark = false;
              } else {
                currentState.leftWheelSpeed = 0;
                currentState.rightWheelSpeed = 0;
                currentState.isLeftSensorDark = false;
                currentState.isRightSensorDark = false;
              }
            } catch (ex) {
              print(ex);
              currentState.connected = false;
            }
          } else {
            print(String.fromCharCodes(snapshot.data!));
            port.write(Uint8List.fromList(
                (TelemetryData.toJson(currentState).toString() + "\n")
                    .codeUnits));
          }

          return Scaffold(
            body: Row(
              children: [
                SafeArea(child: portInfo(port)),
                Expanded(
                  child: telemetryDisplay(currentState),
                ),
              ],
            ),
            floatingActionButton: Row(
              children: [
                const Spacer(),
                IconButton(
                  icon: const Icon(Icons.precision_manufacturing),
                  onPressed: () {
                    AutoMode = true;
                    port.write(Uint8List.fromList("{auto}\n".codeUnits));
                  },
                ),
                IconButton(
                  icon: const Icon(Icons.control_camera),
                  onPressed: () {
                    AutoMode = false;
                    port.write(Uint8List.fromList("{manual}\n".codeUnits));
                  },
                ),
              ],
            ),
          );
        },
      ),
    );
  }

  @override
  void dispose() {
    port.close();
    super.dispose();
  }

  Widget telemetryDisplay(TelemetryData state) {
    return Column(
      children: [
        Row(
          children: [
            Spacer(),
            Text(
              "Distance travelled: " + state.distanceTravelled.toString() + "m",
              //style:
              //  DefaultTextStyle.of(context).style.apply(fontSizeFactor: 3.0),
            ),
            Spacer(),
          ],
        ),
        Row(
          children: [
            Expanded(
              child: Column(
                children: [
                  Icon(Icons.incomplete_circle, size: 200),
                  Slider(
                      value: state.leftWheelSpeed.toDouble(),
                      min: -255,
                      max: 255,
                      inactiveColor: Colors.white,
                      onChanged: ((double i) {})),
                  Row(
                    children: [
                      const Spacer(),
                      Text("Left Wheel Speed: " +
                          currentState.leftWheelSpeed.toString()),
                      const Spacer(),
                      const Text("Left Sensor: "),
                      Container(
                        color: state.isLeftSensorDark
                            ? Colors.black
                            : Colors.white,
                        width: 50,
                        height: 50,
                      ),
                      const Spacer()
                    ],
                  ),
                ],
              ),
            ),
            Expanded(
              child: Column(
                children: [
                  Icon(Icons.incomplete_circle, size: 200),
                  Slider(
                      value: state.rightWheelSpeed.toDouble(),
                      min: -255,
                      max: 255,
                      inactiveColor: Colors.white,
                      onChanged: ((double i) {})),
                  Row(
                    children: [
                      const Spacer(),
                      Text("Right Wheel Speed: " +
                          currentState.rightWheelSpeed.toString()),
                      const Spacer(),
                      const Text("Right Sensor: "),
                      Container(
                        color: state.isRightSensorDark
                            ? Colors.black
                            : Colors.white,
                        width: 50,
                        height: 50,
                      ),
                      const Spacer()
                    ],
                  ),
                ],
              ),
            ),
          ],
        )
      ],
    );
  }

  Widget portInfo(SerialPort port) {
    return Drawer(
      child: ListView(
        children: [
          ListTile(
            title: Text(port.description!),
          ),
          ListTile(
            title: Text(port.transport.toString()),
          )
        ],
      ),
    );
  }
}

//flutter run -d windows
