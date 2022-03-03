import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:vaja_1/src/ui/viewes/home_page/widgets/accelerometer_widget.dart';
import 'package:vaja_1/src/ui/viewes/home_page/widgets/gyroscope_widget.dart';
import 'package:vaja_1/src/ui/viewes/home_page/widgets/location_widget.dart';
import 'package:vaja_1/src/ui/viewes/home_page/widgets/magnetometer_widget.dart';
import 'package:vaja_1/src/ui/widgets/helpers/dividors.dart';

class HomePage extends StatefulWidget {
  const HomePage({Key? key}) : super(key: key);

  @override
  State<StatefulWidget> createState() {
    return _HomePageState();
  }
}

class _HomePageState extends State<HomePage> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text(
          'Sensors data',
        ),
      ),
      body: Center(
        child: Column(
          children: const <Widget>[
            LocationWidget(),
            horizontalSpaceDividerLarge,
            AccelerometerWidget(),
            horizontalSpaceDividerLarge,
            MagnetometerWidget(),
            horizontalSpaceDividerLarge,
            GyroscopeWidget(),
/*            ListItem(),
            horizontalSpaceDividerLarge,
            ListItem(),
            horizontalSpaceDividerLarge,
            ListItem(),*/
          ],
        ),
      ),
    );
  }
}
