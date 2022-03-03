import 'dart:async';

import 'package:bloc/bloc.dart';
import 'package:equatable/equatable.dart';
import 'package:sensors_plus/sensors_plus.dart';

part 'gyroscope_event.dart';
part 'gyroscope_state.dart';

class GyroscopeBloc extends Bloc<GyroscopeEvent, GyroscopeState> {
  GyroscopeBloc() : super(const GyroscopeDisabled()) {
    on<GyroscopeEvent>((event, emit) async {
      if (event is GyroscopeInitialize) {
        _onGyroscopeInitialize(event, emit);
      } else if (event is GyroscopeChange) {
        _onGyroscopeChange(event, emit);
      }
    });
  }

  Future<void> _onGyroscopeInitialize(
      GyroscopeInitialize event, Emitter<GyroscopeState> emit) async {
    gyroscopeEvents.listen((data) {
      add(
        GyroscopeChange(x: data.x, y: data.y, z: data.z),
      );
    });
  }

  Future<void> _onGyroscopeChange(
      GyroscopeChange event, Emitter<GyroscopeState> emit) async {
    emit(
      GyroscopeData(x: event.x, y: event.y, z: event.z),
    );
  }
}
