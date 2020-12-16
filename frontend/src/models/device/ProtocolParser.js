import { ProtocolMessageType } from './MessageTypes';

class ProtocolParser {
  static parse(message){
    const intView = new Uint8Array(message.data);
    const messageType = intView[0];

    switch(messageType){
      case ProtocolMessageType.POSITION_UPDATE:
        return ProtocolParser.parsePositionUpdate(message.data);
      case ProtocolMessageType.JOB_LINE_NUMBER:
        return ProtocolParser.parseJobLineNumber(message.data);
    }

    throw new Error('Unsupported message from device');
  }

  static parsePositionUpdate(message){
    const floatView = new Float32Array(message.slice(1));

    return {
      type: ProtocolMessageType.POSITION_UPDATE,
      position: {
        x: floatView[0],
        y: floatView[1],
        z: floatView[2]
      }
    }
  }

  static parseJobLineNumber(message){
    const uintView = new Uint32Array(message.slice(1));
    console.dir(uintView);
    return {
      type: ProtocolMessageType.JOB_LINE_NUMBER,
      lineNumber: uintView[0]
    }
  }
}

export default ProtocolParser;
