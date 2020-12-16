import EventEmitter from 'events';
import DeviceWebsocket from './device/Websocket';
import ProtocolParser from './device/ProtocolParser';
import ProtocolEncoder from './device/ProtocolEncoder';
import { ProtocolMessageType } from './device/MessageTypes';

class Device extends EventEmitter {
  constructor(){
    super();

    this.state = {
      position: {
        x: 0,
        y: 0,
        z: 0,
        a: 0,
        b: 0,
        c: 0,
        u: 0,
        v: 0,
        w: 0
      }
    };

    this.websocket = new DeviceWebsocket();
    this.websocket.on('message', this.handleMessage.bind(this));
  }

  handleMessage(binaryMessage){
    const message = ProtocolParser.parse(binaryMessage);

    switch(message.type){
      case ProtocolMessageType.POSITION_UPDATE:
        this.updatePosition(message.position);
        break;
      case ProtocolMessageType.JOB_LINE_NUMBER:
        this.updateLineNumber(message.lineNumber);
        break;
    }
  }

  updatePosition(position){
    this.state.position = Object.assign(this.state.position, position);
    this.emit("positionUpdated", this.state.position);
  }

  updateLineNumber(lineNumber){
    this.emit("jobLineNumber", lineNumber);
  }

  jog(axisDistance){
    const cmdBuffer = ProtocolEncoder.encodeJog(axisDistance);
    this.websocket.send(cmdBuffer);
  }
}

export default new Device();
