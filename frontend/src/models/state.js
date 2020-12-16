const EventEmitter = require('events');


class State extends EventEmitter {
  constructor(){
    super();
  }

  setModel(model){
    this.model = model;
    this.displayModel();
  }

  displayModel(){
    this.emit('modelLines', this.model.toLines());
  }
}

export default new State();
