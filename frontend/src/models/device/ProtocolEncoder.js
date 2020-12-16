import { ProtocolMessageType } from './MessageTypes';

const FLOAT_BYTES = 4;

function arrayBufferConcat(buffer1, buffer2){
  const tmp = new Uint8Array(buffer1.byteLength + buffer2.byteLength);
  tmp.set(new Uint8Array(buffer1), 0);
  tmp.set(new Uint8Array(buffer2), buffer1.byteLength);
  return tmp.buffer;
}

class ProtocolEncoder {
  static encodeJog(axisDistance){
    const intBuffer = new ArrayBuffer(1);
    const intView = new Uint8Array(intBuffer);
    const floatBuffer = new ArrayBuffer(9 * FLOAT_BYTES);
    const floatView = new Float32Array(floatBuffer);

    intView[0] = ProtocolMessageType.JOG;
    floatView[0] = axisDistance.x || 0;
    floatView[1] = axisDistance.y || 0;
    floatView[2] = axisDistance.z || 0;
    floatView[3] = axisDistance.a || 0;
    floatView[4] = axisDistance.b || 0;
    floatView[5] = axisDistance.c || 0;
    floatView[6] = axisDistance.u || 0;
    floatView[7] = axisDistance.w || 0;
    floatView[8] = axisDistance.v || 0;

    return arrayBufferConcat(intBuffer, floatBuffer);
  }
}

export default ProtocolEncoder;
