import 'package:flutter/cupertino.dart';
import 'package:flutter_bloc/flutter_bloc.dart';
import 'package:vaja_1/src/blocs/gyroscope_bloc/gyroscope_bloc.dart';

import '../../../widgets/list_item.dart';

class GyroscopeWidget extends StatefulWidget {
  const GyroscopeWidget({Key? key}) : super(key: key);

  @override
  State<StatefulWidget> createState() {
    return _GyroscopeWidgetState();
  }
}

class _GyroscopeWidgetState extends State<GyroscopeWidget> {
  @override
  Widget build(BuildContext context) {
    return BlocConsumer<GyroscopeBloc, GyroscopeState>(
      listener: (BuildContext context, GyroscopeState state) {},
      builder: (BuildContext context, GyroscopeState state) {
        if (state is GyroscopeData) {
          return ListItem(
            title: 'Gyroscope',
            data: state.x.toStringAsFixed(4) +
                ' ' +
                state.y.toStringAsFixed(4) +
                ' ' +
                state.z.toStringAsFixed(4),
          );
        } else {
          return Container();
        }
      },
    );
  }
}
