import 'package:bloc/bloc.dart';
import 'package:equatable/equatable.dart';
import 'package:sensors_plus/sensors_plus.dart';

part 'accelerometer_event.dart';
part 'accelerometer_state.dart';

class AccelerometerBloc extends Bloc<AccelerometerEvent, AccelerometerState> {
  AccelerometerBloc() : super(const AccelerometerDisabled()) {
    on<AccelerometerEvent>(
        (AccelerometerEvent event, Emitter<AccelerometerState> emit) async {
      if (event is AccelerometerInitialize) {
        _onAccelerometerInitialize(event, emit);
      } else if (event is AccelerometerChange) {
        await _onAccelerometerChange(event, emit);
      }
    });
  }

  Future<void> _onAccelerometerInitialize(
      AccelerometerInitialize event, Emitter<AccelerometerState> emit) async {
    accelerometerEvents.listen((data) {
      add(
        AccelerometerChange(x: data.x, y: data.y, z: data.z),
      );
    });
  }

  Future<void> _onAccelerometerChange(
      AccelerometerChange event, Emitter<AccelerometerState> emit) async {
    emit(
      AccelerometerData(x: event.x, y: event.y, z: event.z),
    );
  }
}
