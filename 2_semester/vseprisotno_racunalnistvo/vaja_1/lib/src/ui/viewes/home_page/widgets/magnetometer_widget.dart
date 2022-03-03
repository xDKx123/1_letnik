import 'package:flutter/cupertino.dart';
import 'package:flutter_bloc/flutter_bloc.dart';
import 'package:vaja_1/src/blocs/magnetometer_bloc/magnetometer_bloc.dart';
import 'package:vaja_1/src/ui/widgets/list_item.dart';

class MagnetometerWidget extends StatefulWidget {
  const MagnetometerWidget({Key? key}) : super(key: key);

  @override
  State<StatefulWidget> createState() {
    return _MagnetometerWidgetState();
  }
}

class _MagnetometerWidgetState extends State<MagnetometerWidget> {
  @override
  Widget build(BuildContext context) {
    return BlocConsumer<MagnetometerBloc, MagnetometerState>(
      listener: (BuildContext context, MagnetometerState state) {},
      builder: (BuildContext context, MagnetometerState state) {
        if (state is MagnetometerData) {
          return ListItem(
            title: 'Magnetometer',
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
