part of 'accelerometer_bloc.dart';

abstract class AccelerometerState extends Equatable {
  const AccelerometerState();
}

class AccelerometerDisabled extends AccelerometerState {
  const AccelerometerDisabled();

  @override
  List<Object> get props => [];
}

class AccelerometerData extends AccelerometerState {
  const AccelerometerData({
    required this.x,
    required this.y,
    required this.z,
  });

  final double x;
  final double y;
  final double z;

  @override
  List<Object?> get props => [x, y, z];
}
