import 'package:flutter/cupertino.dart';
import 'package:flutter_bloc/flutter_bloc.dart';
import 'package:vaja_1/src/blocs/location_bloc/location_bloc.dart';
import 'package:vaja_1/src/ui/widgets/list_item.dart';

class LocationWidget extends StatefulWidget {
  const LocationWidget({Key? key}) : super(key: key);

  @override
  State<StatefulWidget> createState() {
    return _LocationWidgetState();
  }
}

class _LocationWidgetState extends State<LocationWidget> {
  @override
  Widget build(BuildContext context) {
    //BlocProvider.of<LocationBloc>(context).add(const LocationInitialize());

    return BlocConsumer<LocationBloc, LocationState>(
      listener: (BuildContext context, LocationState state) {
        print(state);
      },
      builder: (BuildContext context, LocationState state) {
        if (state is LocationData) {
          return ListItem(
            title: 'Location',
            data: state.longitude!.toStringAsFixed(6) +
                ' ' +
                state.latitude!.toStringAsFixed(6),
          );
        } else {
          return Container();
        }
      },
    );
  }
}
