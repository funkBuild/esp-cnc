import React, { useContext, Fragment } from 'react';
import Window from '../Window';
import FileList from './FileList';
import FileDetails from './FileDetails';
import GcodeViewer from '../GcodeViewer'
import { FileContext } from './FileContext';

function windowContent(loadedFile){
  if(loadedFile)
    return <GcodeViewer />
  else
    return (
      <Fragment>
        <FileList />
        <FileDetails  />
      </Fragment>
    )
}

export default function FileManager(props){
  const { loadedFile } = useContext(FileContext);

  return (
    <Window>
      { windowContent(loadedFile) }
    </Window>
  )
}


