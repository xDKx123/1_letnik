part of 'location_bloc.dart';

abstract class LocationState extends Equatable {
  const LocationState();
}

class LocationDisabled extends LocationState {
  const LocationDisabled();

  @override
  List<Object?> get props => [];
}

class LocationData extends LocationState {
  const LocationData({
    required this.latitude,
    required this.longitude,
  });

  final double? latitude;
  final double? longitude;

  @override
  List<Object?> get props => [latitude, longitude];
}
