part of 'magnetometer_bloc.dart';

abstract class MagnetometerEvent extends Equatable {
  const MagnetometerEvent();
}

class MagnetometerInitialize extends MagnetometerEvent {
  const MagnetometerInitialize();

  @override
  List<Object?> get props => [];
}

class MagnetometerChange extends MagnetometerEvent {
  const MagnetometerChange({
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
