import 'dart:async';

import 'package:bloc/bloc.dart';
import 'package:equatable/equatable.dart';
import 'package:location/location.dart';

part 'location_event.dart';
part 'location_state.dart';

class LocationBloc extends Bloc<LocationEvent, LocationState> {
  LocationBloc() : super(const LocationDisabled()) {
    on<LocationEvent>((LocationEvent event, Emitter<LocationState> emit) async {
      if (event is LocationInitialize) {
        _onLocationInitialize(event, emit);
      }
      if (event is LocationChange) {
        await _onLocationChange(event, emit);
      }
    });
  }

  final Location _location = Location();

  Future<void> _onLocationInitialize(
      LocationInitialize event, Emitter<LocationState> emit) async {
    _location.onLocationChanged.listen((locationData) {
      add(
        LocationChange(
          latitude: locationData.latitude,
          longitude: locationData.longitude,
        ),
      );
    });
  }

  Future<void> _onLocationChange(
      LocationChange event, Emitter<LocationState> emit) async {
    emit(
      LocationData(
        latitude: event.latitude,
        longitude: event.longitude,
      ),
    );
  }
}
