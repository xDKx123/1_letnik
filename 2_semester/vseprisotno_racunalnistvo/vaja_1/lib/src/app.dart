import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter_bloc/flutter_bloc.dart';
import 'package:vaja_1/src/blocs/accelerometer_bloc/accelerometer_bloc.dart';
import 'package:vaja_1/src/blocs/gyroscope_bloc/gyroscope_bloc.dart';
import 'package:vaja_1/src/blocs/location_bloc/location_bloc.dart';
import 'package:vaja_1/src/blocs/magnetometer_bloc/magnetometer_bloc.dart';
import 'package:vaja_1/src/ui/viewes/home_page/home_page.dart';

class App extends StatelessWidget {
  const App({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return MultiBlocProvider(
      providers: <BlocProvider<dynamic>>[
        BlocProvider<LocationBloc>(
          create: (BuildContext context) => LocationBloc()
            ..add(
              const LocationInitialize(),
            ),
        ),
        BlocProvider<AccelerometerBloc>(
          create: (BuildContext context) => AccelerometerBloc()
            ..add(
              const AccelerometerInitialize(),
            ),
        ),
        BlocProvider<MagnetometerBloc>(
          create: (BuildContext context) => MagnetometerBloc()
            ..add(
              const MagnetometerInitialize(),
            ),
        ),
        BlocProvider<GyroscopeBloc>(
          create: (BuildContext context) => GyroscopeBloc()
            ..add(
              const GyroscopeInitialize(),
            ),
        ),
      ],
      child: const AppView(),
    );
  }
}

class AppView extends StatefulWidget {
  const AppView({Key? key}) : super(key: key);

  @override
  State<StatefulWidget> createState() {
    return _AppViewState();
  }
}

class _AppViewState extends State<AppView> {
  @override
  Widget build(BuildContext context) {
    return const MaterialApp(
      title: 'Vaja 1',
      home: HomePage(),
    );
  }
}
