const EventEmitter = require('events');

class DeviceWebsocket extends EventEmitter {
  constructor(){
    super();

    this.connect();
  }

  connect(){
    this._socket = new WebSocket(`ws://${process.env.REACT_APP_DEVICE_IP}/ws`);
    this._socket.binaryType = "arraybuffer";

    this._socket.addEventListener('open', this.onConnect.bind(this));
    this._socket.addEventListener('message', this.onMessage.bind(this));
    this._socket.addEventListener('close', this.onDisconnect.bind(this));
  }

  onMessage(event){
    this.emit('message', event);
  }

  onConnect(){
    console.log('Socket connected');
    this.emit('connected');
  }

  onDisconnect(){
    console.log('Websocket closed');
    this.emit('disconnected');
    setTimeout(() => this.connect(), 1000);
  }

  send(message){
    this._socket.send(message);
  }
}

export default DeviceWebsocket;
