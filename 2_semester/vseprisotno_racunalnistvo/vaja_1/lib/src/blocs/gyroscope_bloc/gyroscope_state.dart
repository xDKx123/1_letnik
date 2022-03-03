part of 'gyroscope_bloc.dart';

abstract class GyroscopeState extends Equatable {
  const GyroscopeState();
}

class GyroscopeDisabled extends GyroscopeState {
  const GyroscopeDisabled();

  @override
  List<Object> get props => [];
}

class GyroscopeData extends GyroscopeState {
  const GyroscopeData({
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
