import 'package:flutter/cupertino.dart';
import 'package:vaja_1/src/ui/widgets/helpers/dividors.dart';

class ListItem extends StatelessWidget {
  const ListItem({
    Key? key,
    required this.title,
    required this.data,
  }) : super(key: key);

  final String title;
  final String data;

  @override
  Widget build(BuildContext context) {
    return Column(
      children: <Widget>[
        Text(title),
        horizontalSpaceDividerSmall,
        Text(data),
      ],
    );
  }
}
