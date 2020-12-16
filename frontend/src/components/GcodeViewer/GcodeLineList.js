import React, { useContext, useState } from 'react';
import GcodeLine from './GcodeLine';

import './GcodeLineList.css';

export default function GcodeLineList(props){
  const { currentLine, file } = props;

  const lines = file.gcodeLines.slice(0, 5000);

  return (
    <div className="GcodeLineList">
      { lines.map( (line, lineNumber) => <GcodeLine line={line} lineNumber={lineNumber+1} key={lineNumber} />) }
    </div>
  )
}
