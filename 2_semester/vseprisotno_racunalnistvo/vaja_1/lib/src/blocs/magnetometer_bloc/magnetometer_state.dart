part of 'magnetometer_bloc.dart';

abstract class MagnetometerState extends Equatable {
  const MagnetometerState();
}

class MagnetometerDisabled extends MagnetometerState {
  @override
  List<Object> get props => [];
}

class MagnetometerData extends MagnetometerState {
  const MagnetometerData({
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
