part of 'accelerometer_bloc.dart';

abstract class AccelerometerEvent extends Equatable {
  const AccelerometerEvent();
}

class AccelerometerInitialize extends AccelerometerEvent {
  const AccelerometerInitialize();

  @override
  List<Object?> get props => [];
}

class AccelerometerChange extends AccelerometerEvent {
  const AccelerometerChange({
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
