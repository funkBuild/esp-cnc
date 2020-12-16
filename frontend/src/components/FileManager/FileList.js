import React, { useContext } from 'react';
import FileListItem from './FileListItem';
import DragAndDropArea from './DragAndDropArea';
import { bytesToString } from '../../util/conversions';
import { FileContext } from './FileContext';
import { Plus, FolderPlus } from 'react-feather';
import { Loading } from "../Loading"

import './FileList.css';

const backItem = {name: '..', type: 'd'};

export default () => {
  const {files, directories, usedSpace, totalSpace, loading, handleUpload, currentPath, unsetSelected} = useContext(FileContext);
  let key = 0;

  return (
    <React.Fragment>
      <DragAndDropArea handleDrop={files => handleUpload(files)}>
        <div className="FileList" onClick={() => unsetSelected()}>
          <Loading hidden={!loading} />

          <div className="list-container">
            { currentPath !== '' && <FileListItem item={backItem} key={key++} /> }
            { directories.map(item => <FileListItem item={item} key={key++} />) }
            { files.map(item => <FileListItem item={item} key={key++} />) }
          </div>
        </div>
        <div className="FileMenu">
          <div className="actions">
            <div>
              <Plus />
            </div>
            <div>
              <FolderPlus />
            </div>  
          </div>
          <div className="free-space">
            <span>{ bytesToString(1024 * usedSpace) } / { bytesToString(1024 * totalSpace) }</span>
            <div className="free-space-graph">
              <div style={{width: `${100*usedSpace/totalSpace}%`}}>&nbsp;</div>
            </div>
          </div>
        </div>
      </DragAndDropArea>
    </React.Fragment>
  )
}
