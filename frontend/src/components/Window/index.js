import React, { Component } from 'react';

import './Window.css';

class Window extends Component {
  state = {
    open: true
  };

  componentDidMount(){
    // Prevents OrbitControls from reacting to events meant for the Window content
    this.container.addEventListener('wheel', this.preventPropagation, { passive: false });
    this.container.addEventListener('mousedown', this.preventPropagation);
    this.container.addEventListener('mouseup', this.preventPropagation);
  }

  componentWillUnmount(){
    this.container.removeEventListener('wheel', this.preventPropagation);
    this.container.removeEventListener('mousedown', this.preventPropagation);
    this.container.removeEventListener('mouseup', this.preventPropagation);
  }

  toggle(){
    this.setState({open: !this.state.open});
  }

  get collapseIcon(){
    if(this.state.open)
      return <svg id="ei-chevron-up-icon" viewBox="0 0 50 50" width="100%" height="100%"><path d="M33.3 28.7L25 20.4l-8.3 8.3-1.4-1.4 9.7-9.7 9.7 9.7z"></path></svg>
    else
      return <svg id="ei-chevron-down-icon" viewBox="0 0 50 50"><path d="M25 32.4l-9.7-9.7 1.4-1.4 8.3 8.3 8.3-8.3 1.4 1.4z"></path></svg>
  }

  preventPropagation = (e) => {
    e.stopPropagation();
  }

  render() {
    return (
      <div className="Window" ref={elem => this.container = elem}>
        <div className="Window-header">
          <span>☰</span>
          <span className="title">{ this.props.title }</span>
          <span onClick={() => this.toggle()}>
            { this.collapseIcon }
          </span>
        </div>
        { this.state.open && (
          <div className="Window-content">
            { this.props.children }
          </div>
        )}
      </div>
    );
  }
}

export default Window;



