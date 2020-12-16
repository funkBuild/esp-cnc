import React, { useContext, useState } from 'react';
import GcodeLineList from './GcodeLineList';
import GcodeActions from './GcodeActions';
import { JobContext } from '../../context/JobContext';

//import './FileList.css';

export default function GcodeViewer(props){
  const { loadedFile } = useContext(JobContext);
  const [currentLine, setCurrentLine] = useState(0);

  if(!loadedFile)
    return null
  
  return (
    <div>
      <GcodeActions />
      <GcodeLineList currentLine={currentLine} file={loadedFile} />
    </div>
  );
}
