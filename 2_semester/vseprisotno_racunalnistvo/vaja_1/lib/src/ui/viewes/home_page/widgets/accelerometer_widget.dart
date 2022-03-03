import 'package:flutter/cupertino.dart';
import 'package:flutter_bloc/flutter_bloc.dart';
import 'package:vaja_1/src/blocs/accelerometer_bloc/accelerometer_bloc.dart';
import 'package:vaja_1/src/ui/widgets/list_item.dart';

class AccelerometerWidget extends StatefulWidget {
  const AccelerometerWidget({Key? key}) : super(key: key);

  @override
  State<StatefulWidget> createState() {
    return _AccelerometerWidgetState();
  }
}

class _AccelerometerWidgetState extends State<AccelerometerWidget> {
  @override
  Widget build(BuildContext context) {
    return BlocConsumer<AccelerometerBloc, AccelerometerState>(
        listener: (context, state) {},
        builder: (context, state) {
          if (state is AccelerometerData) {
            return ListItem(
              title: 'Accelerometer',
              data: state.x.toStringAsFixed(4) +
                  ' ' +
                  state.y.toStringAsFixed(4) +
                  ' ' +
                  state.z.toStringAsFixed(4),
            );
          } else {
            return Container();
          }
        });
  }
}
