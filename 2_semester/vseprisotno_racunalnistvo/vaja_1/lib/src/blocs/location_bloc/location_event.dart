part of 'location_bloc.dart';

abstract class LocationEvent extends Equatable {
  const LocationEvent();
}

class LocationInitialize extends LocationEvent {
  const LocationInitialize();
  @override
  List<Object?> get props => [];
}

class LocationChange extends LocationEvent {
  const LocationChange({
    required this.latitude,
    required this.longitude,
  });

  final double? latitude;
  final double? longitude;

  @override
  List<Object?> get props => [latitude, longitude];
}
