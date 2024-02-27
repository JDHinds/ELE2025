import 'dart:typed_data';
import 'package:flutter/material.dart';
import 'package:flutter/foundation.dart';
import 'package:flutter_libserialport/flutter_libserialport.dart'; //https://www.youtube.com/watch?v=4WiH9pf2ULQ

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
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
        useMaterial3: true,
      ),
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
  SerialPort port = SerialPort(SerialPort.availablePorts[0]);
  late SerialPortReader reader;

  List<int> data = [];

  @override
  void initState() {
    super.initState();

    print(SerialPort.availablePorts);

    port.config = SerialPortConfig()
      ..baudRate = 2000000
      ..bits = 8
      ..parity = 0
      ..stopBits = 1;

    //port.config.setFlowControl(2);

    var res = port.openReadWrite();

    if (!res) {
      print('Error opening port:${port.name}');
    }

    reader = SerialPortReader(port);
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: StreamBuilder<Uint8List>(
        stream: reader.stream,
        builder: (context, snapshot) {
          if (snapshot.hasError) {
            return Text('Error: ${snapshot.error}');
          }
          if (snapshot.connectionState == ConnectionState.waiting) {
            return const Text('Awaiting result...');
          }

          var decodedString = String.fromCharCodes(snapshot.data!);

          return Text(decodedString);
        },
      ),
    );
  }

  @override
  void dispose() {
    port.close();
    super.dispose();
  }
}

//flutter run -d windows
