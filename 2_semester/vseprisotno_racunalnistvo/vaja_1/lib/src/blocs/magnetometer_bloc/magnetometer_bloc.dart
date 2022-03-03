import 'dart:async';

import 'package:bloc/bloc.dart';
import 'package:equatable/equatable.dart';
import 'package:sensors_plus/sensors_plus.dart';

part 'magnetometer_event.dart';
part 'magnetometer_state.dart';

class MagnetometerBloc extends Bloc<MagnetometerEvent, MagnetometerState> {
  MagnetometerBloc() : super(MagnetometerDisabled()) {
    on<MagnetometerEvent>((event, emit) async {
      if (event is MagnetometerInitialize) {
        _onMagnetometerInitialize(event, emit);
      } else if (event is MagnetometerChange) {
        await _onMagnetometerChange(event, emit);
      }
    });
  }

  Future<void> _onMagnetometerInitialize(
      MagnetometerInitialize event, Emitter<MagnetometerState> emit) async {
    magnetometerEvents.listen((data) {
      add(
        MagnetometerChange(x: data.x, y: data.y, z: data.z),
      );
    });
  }

  Future<void> _onMagnetometerChange(
      MagnetometerChange event, Emitter<MagnetometerState> emit) async {
    emit(
      MagnetometerData(x: event.x, y: event.y, z: event.z),
    );
  }
}
