part of 'gyroscope_bloc.dart';

abstract class GyroscopeEvent extends Equatable {
  const GyroscopeEvent();
}

class GyroscopeInitialize extends GyroscopeEvent {
  const GyroscopeInitialize();

  @override
  List<Object?> get props => [];
}

class GyroscopeChange extends GyroscopeEvent {
  const GyroscopeChange({
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
