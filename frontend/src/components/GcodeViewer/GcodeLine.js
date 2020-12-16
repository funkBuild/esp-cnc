import React, { Fragment } from 'react';


import './GcodeLine.css';

export default React.memo(function GcodeLine(props){
  const { line, lineNumber } = props;

  const parts = line.match(/(;.+|[-\d\.]+|[^\d-]+)/g).map(part => part.trim());
  const elements = [];

  for(let i=0; i < parts.length; i += 2){
    const letter = parts[i].toUpperCase();
    const number = parts[i+1];

    elements.push((
      <span className={`${letter}`} key={i/2}>
        <span>{letter}</span>
        <span>{number}</span>
      </span>
    ));
  }

  return (
    <div className={`gcodeLine`} key={ lineNumber }>
      <span>{ lineNumber }</span>
      { elements }
    </div>
  )
})

