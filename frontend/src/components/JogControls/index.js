import React, { Component } from 'react';
import Window from '../Window';
import Device from '../..//models/Device';

import './JogControls.css';

const AXIS_ORDER = [
  ['x', 'y', 'z'],
  ['a', 'b', 'c'],
  ['u', 'v', 'w']
]

class JogControls extends Component {
  constructor(){
    super();

    this.state = {
      axisIdx: 0,
      jogDistance: 1.0
    };
  }

  onAxisChange(){
    let nextIdx = this.state.axisIdx + 1;

    if(!AXIS_ORDER[nextIdx]) nextIdx = 0;

    this.setState({ axisIdx: nextIdx });
  }

  onClickHandler(pos0 = 0, pos1 = 0, pos2 = 0){
    const { axisIdx, jogDistance } = this.state;
    let axisDistance = {};    
    axisDistance[ AXIS_ORDER[axisIdx][0] ] = pos0 * jogDistance;
    axisDistance[ AXIS_ORDER[axisIdx][1] ] = pos1 * jogDistance;
    axisDistance[ AXIS_ORDER[axisIdx][2] ] = pos2 * jogDistance;

    Device.jog(axisDistance);
  }

  axisName(idx){
    const { axisIdx } = this.state;
    return AXIS_ORDER[axisIdx][idx].toUpperCase();
  }

  render() {
    return (
      <Window title="Axes">
        <div className="JogControls">
          <span class="row">
            <span onClick={() => this.onClickHandler(-1, 1)}>↖</span>
            <span onClick={() => this.onClickHandler(0, 1)}>{ this.axisName(1) }+</span>
            <span onClick={() => this.onClickHandler(1, 1)}>↗</span>
          </span>
          <span class="row">
            <span onClick={() => this.onClickHandler(-1, 0)}>{ this.axisName(0) }-</span>
            <span onClick={() => this.onAxisChange()}>X/Y</span>
            <span onClick={() => this.onClickHandler(1, 0)}>{ this.axisName(0) }+</span>
          </span>
          <span class="row">
            <span onClick={() => this.onClickHandler(-1, -1)}>↙</span>
            <span onClick={() => this.onClickHandler(0, -1)}>{ this.axisName(1) }-</span>
            <span onClick={() => this.onClickHandler(1, -1)}>↘</span>
          </span>
        </div>
      </Window>
    );
  }
}

export default JogControls;



