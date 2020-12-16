import React, { useContext, useState } from 'react';
import * as Icon from 'react-feather';


import "./GcodeActions.css"


export default function GcodeActions(props){

  return (
    <div className="GcodeActions">
      <span>
        <Icon.Play />
      </span>
      <span>
        <Icon.Pause />
      </span>
    </div>
  );
}
