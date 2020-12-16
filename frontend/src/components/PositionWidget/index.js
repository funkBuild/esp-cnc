import React, { Component } from 'react';
import Device from '../../models/Device';
import Window from '../Window';

import './PositionWidget.css';

const AXES = ['x', 'y', 'z']

class DeviceControls extends Component {
  componentDidMount(){
    Device.on("positionUpdated", () => this.forceUpdate());
  }

  renderAxis(axis){
    return (
      <div className="axis" key={axis.toUpperCase()}>
        <div className="axisLabel">
          <span>{ axis.toUpperCase() }</span>
          <span>mm</span>
        </div>
        <div className="axisPosition">
          <span>{ Device.state.position[axis].toFixed(3) }</span>
          <span>{ Device.state.position[axis].toFixed(3) }</span>
        </div>
        <div className="axisButtons">
          <div>
            <svg class="feather feather-home sc-dnqmqq jxshSx" xmlns="http://www.w3.org/2000/svg" width="15" height="15" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" aria-hidden="true" data-reactid="671"><path d="M3 9l9-7 9 7v11a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2z"></path><polyline points="9 22 9 12 15 12 15 22"></polyline></svg>
          </div>
          <div>
            <svg class="feather feather-disc sc-dnqmqq jxshSx" xmlns="http://www.w3.org/2000/svg" width="15" height="15" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" aria-hidden="true" data-reactid="466"><circle cx="12" cy="12" r="10"></circle><circle cx="12" cy="12" r="3"></circle></svg>
          </div>
        </div>
      </div>
    );
  }

  render() {
    return (
      <Window title="Position">
        { AXES.map(axis => this.renderAxis(axis)) }
      </Window>
    );
  }
}

export default DeviceControls;



